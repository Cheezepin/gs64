#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "sm64.h"
#include "actors/common0.h"
#include "actors/common1.h"
#include "gfx_dimensions.h"
#include "game_init.h"
#include "level_update.h"
#include "camera.h"
#include "print.h"
#include "ingame_menu.h"
#include "hud.h"
#include "segment2.h"
#include "area.h"
#include "save_file.h"
#include "print.h"
#include "battle_helpers.h"
#include "seq_ids.h"
#include "audio/external.h"
#include "object_list_processor.h"
#include "behavior_data.h"
#include "camera.h"
#include "object_helpers.h"

#include "s2d_engine/init.h"
#include "s2d_engine/s2d_draw.h"
#include "s2d_engine/s2d_print.h"
#include <PR/gs2dex.h>
#include "src/s2d_engine/icons/icons.c"
#include "src/s2d_engine/icons/icons.h"
#include "src/s2d_engine/icons/bar.h"
#include "src/s2d_engine/icons/barscripts/bar.h"

extern s16 gCutsceneTimer;

struct BattleInfo gBattleInfo;

extern struct SaveBuffer gSaveBuffer;

u8 gCharactersUnlocked;

void setup_mtx(uObjMtx *buf, int x, int y, float scale) {
	buf->m.A = FTOFIX32(scale);
	buf->m.D = FTOFIX32(scale);

	buf->m.X = x << 2;
	buf->m.Y = y << 2;

	buf->m.BaseScaleX = 1 << 10;
	buf->m.BaseScaleY = 1 << 10;
}

void call_icons_sprite_dl(int idx, int x, int y, uObjMtx *buffer, int buf_idx, float scale) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &icons_tex[idx]);
	setup_mtx(&buffer[buf_idx], x, y, scale);
	gSPObjMatrix(gDisplayListHead++, &buffer[buf_idx]);
	gSPObjSprite(gDisplayListHead++, &icons_obj);
}

void render_battle_fill_rect(ulx, uly, lrx, lry, r, g, b) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetFillColor(gDisplayListHead++, GPACK_RGBA5551(r,g,b,0) << 16 | GPACK_RGBA5551(r,g,b,0));
    gDPFillRectangle(gDisplayListHead++, ulx, uly, lrx, lry);
}

uObjMtx bar_buf[8][8];
void setup_bar_mtx(uObjMtx *buf, int x, int y, float scaleX, float scaleY) {
	buf->m.A = FTOFIX32(scaleX);
	buf->m.D = FTOFIX32(scaleY);

	buf->m.X = x << 2;
	buf->m.Y = y << 2;

	buf->m.BaseScaleX = 1 << 10;
	buf->m.BaseScaleY = 1 << 10;
}

void call_bar_split_sprite_dl(int idx, int x, int y, uObjMtx *buffer, float scaleX, float scaleY) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_NOTXCLAMP);
	gSPObjLoadTxtr(gDisplayListHead++, &bar_split_tex[idx]);
	setup_bar_mtx(&buffer[0], x, y, scaleX, scaleY);
	gSPObjMatrix(gDisplayListHead++, &buffer[0]);
	gSPObjSprite(gDisplayListHead++, &bar_split_obj);
}

uObjMtx buf[10];

char cbuf[512];
char cbuf_prev[512];
s8 atkr = 0;
s8 overIcon = 3;
u8 menuState = 0;
const char *atkrString = "Mario";
const char *enemyString = "Goomba";
const char *overString = "00000000";

void determine_over_icon(void) {
    //overIcon = random_u16() % 9;
    switch(overIcon) {
        case OVER_FIGHT:
            overString = "Fight";
            break;
        case OVER_FLEE:
            overString = "Flee";
            break;
        case OVER_STATUS:
            overString = "Status";
            break;
        case OVER_ATTACK:
            overString = "Attack";
            break;
        case OVER_PSYNERGY:
            overString = "Psynergy";
            break;
        case OVER_DJINN:
            overString = "Djinn";
            break;
        case OVER_SUMMON:
            overString = "Summon";
            break;
        case OVER_ITEM:
            overString = "Item";
            break;
        case OVER_DEFEND:
            overString = "Defend";
            break;
    }
}

