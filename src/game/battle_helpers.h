#include <PR/ultratypes.h>
#include <PR/gbi.h>

#define OVER_FIGHT    0
#define OVER_FLEE     1
#define OVER_STATUS   2
#define OVER_ATTACK   3
#define OVER_PSYNERGY 4
#define OVER_DJINN    5
#define OVER_SUMMON   6
#define OVER_ITEM     7
#define OVER_DEFEND   8

#define MENU_NONE   0
#define MENU_START  1
#define MENU_FIGHT  2
#define MENU_ATTACK 3
#define MENU_TURN   4
#define MENU_WIN    5

#define SHADOW    0
#define NO_SHADOW 1

#define ENEMY_GOOMBA 0
#define ENEMY_BOBOMB 1
#define ENEMY_WHOMP  2
#define ENEMY_THWOMP 3

#define CAMERA_SIDE 0
#define CAMERA_BACK 1

#define ACT_ATTACK   0
#define ACT_PSYNERGY 1

#define TURN_PLAYER1 0
#define TURN_PLAYER2 1
#define TURN_PLAYER3 2
#define TURN_PLAYER4 3
#define TURN_ENEMY1  4
#define TURN_ENEMY2  5
#define TURN_ENEMY3  6

#ifndef BATTLE_HELPERS_H
#define BATTLE_HELPERS_H

struct Enemy
{
    struct Object *obj;
    u8 id;
    u8 element;
    u16 baseHP;
    s16 HP;
    u8 attack;
    u8 defense;
    u8 agility;
    const char name[16];
    u8 action;
    u8 subAction;
    u8 actionProgressMax;
    u8 target;
};

struct BattlePlayer
{
    struct Object *obj;
    u16 baseHP;
    s16 HP;
    u16 basePP;
    s16 PP;
    s16 baseAttack;
    s16 attack;
    u8 ttAttackR; //turns till attack revert
    s16 baseDefense;
    s16 defense;
    u8 ttDefenseR;
    s16 baseAgility;
    s16 agility;
    u8 ttAgilityR;
    u8 element;
    u8 action;
    u8 subAction;
    u8 target;
    u8 actionProgressMax;
};

struct BattleInfo
{
    Vec3f lastPos;
    u32 turn;
    u8 turnUser;
    u8 turnActionProgress;
    u8 camState;
    u8 currentUser;
    u8 selectedUser;
    s8 turnOrder[7];
    struct Enemy enemy[3];
    struct BattlePlayer player[4];
};

#endif

extern struct BattleInfo gBattleInfo;

void initialize_battle(void);
void render_battle(void);