#include "src/game/battle_helpers.h"
#include "src/game/save_file.h"
#include "actors/group14.h"
#include "actors/group1.h"
#include "actors/group0.h"

extern struct SaveBuffer gSaveBuffer;
extern u8 turnOrder[7];
extern struct Spell **EnemySpellPool[12];
extern struct Spell None;

void bhv_enemy_init(void) {
    struct Enemy *enemy = &gBattleInfo.enemy[o->oBehParams2ndByte];
    o->oPosY = -11000.0f;
    o->oMoveAngleYaw = 0xE000;
    o->oMoveAnglePitch = o->oMoveAngleRoll = 0;
    o->oPosX = 375.0f + (150.0f*o->oBehParams2ndByte) - (gBattleInfo.totalEnemies*75.0f);
    o->oPosZ = -375.0f + (150.0f*o->oBehParams2ndByte) - (gBattleInfo.totalEnemies*75.0f);
    o->oInitialAnim = 0;
    switch(gBattleInfo.enemy[o->oBehParams2ndByte].id) {
        case ENEMY_GOOMBA:
            enemy->HP = enemy->baseHP = 5 + (random_u16() % 3);
            enemy->agility = 4;
            enemy->attack = 6;
            enemy->defense = 2;
            enemy->element = VENUS;
            sprintf(enemy->name, "Goomba");
            cur_obj_set_model(MODEL_GOOMBA);
            o->oAnimations = goomba_seg8_anims_0801DA4C;
            cur_obj_init_animation(0);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 50.0f;
            enemy->expYield = 4;
            enemy->psynergyChance = 1;
            break;
        case ENEMY_BOBOMB:
            enemy->HP = enemy->baseHP = 10 + (random_u16() % 3);
            enemy->agility = 7;
            enemy->attack = 7;
            enemy->defense = 2;
            enemy->element = MARS;
            sprintf(enemy->name, "Bob-omb");
            cur_obj_set_model(MODEL_BLACK_BOBOMB);
            o->oAnimations = bobomb_seg8_anims_0802396C;
            cur_obj_init_animation(0);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 50.0f;
            enemy->expYield = 10;
            enemy->psynergyChance = 6;
            break;
        case ENEMY_CHUCKYA:
            enemy->HP = enemy->baseHP = 16 + (random_u16() % 4);
            enemy->agility = 10;
            enemy->attack = 9;
            enemy->defense = 2;
            enemy->element = JUPITER;
            sprintf(enemy->name, "Chuckya");
            cur_obj_set_model(MODEL_CHUCKYA);
            o->oAnimations = chuckya_seg8_anims_0800C070;
            cur_obj_init_animation(5);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 125.0f;
            cur_obj_scale(1.5f);
            o->oInitialAnim = 5;
            enemy->expYield = 22;
            enemy->psynergyChance = 5;
            break;
        case ENEMY_AMP:
            enemy->HP = enemy->baseHP = 14 + (random_u16() % 3);
            enemy->agility = 18;
            enemy->attack = 8;
            enemy->defense = 4;
            enemy->element = JUPITER;
            sprintf(enemy->name, "Amp");
            cur_obj_set_model(MODEL_AMP);
            o->oAnimations = amp_seg8_anims_08004034;
            cur_obj_init_animation(0);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 70.0f;
            o->oGraphYOffset = 60.0f;
            o->oAnimState = 1;
            enemy->expYield = 32;
            enemy->psynergyChance = 3;
            break;
        case ENEMY_WHOMP:
            enemy->HP = enemy->baseHP = 16 + (random_u16() % 5);
            enemy->agility = 8;
            enemy->attack = 11;
            enemy->defense = 4;
            enemy->element = VENUS;
            sprintf(enemy->name, "Whomp");
            cur_obj_set_model(MODEL_WHOMP);
            o->oAnimations = whomp_seg6_anims_06020A04;
            cur_obj_init_animation(0);
            cur_obj_scale(0.5f);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 200.0f;
            enemy->expYield = 40;
            enemy->psynergyChance = 6;
            break;
        case ENEMY_THWOMP:
            enemy->HP = enemy->baseHP = 23 + (random_u16() % 5);
            enemy->agility = 2;
            enemy->attack = 16;
            enemy->defense = 8;
            enemy->element = MERCURY;
            sprintf(enemy->name, "Thwomp");
            cur_obj_set_model(MODEL_THWOMP);
            cur_obj_scale(0.75f);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 225.0f;
            enemy->expYield = 60;
            enemy->psynergyChance = 5;
            break;
        case ENEMY_BULLY:
            enemy->HP = enemy->baseHP = 25 + (random_u16() % 5);
            enemy->agility = 9;
            enemy->attack = 13;
            enemy->defense = 7;
            enemy->element = VENUS;
            sprintf(enemy->name, "Bully");
            cur_obj_set_model(MODEL_BULLY);
            o->oAnimations = bully_seg5_anims_0500470C;
            cur_obj_init_animation(0);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 125.0f;
            enemy->expYield = 45;
            enemy->psynergyChance = 5;
            break;
        case ENEMY_KOOPA:
            enemy->HP = enemy->baseHP = 30 + (random_u16() % 5);
            enemy->agility = 11;
            enemy->attack = 11;
            enemy->defense = 6;
            enemy->element = MERCURY;
            sprintf(enemy->name, "Koopa");
            cur_obj_set_model(MODEL_KOOPA_WITH_SHELL);
            o->oAnimations = koopa_seg6_anims_06011364;
            cur_obj_init_animation(9);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 175.0f;
            enemy->expYield = 38;
            enemy->psynergyChance = 5;
            break;
        case ENEMY_SCUTTLEBUG:
            enemy->HP = enemy->baseHP = 35 + (random_u16() % 5);
            enemy->agility = 12;
            enemy->attack = 9;
            enemy->defense = 5;
            enemy->element = JUPITER;
            sprintf(enemy->name, "Scuttlebug");
            cur_obj_set_model(MODEL_SCUTTLEBUG);
            o->oAnimations = scuttlebug_seg6_anims_06015064;
            cur_obj_init_animation(0);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 100.0f;
            enemy->expYield = 50;
            enemy->psynergyChance = 5;
            break;
        case ENEMY_PIRANHA:
            enemy->HP = enemy->baseHP = 27 + (random_u16() % 5);
            enemy->agility = 15;
            enemy->attack = 14;
            enemy->defense = 6;
            enemy->element = MARS;
            sprintf(enemy->name, "Piranha Plant");
            cur_obj_set_model(MODEL_PIRANHA_PLANT);
            o->oAnimations = piranha_plant_seg6_anims_0601C31C;
            cur_obj_init_animation(0);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 125.0f;
            enemy->expYield = 60;
            enemy->psynergyChance = 5;
            break;
        case ENEMY_KING_BOBOMB:
            enemy->HP = enemy->baseHP = 120;
            enemy->agility = 100;
            enemy->attack = 17;
            enemy->defense = 10;
            enemy->element = MARS;
            sprintf(enemy->name, "King Bob-Omb");
            cur_obj_set_model(MODEL_KING_BOBOMB);
            o->oAnimations = king_bobomb_seg5_anims_0500FE30;
            cur_obj_init_animation(5);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 250.0f;
            o->oInitialAnim = 5;
            enemy->expYield = 1000;
            enemy->psynergyChance = 3;
            break;
        case ENEMY_PORKY:
            enemy->HP = enemy->baseHP = 250;
            enemy->agility = 20;
            enemy->attack = 25;
            enemy->defense = 12;
            enemy->element = VENUS;
            sprintf(enemy->name, "Porky");
            cur_obj_set_model(MODEL_PORKY);
            o->oAnimations = porky_anims;
            cur_obj_init_animation(0);
            cur_obj_scale(0.25f);
            o->hitboxRadius = 72.0f;
            o->hitboxHeight = 250.0f;
            o->oInitialAnim = 0;
            enemy->expYield = 5000;
            enemy->psynergyChance = 3;
            break;
    }
    if(o->header.gfx.animInfo.curAnim != 0) {
        o->header.gfx.animInfo.animFrame = random_u16() % (o->header.gfx.animInfo.curAnim->loopEnd - 1);
    }

    //level scaling
    enemy->HP += (gSaveBuffer.files[gCurrSaveFileNum - 1][0].level) + (gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked*2);
    enemy->attack += ((gSaveBuffer.files[gCurrSaveFileNum - 1][0].level*1)/2) + gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked;
    enemy->defense += ((gSaveBuffer.files[gCurrSaveFileNum - 1][0].level*1)/2) + gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked;
    enemy->agility += (gSaveBuffer.files[gCurrSaveFileNum - 1][0].level);
}

