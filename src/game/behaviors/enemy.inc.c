#include "src/game/battle_helpers.h"

void bhv_enemy_init(void) {
    struct Enemy *enemy = &gBattleInfo.enemy[o->oBehParams2ndByte];
    o->oPosY = -11000.0f;
    o->oMoveAngleYaw = 0xE000;
    switch(o->oBehParams2ndByte) {
        case 0:
            o->oPosX = 375.0f + (125.0f*o->oBehParams2ndByte);
            o->oPosZ = -375.0f - (125.0f*o->oBehParams2ndByte);
            break;
    }
    switch(gBattleInfo.enemy[o->oBehParams2ndByte].id) {
        case ENEMY_GOOMBA:
            enemy->HP = enemy->baseHP = 15 + (random_u16() % 5);
            enemy->agility = 3;
            enemy->attack = 2;
            enemy->defense = 3;
            sprintf(enemy->name, "Goomba");
            o->oAnimations = goomba_seg8_anims_0801DA4C;
            cur_obj_init_animation(0);
            break;
    }
}

void bhv_enemy_update(void) {
    struct Enemy *enemy = &gBattleInfo.enemy[o->oBehParams2ndByte];
    enemy->target = 0;
}