u8 fL, fR, fU, fD;
void determine_joystick_increment(s8 initSprite, u8 maxSprite) {
    u8 oldOverIcon;

    switch(menuState) {
        case MENU_START:
        case MENU_FIGHT:
            oldOverIcon = overIcon;

            if(gPlayer1Controller->stickX > 20.0f && fR == 0) {
                overIcon++;
                fR = 5;
            } else if(gPlayer1Controller->stickX < -20.0f && fL == 0) {
                overIcon--;
                fL = 5;
            }

            if(overIcon < initSprite)
                overIcon = maxSprite;
            if(overIcon > maxSprite)
                overIcon = initSprite;

            if(oldOverIcon != overIcon) {
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            }

            break;
        case MENU_ATTACK:
            break;
    }

    if(fR > 0)
        fR--;
    if(fL > 0)
        fL--;
    if(fU > 0)
        fU--;
    if(fD > 0)
        fD--;
}

u8 turnOrder[7];
u8 agilities[7];
void determine_turn_order(void) {
    u8 i, j, k;
    
    gBattleInfo.turnActionProgress = 0;
    gBattleInfo.turnUser = 0;

    agilities[0] = gBattleInfo.player[0].agility;
    agilities[1] = gBattleInfo.player[1].agility;
    agilities[2] = gBattleInfo.player[2].agility;
    agilities[3] = gBattleInfo.player[3].agility;
    agilities[4] = gBattleInfo.enemy[0].agility;
    agilities[5] = gBattleInfo.enemy[1].agility;
    agilities[6] = gBattleInfo.enemy[2].agility;

    for(j = 0; j < 7; j++) {
        turnOrder[j] = 0;
    }

    for(j = 0; j < 7; j++) {
        for(i = 0; i < 7; i++) {
            if(turnOrder[i] == 0) {
                if(agilities[j] == 0)
                    turnOrder[i] = 0;
                else
                    turnOrder[i] = j + 1;
                i = 100;
            }
            else if (agilities[j] > agilities[turnOrder[i] - 1]) {
                for(k = 7; k < (i - 1); k--) {
                    turnOrder[k] = turnOrder[k-1];
                }
                turnOrder[i] = j + 1;
                i = 100;
            }
        }
    }

    for(j = 0; j < 7; j++) {
        if(turnOrder[j] == 0)
            turnOrder[j] = 0xFF;
        else
            turnOrder[j] -= 1;
    }
}

void exit_battle(void) {
    u8 i;
    menuState = MENU_NONE;
    overIcon = OVER_FIGHT;
    set_mario_action(gMarioState, ACT_IDLE, 0);
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, SEQ_LEVEL_GRASS), 0);
    gCamera->cutscene = 0;
    vec3f_copy(gMarioState->pos, gBattleInfo.lastPos);
    vec3f_copy(gMarioObject->header.gfx.pos, gMarioState->pos);
    gCutsceneTimer = 0;
    reset_camera(gCamera);
    for(i = 0; i < 3; i++) {
        if(gBattleInfo.enemy[i].obj != 0) {
            gBattleInfo.enemy[i].obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            gBattleInfo.enemy[i].obj = 0;
        }
        if(gBattleInfo.player[i+1].obj != 0) {
            gBattleInfo.player[i+1].obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            gBattleInfo.player[i+1].obj = 0;
        }
    }
}