void bhv_enemy_update(void) {
    u8 i;
    if(o->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
        f32 dist = 0;
        struct Enemy *enemy = &gBattleInfo.enemy[o->oBehParams2ndByte];
        struct Spell **spellPool = EnemySpellPool[enemy->id];
        struct Spell *spellUsed;

        if(!(menuState == MENU_TURN && turnOrder[gBattleInfo.turnUser] == o->oBehParams2ndByte + 4)) {
            if((random_u16() % enemy->psynergyChance) == 0 && spellPool != 0) {
                enemy->action = ACT_PSYNERGY;
                spellUsed = 0;
                do {
                    enemy->subAction = random_u16() % 4;
                    spellUsed = spellPool[enemy->subAction];
                } while(spellPool == 0 || spellUsed == &None);
            } else {
                enemy->action = ACT_ATTACK;
                enemy->subAction = 0;
            }

            if(enemy->action == ACT_ATTACK || (enemy->action == ACT_PSYNERGY && spellUsed != 0 && spellUsed->range == RANGE_SINGLE_ENEMY)) {
                enemy->target[0] = enemy_select_target(enemy->element);
                enemy->target[1] = 0xFF;
                enemy->target[2] = 0xFF;
                enemy->target[3] = 0xFF;
                while(gBattleInfo.player[enemy->target[0]].HP <= 0 && (gBattleInfo.player[0].HP != 0 || gBattleInfo.player[1].HP != 0 || gBattleInfo.player[2].HP != 0 || gBattleInfo.player[3].HP != 0)) {
                    enemy->target[0] = enemy_select_target(enemy->element);
                }
            } else {
                for(i = 0; i < 4; i++) {
                    if(gBattleInfo.player[i].HP > 0 && i <= gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked) {
                        enemy->target[i] = i;
                    } else {
                        enemy->target[i] = 0xFF;
                    }
                }
            }
        }

        cur_obj_find_nearest_object_with_behavior(bhvPsynergy, &dist);
        if(dist < 75.0f) {
            o->oOpacity = 1;
            o->oTimer = 0;
        }
        cur_obj_find_nearest_object_with_behavior(bhvSummonStar, &dist);
        if(dist < 125.0f) {
            o->oOpacity = 1;
            o->oTimer = 0;
        }
        if(o->oOpacity == 1) {
            if(o->oTimer > 30) {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, 0xE000, 0x400);
                if(o->oMoveAngleYaw == -0x2000)
                    o->oOpacity = 0;
            } else {
                o->oMoveAngleYaw += (30 - o->oTimer)*0x180;
            }
        }
        if(o->oVelY != 0.0f || o->oPosY != -11000.0f && turnOrder[gBattleInfo.turnUser] < 4) {
            o->oPosY += o->oVelY;
            o->oVelY -= 2.0f;
            if(o->oPosY <= -11000.0f) {
                o->oPosY = -11000.0f;
                o->oVelY = 0;
            }
        }
    }
}

