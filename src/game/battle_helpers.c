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
#include "src/s2d_engine/icons/elements.c"
#include "src/s2d_engine/icons/elements.h"
#include "src/s2d_engine/icons/psynergy.c"
#include "src/s2d_engine/icons/psynergy.h"

extern s16 gCutsceneTimer;

struct BattleInfo gBattleInfo;

extern struct SaveBuffer gSaveBuffer;

struct SequenceQueueItem {
    u8 seqId;
    u8 priority;
};

extern struct SequenceQueueItem sBackgroundMusicQueue[6];

u8 gCharactersUnlocked;

struct Spell None = {
    "",
    "",
    SPELL_NONE,
    0,
    255,
    0,
    RANGE_SINGLE_ENEMY,
};

struct Spell Guard = {
    "Guard",
    "Boost ally's Defense.",
    SPELL_GUARD,
    5,
    0,
    3,
    RANGE_SINGLE_PARTY,
};

struct Spell Protect = {
    "Protect",
    "Boost party's Defense.",
    SPELL_PROTECT,
    5,
    4,
    5,
    RANGE_ALL_PARTY,
};

struct Spell Flare = {
    "Flare",
    "Attack with flaring flames.",
    SPELL_FLARE,
    5,
    0,
    4,
    RANGE_SINGLE_ENEMY,
};

struct Spell FlareWall = {
    "Flare Wall",
    "Attack with searing flames.",
    SPELL_FLARE_WALL,
    12,
    2,
    7,
    RANGE_ALL_ENEMIES,
};

struct Spell FlareStorm = {
    "Flare Storm",
    "Attack with incinerating flames.",
    SPELL_FLARE_STORM,
    20,
    6,
    12,
    RANGE_ALL_ENEMIES,
};

struct Spell Volcano = {
    "Volcano",
    "Attack with volcanic might.",
    SPELL_VOLCANO,
    15,
    8,
    6,
    RANGE_SINGLE_ENEMY,
};

struct Spell Growth = {
    "Growth",
    "Attack with wild plants.",
    SPELL_GROWTH,
    0,
    0,
    0,
    RANGE_SINGLE_ENEMY,
};

struct Spell Quake = {
    "Quake",
    "Attack with a powerful quake.",
    SPELL_QUAKE,
    0,
    0,
    0,
    RANGE_ALL_ENEMIES,
};

struct Spell Earthquake = {
    "Earthquake",
    "Attack with a mighty tremor.",
    SPELL_EARTHQUAKE,
    0,
    0,
    0,
    RANGE_ALL_ENEMIES,
};

struct Spell QuakeSphere = {
    "Quake Sphere",
    "Attack with a massive quake.",
    SPELL_QUAKE_SPHERE,
    0,
    0,
    0,
    RANGE_ALL_ENEMIES,
};

struct Spell Spire = {
    "Spire",
    "Attack with an earthen spire.",
    SPELL_SPIRE,
    0,
    0,
    0,
    RANGE_SINGLE_ENEMY,
};

struct Spell Whirlwind = {
    "Whirlwind",
    "Attack with a swirling tornado.",
    SPELL_WHIRLWIND,
    0,
    0,
    0,
    RANGE_ALL_ENEMIES,
};

struct Spell Tornado = {
    "Quake",
    "Attack with a mighty tornado.",
    SPELL_TORNADO,
    0,
    0,
    0,
    RANGE_ALL_ENEMIES,
};

struct Spell Impact = {
    "Impact",
    "Boost ally's attack.",
    SPELL_IMPACT,
    0,
    0,
    0,
    RANGE_SINGLE_PARTY,
};

struct Spell HighImpact = {
    "High Impact",
    "Boost party's attack.",
    SPELL_HIGH_IMPACT,
    0,
    0,
    0,
    RANGE_ALL_PARTY,
};

struct Spell Revive = {
    "Revive",
    "Revive a downed ally.",
    SPELL_REVIVE,
    0,
    0,
    0,
    RANGE_SINGLE_PARTY,
};

struct Spell Frost = {
    "Frost",
    "Attack with icy blasts.",
    SPELL_FROST,
    5,
    0,
    3,
    RANGE_SINGLE_ENEMY,
};

struct Spell Tundra = {
    "Tundra",
    "Attack with frigid blasts.",
    SPELL_TUNDRA,
    5,
    4,
    5,
    RANGE_ALL_ENEMIES,
};