void determine_menu_switch(void) {
    switch(menuState) {
        case MENU_START:
            if(overIcon == OVER_FIGHT && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_FIGHT;
                overIcon = OVER_ATTACK;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else if(overIcon == OVER_FLEE && gPlayer1Controller->buttonPressed & A_BUTTON) {
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
                exit_battle();
            }
            break;
        case MENU_FIGHT:
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                menuState = MENU_START;
                overIcon = OVER_FIGHT;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(overIcon == OVER_ATTACK && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_ATTACK;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            }
            break;
        case MENU_ATTACK:
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                menuState = MENU_FIGHT;
                overIcon = OVER_ATTACK;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(gPlayer1Controller->buttonPressed & A_BUTTON) {
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                determine_turn_order();
                menuState = MENU_TURN;
                gBattleInfo.player[0].action = ACT_ATTACK;
            }
            break;
    }
}

u8 barsRendered;

void render_bar(int ulx, int uly, int lrx, int lry) {
    if(barsRendered < 8) {
        u8 idx = barsRendered;
        render_battle_fill_rect(ulx + 4, uly + 4, lrx - 4, lry - 4, 0, 0x5A, 0x84);
        call_bar_split_sprite_dl(1, ulx + 8, uly, &bar_buf[idx][1], (f32)(lrx - ulx - 8) / 8.0f, 1.0f);
        call_bar_split_sprite_dl(3, lrx - 8, uly + 8, &bar_buf[idx][3], 1.0f, (f32)(lry - uly - 8) / 8.0f);
        call_bar_split_sprite_dl(5, ulx + 8, lry - 8, &bar_buf[idx][5], (f32)(lrx - ulx - 8) / 8.0f, 1.0f);
        call_bar_split_sprite_dl(7, ulx, uly + 8, &bar_buf[idx][7], 1.0f, (f32)(lry - uly - 8) / 8.0f);
        call_bar_split_sprite_dl(0, ulx, uly, &bar_buf[idx][0], 1.0f, 1.0f);
        call_bar_split_sprite_dl(2, lrx - 8, uly, &bar_buf[idx][2], 1.0f, 1.0f);
        call_bar_split_sprite_dl(4, lrx - 8, lry - 8, &bar_buf[idx][4], 1.0f, 1.0f);
        call_bar_split_sprite_dl(6, ulx, lry - 8, &bar_buf[idx][6], 1.0f, 1.0f);
        barsRendered++;
    }
}

void render_bar_wh(int ulx, int uly, int w, int h) {
    render_bar(ulx, uly, ulx + w, uly + h);
}

char tbuf[512];

void gs_print(int x, int y, const char *str, int shadow) {
    uObjMtx *sbuf;
    if(shadow == SHADOW) {
        sbuf = alloc_display_list(sizeof(uObjMtx) * s2d_strlen(str));
        sprintf(tbuf, COLOR"0 0 0 255%s", str);
        s2d_print(x, y + 1, tbuf, sbuf);
    }
    sbuf = alloc_display_list(sizeof(uObjMtx) * s2d_strlen(str));
    sprintf(tbuf, COLOR"255 255 255 255%s", str);
    s2d_print(x, y, tbuf, sbuf);
}

struct Object *pointer;
void print_pointer(void) {
    if(pointer == 0) {
        pointer = spawn_object(gMarioObject, MODEL_POINTER, bhvPointer);
    }
    pointer->oPosX = gBattleInfo.enemy[0].obj->oPosX;
    pointer->oPosY = gMarioObject->oPosY + 150.0f;
    pointer->oPosZ = gBattleInfo.enemy[0].obj->oPosZ;
}

void render_battle_icons(void) {
    uObjMtx *sbuf;
    u8 i, frontLayerIcon, frontLayerXval, globalTimerMod, initSprite, maxSprite;
    u8 xval;
    f32 iconScale;

    iconScale = 0;
    s2d_init();

    sprintf(cbuf, "");
    sprintf(cbuf_prev, "");

    determine_menu_switch();

    switch(menuState) {
            case MENU_START:
                initSprite = 0;
                maxSprite = 2;
                xval = 112;
                gBattleInfo.camState = CAMERA_SIDE;
                break;
            case MENU_FIGHT:
                initSprite = 3;
                maxSprite = 8;
                xval = 80;
                gBattleInfo.camState = CAMERA_BACK;
                break;
        }

        determine_joystick_increment(initSprite, maxSprite);

    if(menuState == MENU_START || menuState == MENU_FIGHT) {
        determine_over_icon();
        if(pointer != 0) {
            pointer->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            pointer = 0;
        }
        for(i = initSprite; i < maxSprite + 1; i++){
            if(overIcon == i) {
                globalTimerMod = gGlobalTimer % 8;
                if (globalTimerMod > 3) {
                    globalTimerMod = 8 - globalTimerMod;
                }
                iconScale = ((f32)(globalTimerMod) / 8.0f) + 1.0f;
                frontLayerIcon = i;
                frontLayerXval = xval;
            } else {
                call_icons_sprite_dl(i, (s32) xval - 16, 208, &buf[i - initSprite], 0, 1.0f);
            }
            xval += 32;
        }
        if(iconScale != 0)
        call_icons_sprite_dl(frontLayerIcon, (s32)((frontLayerXval) - (iconScale*16.0f)), 224 - (s32)(iconScale*16.0f), &buf[frontLayerIcon - initSprite], 0, iconScale);

        //gSPDisplayList(gDisplayListHead++, bar_sprite_dl);
        //render_bar(256, 212, 320, 236);
        render_bar_wh(256, 212, 64, 24);
        sprintf(cbuf, "%s", overString);
        gs_print(254, 220, cbuf, SHADOW);
    } else if (menuState == MENU_ATTACK) {
        call_icons_sprite_dl(OVER_ATTACK, (s32) 80, 208, &buf[0], 0, 1.0f);
        render_bar_wh(112, 208, 128, 32);
        gs_print(148, 220, "Attack", SHADOW);
        print_pointer();
    }

    s2d_stop();
}

void render_previous_text(void) {
    u16 i;
    for(i = 0; i < 512; i++) {
        cbuf_prev[i] = cbuf[i];
    }
}

void print_battle_text(void) {
    if(cbuf_prev[0] == 0x00) {
        gs_print(0, 212, cbuf, NO_SHADOW);
    } else {
        gs_print(0, 212, cbuf_prev, NO_SHADOW);
        gs_print(0, 228, cbuf, NO_SHADOW);
    }
}

void render_battle_init_text(void) {
    uObjMtx *sbuf;
    enemyString = gBattleInfo.enemy[0].name;
    s2d_init();
    sprintf(cbuf, "%s attacks!", enemyString);
    gs_print(0, 212, cbuf, NO_SHADOW);
    s2d_stop();
    if(gPlayer1Controller->buttonPressed & A_BUTTON)
        menuState = MENU_START;
}

s16 calculate_damage(s16 attack, s16 defense) {
    s16 damage;

    damage = attack - defense;

    if(damage < 0)
        damage = 0;

    return damage;
}

u8 targetDead;
void apply_damage(s16 damage, u8 target) {
    s16 targetHP;
    u8 i;

    if(target < 4) {
        targetHP = gBattleInfo.player[target].HP -= damage;
    } else {
        targetHP = gBattleInfo.enemy[target - 4].HP -= damage;
    }

    if(targetHP <= 0) {
        targetDead = 1;
        for(i = 0; i < 7; i++) {
            if(turnOrder[i] == target)
                turnOrder[i] = 0xFF;
        }
        if(target < 4)
            gBattleInfo.player[target].HP = 0;
        else
            gBattleInfo.enemy[target - 4].HP = 0;
    }
}

u8 enemy_death(u8 target) {
    struct Object *targetObj = gBattleInfo.enemy[target].obj;
    if(targetObj != 0) {
        if(targetObj->header.gfx.scale[0] > 0.0f) {
            obj_scale(targetObj, targetObj->header.gfx.scale[0] - 0.0625f);
            return 1;
        } else {
            targetObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            gBattleInfo.enemy[target].obj = 0;
        }
    }
    return 0;
}

get_attacker_string(u8 switchBy) {
    switch(switchBy) {
        case 0:
            atkrString = "Mario";
            break;
        case 1:
            atkrString = "Verio";
            break;
        case 2:
            atkrString = "Jurio";
            break;
        case 3:
            atkrString = "Merio";
            break;
    }
}
u8 isAttackDone;
u8 animPlaying;
s16 damage;
void render_battle_attack_text(void) {
    uObjMtx *sbuf;
    u8 turnUserID;
    u8 userActionProgressMax;

    s2d_init();
    turnUserID = turnOrder[gBattleInfo.turnUser];
    if(turnUserID < 4) {
        u8 target = gBattleInfo.player[turnUserID].target - 4;
        get_attacker_string(turnUserID);
        switch(gBattleInfo.player[turnUserID].action) {
            case ACT_ATTACK:
                switch(gBattleInfo.turnActionProgress) {
                    case 0:
                        sprintf(cbuf, "%s attacks!", atkrString);
                        break;
                    case 1:
                        damage = calculate_damage(5 + gBattleInfo.player[turnUserID].attack, gBattleInfo.enemy[target].defense);
                        sprintf(cbuf, "It does %d damage!", damage);
                        break;
                    case 2:
                        apply_damage(damage, gBattleInfo.player[turnUserID].target);
                        if(targetDead == 0)
                            isAttackDone = 1;
                        else {
                            animPlaying = enemy_death(target);
                            sprintf(cbuf, "%s falls!", gBattleInfo.enemy[target].name);
                        }
                        break;
                    case 3:
                        isAttackDone = 1;
                        break;
                }
                break;
        }
    } else {
                switch(gBattleInfo.turnActionProgress) {
                    case 0:
                        sprintf(cbuf, "%s attacks!", gBattleInfo.enemy[turnUserID - 4].name);
                        break;
                    case 1:
                        sprintf(cbuf, "It does 5 damage!");
                        break;
                    case 2:
                        isAttackDone = 1;
                        break;
                }
    }
    if(isAttackDone == 0) {
        print_battle_text();
    }
    s2d_stop();
    if((gPlayer1Controller->buttonPressed & A_BUTTON || isAttackDone == 1) && animPlaying == 0) {
        u16 i;
        if(isAttackDone == 1) {
            gBattleInfo.turnUser++;
            targetDead = 0;
            gBattleInfo.turnActionProgress = 0;
            isAttackDone = 0;
            if(gBattleInfo.enemy[0].obj == 0 && gBattleInfo.enemy[1].obj == 0 && gBattleInfo.enemy[2].obj == 0) {
                menuState = MENU_WIN;
                render_previous_text();
            }
        } else {
            gBattleInfo.turnActionProgress++;
            render_previous_text();
        }
        while(turnOrder[gBattleInfo.turnUser] == 0xFF && gBattleInfo.turnUser < 7) {
            if(gBattleInfo.turnUser == 7)    
                menuState = MENU_START;
            else
                gBattleInfo.turnUser++;
        }
        if(gBattleInfo.turnUser == 7 && menuState == MENU_TURN)    
                menuState = MENU_START;
    }
}

void render_battle_win_text(void) {
    uObjMtx *sbuf;
    u8 turnUserID;
    u8 userActionProgressMax;

    s2d_init();
    sprintf(cbuf, "You win!");
    print_battle_text();
    s2d_stop();

    if(gPlayer1Controller->buttonPressed & A_BUTTON) {
        exit_battle();
    }
}

char hbuf[512];
void render_health(void) {
    u8 i;
    s2d_init();
    //for(i = 0; i <= gCharactersUnlocked; i++) {
    //    render_bar_wh(320 - ((i+1)*64), 0, 64, 32);
    //}
    render_battle_fill_rect(0, 0, 320, 32, 0x00, 0x00, 0x00);
    render_bar_wh(320 - ((gCharactersUnlocked+2)*64), 0, (gCharactersUnlocked+2)*64, 32);
    for(i = 0; i <= gCharactersUnlocked; i++) {
        render_battle_fill_rect(320 - (i+1)*64, 4, 321 - (i+1)*64, 28, 0x00, 0x97, 0xE2);
        render_battle_fill_rect(319 - (i+1)*64, 4, 320 - (i+1)*64, 28, 0x00, 0x37, 0x41);
        render_battle_fill_rect(261 - (i)*64, 0, 298 - (i)*64, 8, 0x00, 0x5A, 0x84);
        get_attacker_string(gCharactersUnlocked - i);
        sprintf(hbuf, "%s", atkrString);
        gs_print(256 - (i*64), 0, hbuf, SHADOW);
        render_battle_fill_rect(260 - (i)*64, 15, 308 - (i)*64, 18, 0xDB, 0x00, 0x00);
        render_battle_fill_rect(260 - (i)*64, 15, 260 - (i)*64 + (s32)(((f32)gBattleInfo.player[gCharactersUnlocked - i].HP / (f32)gBattleInfo.player[gCharactersUnlocked - i].baseHP)*48.0f), 18, 0x00, 0x00, 0xD0);
        sprintf(hbuf, "HP %d", gBattleInfo.player[gCharactersUnlocked - i].HP);
        gs_print(256 - (i*64), 10, hbuf, SHADOW);
        render_battle_fill_rect(260 - (i)*64, 25, 308 - (i)*64, 28, 0xDB, 0x00, 0x00);
        render_battle_fill_rect(260 - (i)*64, 25, 260 - (i)*64 + (s32)(((f32)gBattleInfo.player[gCharactersUnlocked - i].PP / (f32)gBattleInfo.player[gCharactersUnlocked - i].basePP)*48.0f), 28, 0x00, 0x00, 0xD0);
        sprintf(hbuf, "PP %d", gBattleInfo.player[gCharactersUnlocked - i].PP);
        gs_print(256 - (i*64), 20, hbuf, SHADOW);
    }
    s2d_stop();
}

void initialize_player(u8 player) {
    gBattleInfo.player[0].agility = 5;
    gBattleInfo.player[0].attack = 4;
    gBattleInfo.player[0].defense = 3;
    gBattleInfo.player[0].target = 4;
    gBattleInfo.player[player].HP = random_u16() % 30;
    gBattleInfo.player[player].PP = random_u16() % 20;
    gBattleInfo.player[player].baseHP = 30;
    gBattleInfo.player[player].basePP = 20;

    if(player == 0) {
        gBattleInfo.player[0].obj = &gMarioObject;
        gMarioState->pos[0] = gMarioState->pos[2] = (-62.5*gCharactersUnlocked);
        gMarioState->pos[1] = -11000.0f;
        vec3f_copy(gMarioObject->header.gfx.pos, gMarioState->pos);
    } else {
        struct BattlePlayer *me; 
        gBattleInfo.player[player].obj = spawn_object(gMarioObject, MODEL_MARIO, bhvPointer);
        me = &gBattleInfo.player[player];
        me->obj->oPosX = (-62.5*gCharactersUnlocked) + (125.0f*player);
        me->obj->oPosZ = (-62.5*gCharactersUnlocked) + (125.0f*player);
        me->obj->oPosY = -11000.0f;
    }
}

void initialize_battle(void) {
    u8 i;
    struct Object *enemyTemp;
    gCharactersUnlocked = gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked;
    gBattleInfo.enemy[0].obj = enemyTemp = spawn_object(gMarioObject, MODEL_GOOMBA, bhvEnemy);
    gMarioObject->header.gfx.angle[1] = 0x6000;
    vec3f_copy(gBattleInfo.lastPos, gMarioState->pos);
    start_cutscene(gCamera, CUTSCENE_BATTLE);
    set_mario_action(gMarioState, ACT_BATTLE, 0);
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_BATTLE), 0);
    copy_mario_state_to_object();
    for(i = 0; i <= gCharactersUnlocked; i++) {
        initialize_player(i);
    }
}

void render_battle(void) {
    barsRendered = 0;
    gCamera->cutscene = CUTSCENE_BATTLE;
    gHudDisplay.flags = HUD_DISPLAY_NONE;
    update_camera(gCamera);
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
    render_battle_fill_rect(0, 208, 320, 240, 0, 0, 0);
    render_health();
    switch(menuState) {
        case MENU_NONE:
            render_battle_init_text();
            break;
        case MENU_TURN:
            render_battle_attack_text();
            break;
        case MENU_WIN:
            render_battle_win_text();
            break;
        default:
            render_battle_icons();
            break;

    }
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0x3000);

    print_text_fmt_int(50, 50, "%d", gBattleInfo.enemy[0].HP);
}