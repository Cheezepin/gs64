#include "src/game/battle_helpers.h"
#include "src/game/object_list_processor.h"
#include "src/audio/external.h"
#include "src/game/hud.h"

extern u8 gCharactersUnlocked;

f32 dist2lol = 0.0f;
void bhv_liftrock_update(void) {
    struct Object *sparkle;
    if(o->oTimer % 3 == 0 && o->oBehParams2ndByte == 1) {
        sparkle = spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
        sparkle->oPosY += 250.0f;
    }
    if(o->behavior == segmented_to_virtual(bhvFrostSpire)) {
        struct Object *affectedObj;
        affectedObj = cur_obj_find_nearest_object_with_behavior(bhvPuddle, &dist2lol);
        if(affectedObj != 0 && dist2lol < 100.0f) {
            affectedObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    }
}

u8 fanfarePlayed;
void bhv_character_pickup_update(void) {
    if(gCharactersUnlocked >= o->oBehParams2ndByte) {
        fanfarePlayed = 0;
        return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
    if(o->oBehParams2ndByte == 3) {
        cur_obj_init_animation(ANIM_DEATH);
    }
     if(o->oOpacity == 3) {
    //     gCharactersUnlocked = gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked = o->oBehParams2ndByte;
    //     fanfarePlayed = 0;
    //     return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        o->oOpacity = 4;
     }
    if(o->oDistanceToMario < 100.0f && o->oOpacity != 4) {
        o->oOpacity = cur_obj_update_dialog(2, 2, o->oBehParams2ndByte, 0);
        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x800);
    }
    if(o->oOpacity == 4) {
        if(fanfarePlayed == 0) {
            play_peachs_jingle();
            fanfarePlayed = 1;
            set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
            gPartyMemberGot = o->oBehParams2ndByte;
        }
        if(o->oTimer > 90 && gPlayer1Controller->buttonPressed & A_BUTTON) {
            gCharactersUnlocked = gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked = o->oBehParams2ndByte;
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[o->oBehParams2ndByte].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[o->oBehParams2ndByte].baseHP;
            gPartyMemberGot = 0;
            fanfarePlayed = 0;
            spawn_object(gCurrentObject, 0, bhvSparkleSpawn);
            set_mario_action(gMarioState, ACT_IDLE, 0);
            return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    } else {
        o->oTimer = 0;
    }
}

void bhv_tornado_init(void) {
    o->oPosX += 750.0f;
    o->oPosZ += 750.0f;
    cur_obj_scale(0.0f);
}

void bhv_tornado_update(void) {
    o->oFaceAnglePitch = o->oFaceAngleRoll = 0;
    if(o->oTimer < 30) {
        o->oPosX -= 25.0f;
        o->oPosZ -= 25.0f;
        o->oMoveAngleYaw += 0x3241;
        if(o->header.gfx.scale[0] < 1.0f) {
            o->header.gfx.scale[2] = o->header.gfx.scale[1] = o->header.gfx.scale[0] = o->header.gfx.scale[0] + 0.125f;
        }
    } else {
        if(o->header.gfx.scale[0] > 0.0f) {
            o->header.gfx.scale[2] = o->header.gfx.scale[1] = o->header.gfx.scale[0] = o->header.gfx.scale[0] - 0.0625f;
        } else {
            return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    }
}

void bhv_leaf_update(void) {
    struct Object *sparkle;
    if(o->oBehParams2ndByte != 0) {
        if(o->oTimer % 3 == 0 && o->oBehParams2ndByte == 1) {
            sparkle = spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            sparkle->oPosY += 250.0f;
        }
        if(o->oTimer > 30) {
            o->oForwardVel = 2.0f*(o->oTimer - 30);
            cur_obj_move_xz_using_fvel_and_yaw();
            if(o->header.gfx.scale[0] > 0.0f) {
                o->header.gfx.scale[2] = o->header.gfx.scale[1] = o->header.gfx.scale[0] = o->header.gfx.scale[0] - 0.0625f;
                o->oPosY += 10.0f;
            } else {
                return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
        }
    } else {
        o->oTimer = 0;
    }
}

void bhv_generic_psynergy_update(void) {
    u8 i;
    switch(o->oBehParams2ndByte) {
        case SPELL_WHIRLWIND:
        case SPELL_TORNADO:
            cur_obj_play_sound_1(SOUND_ENV_WIND1);
            if(o->oTimer < 45) {
                o->oPosX += 25.0f;
                o->oPosZ += 25.0f;
            } else {
                if(o->header.gfx.scale[0] > 0.0f) {
                    o->header.gfx.scale[2] = o->header.gfx.scale[1] = o->header.gfx.scale[0] = o->header.gfx.scale[0] - 0.0625f;
                } else {
                    return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                }
            }
            o->oFaceAngleYaw += 0x3241;
            break;
        case SPELL_GROWTH:
        case SPELL_SPIRE:
            cur_obj_shake_screen(SHAKE_FOV_MEDIUM);
            cur_obj_play_sound_1(SOUND_GENERAL_GRINDEL_ROLL);
            o->oPosX = o->oHomeX + (((f32)((s16)random_u16())) / 2000.0f);
            o->oPosZ = o->oHomeZ + (((f32)((s16)random_u16())) / 2000.0f);
            if(o->oTimer > 15 && o->oTimer < 25) {
                o->oPosY += 50.0f;
            }
            if(o->oTimer > 35) {
                o->oPosY -= 15.0f;
            }
            if(o->oTimer > 60) {
                return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
        case SPELL_FLARE:
            cur_obj_play_sound_1(SOUND_MOVING_LAVA_BURN);
            o->oPosX += 50.0f;
            o->oPosZ += 50.0f;
            if(o->oTimer % 2 == 0) {
                o->oAnimState = (o->oAnimState + 1) % 8;
            }
            if(o->oTimer > 45) {
                return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
        case SPELL_VOLCANO:
            cur_obj_play_sound_1(SOUND_MOVING_LAVA_BURN);
            o->oPosY += 50.0f;
            if(o->oTimer > 30) {
                return o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
        case SPELL_FROST:
        case SPELL_TUNDRA:
        case SPELL_GLACIER:
            if(o->oTimer < 20) {
                o->oPosY += o->header.gfx.scale[1]*60.0f;
                cur_obj_shake_screen(o->oBehParams2ndByte - 17);
                cur_obj_play_sound_1(SOUND_GENERAL_GRINDEL_ROLL);
                o->oPosX = o->oHomeX + (((f32)((s16)random_u16())) / 2000.0f);
                o->oPosZ = o->oHomeZ + (((f32)((s16)random_u16())) / 2000.0f);
            }
            if(o->oTimer == 40) {
                struct Object *targetObj = gBattleInfo.enemy[o->oOpacity].obj;
                struct Object *explosion;
                explosion = spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
                explosion->oGraphYOffset += 100.0f;
                if(o->oBehParams2ndByte == SPELL_FROST) {
                    targetObj->oOpacity = 1;
                    targetObj->oTimer = 0;
                } else {
                    for(i = 0; i < 3; i++) {
                        targetObj = gBattleInfo.enemy[i].obj;
                        if(targetObj != 0) {
                            targetObj->oOpacity = 1;
                            targetObj->oTimer = 0;
                        }
                    }
                }
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
        case SPELL_QUAKE:
        case SPELL_EARTHQUAKE:
        case SPELL_QUAKE_SPHERE:
            cur_obj_shake_screen(o->oBehParams2ndByte - 8);
            cur_obj_play_sound_1(SOUND_GENERAL_GRINDEL_ROLL);
            o->oPosY += o->oVelY;
            o->oVelY -= 2.0f;
            if(o->oPosY < -11000.0f) {
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}

void bhv_boss_update(void) {
    if(o->oOpacity == 3) {
        set_mario_action(gMarioState, ACT_BATTLE, 0);
        gBattleInfo.lastPos[0] = gBattleInfo.lastPos[2] = 0;
    }
    if(o->oDistanceToMario < 500.0f) {
        o->oOpacity = cur_obj_update_dialog(2, 2, 17 + o->oBehParams2ndByte, 0);
        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x400);
    }
}

void bhv_chest_update(void) {
    u8 i;
    if(lateral_dist_between_objects(o, gMarioObject) <= 200.0f && (gMarioState->action & 0x600 != 0 || gMarioState->action == ACT_PUNCHING) && gMarioState->action != ACT_BATTLE && gMarioState->action != ACT_PSYNERGYF && gPlayer1Controller->buttonPressed & B_BUTTON && (gSaveBuffer.files[gCurrSaveFileNum - 1][0].chestIndex & (1 << (o->oBehParams >> 24))) == 0 && (((o->oAngleToMario- o->oFaceAngleYaw) & 0xFFFF) > 0xE000 || ((o->oAngleToMario- o->oFaceAngleYaw) & 0xFFFF) < 0x2000) && (((gMarioState->faceAngle[1] - o->oFaceAngleYaw) & 0xFFFF) < 0xC000 && ((gMarioState->faceAngle[1] - o->oFaceAngleYaw) & 0xFFFF) > 0x4000)) {
        gMarioState->usedObj = o;
        gSaveBuffer.files[gCurrSaveFileNum - 1][0].chestIndex |= (1 << (o->oBehParams >> 24));
        gScreenX = 0xFFFF0000;
        set_mario_action(gMarioState, ACT_UNLOCKING_CHEST, o->oBehParams2ndByte + 1);
        for(i = 0; i < 16; i++) {
            if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].id == o->oBehParams2ndByte) {
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].number++;
                i = 16;
            } else if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].id == 0xFF) {
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].id = o->oBehParams2ndByte;
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].number = 1;
                i = 16;
            }
            update_inventory();
        }
        cur_obj_init_animation(0);
    }
    if((gSaveBuffer.files[gCurrSaveFileNum - 1][0].chestIndex & (1 << (o->oBehParams >> 24))) != 0) {
        cur_obj_init_animation(0);
    }
    cur_obj_push_mario_away_from_cylinder(150.0f, 150.0f);
}

void bhv_summon_star_update(void) {
    o->oMoveAngleYaw += 0x1000;
    if((o->oBehParams & 0xFF) == 0) {
        if(o->oTimer < 15) {
            o->oPosY -= (f32)(15 - o->oTimer) * 5.0f;
            o->oPosX += 25.0f;
            o->oPosZ -= 25.0f;
        }
        if(o->oTimer > 75) {
            o->oPosY += (f32)(o->oTimer - 74) * 5.0f;
            o->oPosX -= 25.0f;
            o->oPosZ += 25.0f;
        }
        if(o->oTimer == 90) {
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
        o->oMoveAngleYaw += 0x1800;
    } else {
        o->oPosY += (5.0f + (f32)(o->oTimer*8));
        if(o->oTimer == 90) {
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    }
}

void bhv_lighthouse_gate_update(void) {
    if(o->oAction != 0) {
        o->oPosY += 10.0f;
    }
}