struct Spell Glacier = {
    "Glacier",
    "Attack with subzero blasts.",
    SPELL_GLACIER,
    5,
    0,
    4,
    RANGE_ALL_ENEMIES,
};

struct Spell Ply = {
    "Ply",
    "Restore 100 HP with faith's power.",
    SPELL_PLY,
    12,
    2,
    7,
    RANGE_SINGLE_PARTY,
};

struct Spell PlyWell = {
    "Ply Well",
    "Restore 200 HP with faith's power.",
    SPELL_PLY_WELL,
    20,
    6,
    12,
    RANGE_SINGLE_PARTY,
};

struct Spell Wish = {
    "Wish",
    "Restore 80 HP to the whole party.",
    SPELL_WISH,
    15,
    8,
    6,
    RANGE_ALL_PARTY,
};

struct Spell *MarsPool[7] = {
    &Flare,
    &FlareWall,
    &FlareStorm,
    &Guard,
    &Protect,
    &Volcano,
    &None,
};

struct Spell *VenusPool[6] = {
    &Growth,
    &Quake,
    &Earthquake,
    &QuakeSphere,
    &Spire,
    &None,
};

struct Spell *JupiterPool[6] = {
    &Whirlwind,
    &Tornado,
    &Impact,
    &HighImpact,
    &Revive,
    &None,
};

struct Spell *MercuryPool[7] = {
    &Frost,
    &Tundra,
    &Glacier,
    &Ply,
    &PlyWell,
    &Wish,
    &None,
};

struct Spell **SpellPool[4] = {
    &MarsPool,
    &VenusPool,
    &JupiterPool,
    &MercuryPool,
};

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
s8 selectedPsynergy;
u8 displayedSelectedPsynergy = 0;
s8 pointerSelectedTarget = 0;
void determine_joystick_increment(s8 initSprite, u8 maxSprite, u8 range) {
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
        case MENU_PSYNERGY:
            if(gPlayer1Controller->stickY > 20.0f && fU == 0) {
                fU = 5;
                selectedPsynergy -= 1;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            } else if(gPlayer1Controller->stickY < -20.0f && fD == 0) {
                fD = 5;
                selectedPsynergy += 1;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            }
            break;
        case MENU_SELECT:
            if(gPlayer1Controller->stickX > 20.0f && fR == 0) {
                pointerSelectedTarget++;
                fR = 5;
            } else if(gPlayer1Controller->stickX < -20.0f && fL == 0) {
                pointerSelectedTarget--;
                fL = 5;
            }
            
            switch(range) {
                case RANGE_SINGLE_ENEMY:
                    if(pointerSelectedTarget > gBattleInfo.totalEnemies)
                        pointerSelectedTarget = 0;
                    if(pointerSelectedTarget < 0)
                        pointerSelectedTarget = gBattleInfo.totalEnemies;
                    while(gBattleInfo.enemy[pointerSelectedTarget].obj == 0) {
                        if(fR > fL)
                            pointerSelectedTarget++;
                        else
                            pointerSelectedTarget--;
                        if(pointerSelectedTarget > gBattleInfo.totalEnemies)
                            pointerSelectedTarget = 0;
                        if(pointerSelectedTarget < 0)
                            pointerSelectedTarget = 2;
                    }
                    break;
                case RANGE_ALL_ENEMIES:
                case RANGE_ALL_PARTY:
                    pointerSelectedTarget = 0;
                    break;
                case RANGE_SINGLE_PARTY:
                    if(pointerSelectedTarget < 0)
                        pointerSelectedTarget = gCharactersUnlocked;
                    if(pointerSelectedTarget > gCharactersUnlocked)
                        pointerSelectedTarget = 0;
                    break;
            }
            break;
        case MENU_ATTACK:
            if(gPlayer1Controller->stickX > 20.0f && fR == 0) {
                pointerSelectedTarget++;
                fR = 5;
            } else if(gPlayer1Controller->stickX < -20.0f && fL == 0) {
                pointerSelectedTarget--;
                fL = 5;
            }

            if(pointerSelectedTarget > gBattleInfo.totalEnemies)
                pointerSelectedTarget = 0;
            if(pointerSelectedTarget < 0)
                pointerSelectedTarget = gBattleInfo.totalEnemies;
            while(gBattleInfo.enemy[pointerSelectedTarget].obj == 0) {
                pointerSelectedTarget--;
                if(pointerSelectedTarget < 0)
                    pointerSelectedTarget = 2;
            }
            break;
    }

    if(menuState != MENU_START && menuState != MENU_FIGHT) {
        oldOverIcon = overIcon;
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

    for(j = 0; j <= gCharactersUnlocked; j++) {
        if(gBattleInfo.player[j].HP <= 0)
            agilities[j] = 0;
        else
            agilities[j] = gBattleInfo.player[j].agility;
    }
    for(j = 0; j < 3; j++) {
        if(gBattleInfo.enemy[j].HP <= 0)
            agilities[j + 4] = 0;
        else
            agilities[j + 4] = gBattleInfo.enemy[j].agility;
    }

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
                for(k = 7; k > (i); k--) {
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
    stop_background_music(sBackgroundMusicQueue[0].seqId);
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, gBattleInfo.lastSeq), 0);
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