void bhv_party_member_init(void) {
    o->header.gfx.animInfo.animFrame = random_u16() % (o->header.gfx.animInfo.curAnim->loopEnd - 1);
}

void bhv_party_member_update(void) {
    f32 dist = 0;

    if(gBattleInfo.player[o->oBehParams2ndByte].HP <= 0) {
        cur_obj_init_animation(ANIM_DEATH);
    }

    cur_obj_find_nearest_object_with_behavior(bhvPsynergy, &dist);
        if(dist < 75.0f) {
            o->oOpacity = 1;
            if(o->oTimer > 60)
                o->oTimer = 0;
        }

    else if(o->oOpacity == 1) {
        if(o->oTimer == 0) {
            switch(random_u16() % 5) {
                case 0:
                    cur_obj_play_sound_1(SOUND_MARIO_DOH);
                    break;
                case 1:
                    cur_obj_play_sound_1(SOUND_MARIO_UH);
                    break;
                case 2:
                    cur_obj_play_sound_1(SOUND_MARIO_OOOF);
                    break;
                case 3:
                    cur_obj_play_sound_1(SOUND_MARIO_OOOF);
                    break;
                case 4:
                    cur_obj_play_sound_1(SOUND_MARIO_ATTACKED);
                    break;
            }
        }
        cur_obj_init_animation(ANIM_FALL);
        if(o->header.gfx.animInfo.animFrame == o->header.gfx.animInfo.curAnim->loopEnd - 1) {
            o->oOpacity = 0;
            cur_obj_init_animation(ANIM_IDLE);
        }
    }
}