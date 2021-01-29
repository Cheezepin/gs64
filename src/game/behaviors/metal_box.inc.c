// metal_box.c.inc

struct ObjectHitbox sMetalBoxHitbox = {
    /* interactType: */ 0,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 0,
    /* health: */ 1,
    /* numLootCoins: */ 0,
    /* radius: */ 220,
    /* height: */ 300,
    /* hurtboxRadius: */ 220,
    /* hurtboxHeight: */ 300,
};

s32 check_if_moving_over_floor(f32 a0, f32 a1) {
    struct Surface *sp24;
    f32 sp20 = o->oPosX + sins(o->oMoveAngleYaw) * a1;
    f32 floorHeight;
    f32 sp18 = o->oPosZ + coss(o->oMoveAngleYaw) * a1;
    floorHeight = find_floor(sp20, o->oPosY, sp18, &sp24);
    if (absf(floorHeight - o->oPosY) < a0) // abs
        return 1;
    else
        return 0;
}

void bhv_pushable_loop(void) {
    UNUSED s16 unused;
    s16 sp1C;
    obj_set_hitbox(o, &sMetalBoxHitbox);
    o->oForwardVel = 0.0f;
    if (obj_check_if_collided_with_object(o, gMarioObject) && gMarioStates[0].flags & MARIO_UNKNOWN_31) {
        sp1C = obj_angle_to_object(o, gMarioObject);
        if (abs_angle_diff(sp1C, gMarioObject->oMoveAngleYaw) > 0x4000) {
            o->oMoveAngleYaw = (s16)((gMarioObject->oMoveAngleYaw + 0x2000) & 0xc000);
            if (check_if_moving_over_floor(8.0f, 150.0f)) {
                o->oForwardVel = 4.0f;
                cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
            }
        }
    }
    cur_obj_move_using_fvel_and_gravity();
}

void bhv_icy_block_loop(void) {
    s16 sp1C;
    s32 i;
    f32 xOffset, zOffset;
    struct Object *cringeObj;
    f32 dist;
    obj_set_hitbox(o, &sMetalBoxHitbox);

    switch(o->oAction) {
        case 0:
            o->oForwardVel = 0.0f;
            o->oVelX = 0.0f;
            o->oVelZ = 0.0f;
            if (obj_check_if_collided_with_object(o, gMarioObject) && gMarioStates[0].flags & MARIO_UNKNOWN_31) {
                sp1C = obj_angle_to_object(o, gMarioObject);
                if (abs_angle_diff(sp1C, gMarioObject->oMoveAngleYaw) > 0x4000) {
                    o->oMoveAngleYaw = (s16)((gMarioObject->oMoveAngleYaw + 0x2000) & 0xc000);
                    o->oForwardVel = 25.0f;
                    o->oAction = 1;
                }
            }
            break;
        case 1:
            cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
            o->oWallHitboxRadius = 125.0f;
            if(cur_obj_resolve_wall_collisions()) {
                o->oAction = 0;
            } else {
                cur_obj_move_using_fvel_and_gravity();
            }
            break;
    }

    i = 0;
    for(xOffset = -110.0f; xOffset <= 110; xOffset += 220) {
        for(zOffset = -110.0f; zOffset <= 110; zOffset += 220) {
            if(find_floor_height(o->oPosX + xOffset, o->oPosY, o->oPosZ + zOffset) >= o->oPosY) {
                i = 1;
            }
        }
    }
    if(i == 0) {
        o->oPosY -= 25.0f;
        cringeObj = cur_obj_find_nearest_object_with_behavior(bhvLighthouseGate, &dist);
        if(cringeObj != 0) {
            cringeObj->oAction = 1;
        }
    }
}