void determine_next_selecting_player(void) {
    if(gBattleInfo.selectingUser < gCharactersUnlocked) {
        gBattleInfo.selectingUser++;
        menuState = MENU_FIGHT;
    } else {
        determine_turn_order();
        menuState = MENU_TURN;
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
                if(gBattleInfo.selectingUser > 0) {
                    menuState = MENU_FIGHT;
                    overIcon = OVER_ATTACK;
                    gBattleInfo.selectingUser--;
                } else {
                    menuState = MENU_START;
                    overIcon = OVER_FIGHT;
                }
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(overIcon == OVER_ATTACK && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_ATTACK;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else if(overIcon == OVER_PSYNERGY && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_PSYNERGY;
                selectedPsynergy = 0;
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
                gBattleInfo.player[gBattleInfo.selectingUser].action = ACT_ATTACK;
                determine_next_selecting_player();
            }
            break;
        case MENU_PSYNERGY:
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                menuState = MENU_FIGHT;
                overIcon = OVER_PSYNERGY;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(gPlayer1Controller->buttonPressed & A_BUTTON) {
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                menuState = MENU_SELECT;
                gBattleInfo.prevMenu = MENU_PSYNERGY;
            }
            break;
        case MENU_SELECT:
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                menuState = gBattleInfo.prevMenu;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(gPlayer1Controller->buttonPressed & A_BUTTON) {
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                determine_next_selecting_player();
            }
            break;
    }

    if(menuState == MENU_FIGHT) {
        deactivate_pointers();
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

struct Object *pointer[4];
void print_pointer(u8 rangeType) {
    u8 i;
    if(menuState == MENU_SELECT || menuState == MENU_ATTACK) {
        if(rangeType == RANGE_SINGLE_ENEMY) {
            if(pointer[0] == 0) {
                pointer[0] = spawn_object(gMarioObject, MODEL_POINTER, bhvPointer);
            }
            pointer[0]->oPosX = gBattleInfo.enemy[pointerSelectedTarget].obj->oPosX;
            pointer[0]->oPosY = gMarioObject->oPosY + 150.0f;
            pointer[0]->oPosZ = gBattleInfo.enemy[pointerSelectedTarget].obj->oPosZ;
            for(i = 1; i < 4; i++) {
                if(pointer[i] != 0) {
                    pointer[i]->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                    pointer[i] = 0;
                }
            }
            gBattleInfo.player[gBattleInfo.selectingUser].target[0] = pointerSelectedTarget + 4;
            gBattleInfo.player[gBattleInfo.selectingUser].target[1], gBattleInfo.player[gBattleInfo.selectingUser].target[2] = 0xFF;
        } else if(rangeType == RANGE_ALL_ENEMIES) {
            for(i = 0; i < 3; i++) {
                if(gBattleInfo.enemy[i].obj != 0) {
                    if(pointer[i] == 0) {
                        pointer[i] = spawn_object(gMarioObject, MODEL_POINTER, bhvPointer);
                    }
                    pointer[i]->oPosX = gBattleInfo.enemy[i].obj->oPosX;
                    pointer[i]->oPosY = gMarioObject->oPosY + 150.0f;
                    pointer[i]->oPosZ = gBattleInfo.enemy[i].obj->oPosZ;
                    gBattleInfo.player[gBattleInfo.selectingUser].target[i] = i + 4;
                }
            }
        } else if(rangeType == RANGE_SINGLE_PARTY) {
            if(pointer[0] == 0) {
                pointer[0] = spawn_object(gMarioObject, MODEL_POINTER, bhvPointer);
            }
            pointer[0]->oPosX = gBattleInfo.player[pointerSelectedTarget].obj->oPosX;
            pointer[0]->oPosY = gMarioObject->oPosY + 150.0f;
            pointer[0]->oPosZ = gBattleInfo.player[pointerSelectedTarget].obj->oPosZ;
            for(i = 1; i < 4; i++) {
                if(pointer[i] != 0) {
                    pointer[i]->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                    pointer[i] = 0;
                }
            }
            gBattleInfo.player[gBattleInfo.selectingUser].target[0] = pointerSelectedTarget;
            gBattleInfo.player[gBattleInfo.selectingUser].target[1], gBattleInfo.player[gBattleInfo.selectingUser].target[2] = 0xFF;
        } else if(rangeType == RANGE_ALL_PARTY) {
            for(i = 0; i < 4; i++) {
                if(pointer[i] == 0) {
                    pointer[i] = spawn_object(gMarioObject, MODEL_POINTER, bhvPointer);
                }
                pointer[i]->oPosX = gBattleInfo.player[i].obj->oPosX;
                pointer[i]->oPosY = gMarioObject->oPosY + 150.0f;
                pointer[i]->oPosZ = gBattleInfo.player[i].obj->oPosZ;
                gBattleInfo.player[gBattleInfo.selectingUser].target[i] = i;
            }
        }
    }
}

void deactivate_pointers(void) {
    u8 i;
    for(i = 0; i < 4; i++) {
        if(pointer[i] != 0) {
            pointer[i]->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            pointer[i] = 0;
        }
    }
    pointerSelectedTarget = 0;
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

        determine_joystick_increment(initSprite, maxSprite, 0);

    if(menuState == MENU_START || menuState == MENU_FIGHT) {
        determine_over_icon();
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
    } /* else if (menuState == MENU_ATTACK) {
        call_icons_sprite_dl(OVER_ATTACK, 80, 208, &buf[0], 0, 1.0f);
        render_bar_wh(112, 208, 128, 32);
        gs_print(148, 220, "Attack", SHADOW);
        print_pointer(0);
    } */

    s2d_stop();
}

void call_spell_sprite_dl(int idx, int x, int y, uObjMtx *buffer) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &spell_tex[idx]);
	setup_mtx(&buffer[0], x, y, 1);
	gSPObjMatrix(gDisplayListHead++, &buffer[0]);
	gSPObjSprite(gDisplayListHead++, &spell_obj);
}

uObjMtx ebuf[6];
uObjMtx hebuf2[6];
char spbuf[512];
u8 psynergyMax = 0;

void render_psynergy_menu(void) {
    struct Spell **movePool;
    u8 i, j = 0;
    determine_menu_switch();
    determine_joystick_increment(0, 255, 0);
    s2d_init();
    call_icons_sprite_dl(OVER_PSYNERGY, 128, 208, &buf[0], 0, 1.0f);
    render_bar_wh(112, 88, 208, 152);
    render_bar_wh(0, 56, 320, 32);
    movePool = SpellPool[gBattleInfo.selectingUser];
    for(i = 0; i < 100; i++) {
        if(movePool[i]->baseLevel > gSaveBuffer.files[gCurrSaveFileNum - 1][0].level) {
            j++;
        }
        if(movePool[i]->sprite == SPELL_NONE) {
            psynergyMax = i - j;
            i = 254;
        }
    }
    
    i = 0;
    if(selectedPsynergy > psynergyMax)
        selectedPsynergy = 0;
    if(selectedPsynergy < 0)
        selectedPsynergy = psynergyMax;
    j = 0;
    render_battle_fill_rect(116, 92 + selectedPsynergy*24, 316, 116 + selectedPsynergy*24, 0x00, 0x97, 0xE2);
    while(i < 255) {
        if(movePool[i]->sprite != SPELL_NONE) {
            if(movePool[i]->baseLevel <= gSaveBuffer.files[gCurrSaveFileNum - 1][0].level) {
                call_spell_sprite_dl(movePool[i]->sprite, 120, 96 + j*24, &ebuf[j]);
                call_element_sprite_dl(gBattleInfo.selectingUser, 280, 100 + j*24, &hebuf2[j]);
                sprintf(spbuf, "%s", movePool[i]->name);
                gs_print(136, 100 + j*24, spbuf, SHADOW);
                sprintf(spbuf, "PP %d", movePool[i]->PP);
                gs_print(232, 100 + j*24, spbuf, SHADOW);
                if(selectedPsynergy == j)
                    displayedSelectedPsynergy = i;
                j++;
            }
            i++;
        } else {
            i = 255;
        }
    }
    sprintf(spbuf, "%s", movePool[displayedSelectedPsynergy]->tooltip);
    gs_print(4, 68, spbuf, SHADOW);
    s2d_stop();
}

void render_select_menu(void) {
    struct Spell **movePool = SpellPool[gBattleInfo.selectingUser];
    print_pointer(movePool[displayedSelectedPsynergy]->range);
    determine_menu_switch();
    determine_joystick_increment(0, 255, movePool[displayedSelectedPsynergy]->range);

    gBattleInfo.player[gBattleInfo.selectingUser].action = ACT_PSYNERGY;
    gBattleInfo.player[gBattleInfo.selectingUser].subAction = displayedSelectedPsynergy;

    s2d_init();
    call_icons_sprite_dl(OVER_PSYNERGY, 80, 208, &buf[0], 0, 1.0f);
    render_bar_wh(112, 208, 208, 32);
    call_spell_sprite_dl(movePool[displayedSelectedPsynergy]->sprite, 120, 216, &ebuf[0]);
    call_element_sprite_dl(gBattleInfo.selectingUser, 280, 220, &hebuf2[0]);
    sprintf(spbuf, "%s", movePool[displayedSelectedPsynergy]->name);
    gs_print(136, 220, spbuf, SHADOW);
    sprintf(spbuf, "PP %d", movePool[displayedSelectedPsynergy]->PP);
    gs_print(232, 220, spbuf, SHADOW);
    s2d_stop();
}

void render_select_attack_menu(void) {
    determine_menu_switch();
    print_pointer(0);
    determine_joystick_increment(0, 255, 0);
    s2d_init();
    call_icons_sprite_dl(OVER_ATTACK, 80, 208, &buf[0], 0, 1.0f);
    render_bar_wh(112, 208, 128, 32);
    gs_print(148, 220, "Attack", SHADOW);
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
            targetDead = 0;
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
s8 target, targetNo;
u8 turnUserID;

u8 search_for_next_enemy() {
    u8 l = 1;
    u8 trueTarget;
    //target = -1;
    while(l == 1 && target < 3) {
        target++;
        if(gBattleInfo.enemy[target].obj != 0) {
            l = 0;
        }
    }
    if(target == 3 && l == 1)
        isAttackDone = 1;
    if(l == 0) {
        if(gBattleInfo.player[turnUserID].target[2] == target + 4)
            targetNo = 2;
        else if(gBattleInfo.player[turnUserID].target[1] == target + 4)
            targetNo = 1;
        gBattleInfo.player[turnUserID].target[targetNo] = target + 4;
    }
    return l;
}

void render_battle_attack_text(void) {
    u8 spellUsed;
    u8 k, l;
    struct Spell **movePool;

    deactivate_pointers();
    s2d_init();
    turnUserID = turnOrder[gBattleInfo.turnUser];
    if(isAttackDone == 0) {
        if(turnUserID < 4) {
            get_attacker_string(turnUserID);
            target = gBattleInfo.player[turnUserID].target[targetNo] - 4;
            switch(gBattleInfo.player[turnUserID].action) {
                case ACT_ATTACK:
                    switch(gBattleInfo.turnActionProgress) {
                        case 0:
                            if(gBattleInfo.enemy[target].obj == 0) {
                                search_for_next_enemy();
                            }
                            else {
                                sprintf(cbuf, "%s attacks!", atkrString);
                            }
                            break;
                        case 1:

                            damage = calculate_damage(5 + gBattleInfo.player[turnUserID].attack, gBattleInfo.enemy[target].defense);
                            sprintf(cbuf, "%s takes %d damage!", gBattleInfo.enemy[target].name, damage);
                            break;
                        case 2:
                            apply_damage(damage, target + 4);
                            if(targetDead == 0)
                                isAttackDone = 1;
                            else {
                                animPlaying = enemy_death(target);
                                sprintf(cbuf, "You felled %s!", gBattleInfo.enemy[target].name);
                            }
                            break;
                        case 3:
                            isAttackDone = 1;
                            break;
                    }
                    break;
                case ACT_PSYNERGY:
                movePool = SpellPool[turnUserID];
                spellUsed = gBattleInfo.player[turnUserID].subAction;
                    switch(gBattleInfo.turnActionProgress) {
                        case 0:
                            if(gBattleInfo.enemy[target].obj == 0) {
                                search_for_next_enemy();
                            }
                            else {
                                sprintf(cbuf, "%s casts %s!", atkrString, movePool[spellUsed]->name);
                            }
                            break;
                        case 1:
                            damage = calculate_damage(5 + gBattleInfo.player[turnUserID].attack, gBattleInfo.enemy[target].defense);
                            sprintf(cbuf, "%s takes %d damage!", gBattleInfo.enemy[target].name, damage);
                            break;
                        case 2:
                            apply_damage(damage, target + 4);
                            if(targetDead == 0)
                                isAttackDone = 1;
                            else {
                                animPlaying = enemy_death(target);
                                sprintf(cbuf, "You felled %s!", gBattleInfo.enemy[target].name);
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
    }
    if(isAttackDone == 0) {
        print_battle_text();
    }
    s2d_stop();
    if((gPlayer1Controller->buttonPressed & A_BUTTON || isAttackDone == 1) && animPlaying == 0) {
        u16 i, tempTargetNo;
        if(isAttackDone == 1) {
            targetNo++;
            if(turnUserID < 4 && (targetNo >= 3 || gBattleInfo.player[turnUserID].target[targetNo] == 0xFF)) {
                k = 1;
            } else if(turnUserID >= 4 && (targetNo >= 4 || gBattleInfo.enemy[turnUserID].target[targetNo] == 0xFF)) {
                k = 1;
            } else if (turnUserID < 4 && gBattleInfo.player[turnUserID].target[targetNo] != 0xFF && gBattleInfo.enemy[gBattleInfo.player[turnUserID].target[targetNo] - 4].obj == 0) {
                k = search_for_next_enemy();
                /* for(tempTargetNo = targetNo; tempTargetNo < 3; tempTargetNo++) {
                    if(gBattleInfo.enemy[tempTargetNo].obj != 0 && gBattleInfo.player[turnUserID].target[targetNo] != 0xFF && k == 1) {
                        targetNo = tempTargetNo;
                        k = 0;
                    }
                } */
            } else {
                k = 0;
            }

            if(k == 1) {
                gBattleInfo.turnUser++;
                targetDead = 0;
                gBattleInfo.turnActionProgress = 0;
                isAttackDone = 0;
                targetNo = 0;
                if(gBattleInfo.enemy[0].obj == 0 && gBattleInfo.enemy[1].obj == 0 && gBattleInfo.enemy[2].obj == 0) {
                    menuState = MENU_WIN;
                    stop_background_music(sBackgroundMusicQueue[0].seqId);
                    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, SEQ_VICTORY), 0);
                    render_previous_text();
                }
            } else {
                gBattleInfo.turnActionProgress = 1;
                isAttackDone = 0;
                targetDead = 0;
                render_previous_text();
            }
        } else {
            if(targetDead == 0) {
                gBattleInfo.turnActionProgress++;
                render_previous_text();
            }
            else {
                    isAttackDone = 1;
                    render_previous_text();
            }
        }
        while(turnOrder[gBattleInfo.turnUser] == 0xFF && gBattleInfo.turnUser < 7) {
            if(gBattleInfo.turnUser == 7)    
                menuState = MENU_START;
            else {
                gBattleInfo.turnUser++;
                targetNo = 0;
            }
        }
        if(gBattleInfo.turnUser == 7 && menuState == MENU_TURN) {
                menuState = MENU_START;
                gBattleInfo.selectingUser = 0;
        }
    }
}

void render_battle_win_text(void) {
    s2d_init();
    sprintf(cbuf, "You win!");
    print_battle_text();
    s2d_stop();

    if(gPlayer1Controller->buttonPressed & A_BUTTON) {
        exit_battle();
    }
}

void call_element_sprite_dl(int idx, int x, int y, uObjMtx *buffer) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &element_tex[idx]);
	setup_mtx(&buffer[0], x, y, 1);
	gSPObjMatrix(gDisplayListHead++, &buffer[0]);
	gSPObjSprite(gDisplayListHead++, &element_obj);
}

char hbuf[512];
uObjMtx hebuf[4];

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
    call_element_sprite_dl(0, 198 - (gCharactersUnlocked*64), 6, &hebuf[0]);
    call_element_sprite_dl(1, 198 - (gCharactersUnlocked*64), 18, &hebuf[1]);
    call_element_sprite_dl(2, 230 - (gCharactersUnlocked*64), 18, &hebuf[2]);
    call_element_sprite_dl(3, 230 - (gCharactersUnlocked*64), 6, &hebuf[3]);

    sprintf(hbuf, " %d", gBattleInfo.player[0].agility);
    gs_print(196 - (gCharactersUnlocked*64), 6, hbuf, SHADOW);
    sprintf(hbuf, " %d", 01);
    gs_print(196 - (gCharactersUnlocked*64), 18, hbuf, SHADOW);
    sprintf(hbuf, " %d", 01);
    gs_print(228 - (gCharactersUnlocked*64), 6, hbuf, SHADOW);
    sprintf(hbuf, " %d", 01);
    gs_print(228 - (gCharactersUnlocked*64), 18, hbuf, SHADOW);
    s2d_stop();
}

void initialize_player(u8 player) {
    struct BattlePlayer *partyStats = &gBattleInfo.player[player];
    struct Player *file = &gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[player];
    partyStats->agility = partyStats->baseAgility = file->agility;
    partyStats->attack = partyStats->baseAttack = file->attack;
    partyStats->defense = partyStats->baseDefense = file->defense;
    partyStats->target[0] = 4;
    partyStats->target[1] = 0xFF;
    partyStats->target[2] = 0xFF;
    partyStats->HP = file->HP;
    partyStats->PP = file->PP;
    partyStats->baseHP = file->baseHP;
    partyStats->basePP = file->basePP;

    if(player == 0) {
        gBattleInfo.player[0].obj = gMarioObject;
        gMarioState->pos[0] = gMarioState->pos[2] = gMarioObject->oPosX = gMarioObject->oPosZ = (-62.5*gCharactersUnlocked);
        gMarioState->pos[1] = gMarioObject->oPosY = -11000.0f;
        vec3f_copy(gMarioObject->header.gfx.pos, gMarioState->pos);
    } else {
        if(partyStats->obj == 0)
            partyStats->obj = spawn_object(gMarioObject, MODEL_MARIO, bhvPointer);
        partyStats->obj->oPosX = (-62.5*gCharactersUnlocked) + (125.0f*player);
        partyStats->obj->oPosZ = (-62.5*gCharactersUnlocked) + (125.0f*player);
        partyStats->obj->oPosY = -11000.0f;
    }
}

void initialize_battle(void) {
    u8 i;
    struct Object *enemyTemp;
    gCharactersUnlocked = gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked;
    gBattleInfo.selectingUser = 0;
    gBattleInfo.totalEnemies = 0;
    for(i = 0; i < 3; i++) {
        gBattleInfo.enemy[i].obj = enemyTemp = spawn_object(gMarioObject, MODEL_GOOMBA, bhvEnemy);
        enemyTemp->oBehParams2ndByte = i;
        gBattleInfo.totalEnemies = i;
    }
    targetDead = 0;
    targetNo = 0;
    gMarioObject->header.gfx.angle[1] = 0x6000;
    vec3f_copy(gBattleInfo.lastPos, gMarioState->pos);
    start_cutscene(gCamera, CUTSCENE_BATTLE);
    set_mario_action(gMarioState, ACT_BATTLE, 0);
    gBattleInfo.lastSeq = sBackgroundMusicQueue[0].seqId;
    stop_background_music(sBackgroundMusicQueue[0].seqId);
    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, SEQ_BATTLE), 0);
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
        case MENU_PSYNERGY:
            render_psynergy_menu();
            break;
        case MENU_SELECT:
            render_select_menu();
            break;
        case MENU_ATTACK:
            render_select_attack_menu();
            break;
        default:
            render_battle_icons();
            break;

    }
    render_health();
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0x3000);

    print_text_fmt_int(25, 50, "%d", gBattleInfo.enemy[0].HP);
    print_text_fmt_int(50, 50, "%d", gBattleInfo.enemy[1].HP);
    print_text_fmt_int(75, 50, "%d", gBattleInfo.enemy[2].HP);
}