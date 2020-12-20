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

#define MENU_NONE     0
#define MENU_START    1
#define MENU_FIGHT    2
#define MENU_ATTACK   3
#define MENU_TURN     4
#define MENU_WIN      5
#define MENU_PSYNERGY 6

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

#define MARS    0
#define VENUS   1
#define JUPITER 2
#define MERCURY 3

#define SPELL_LIFT         0 //field only
#define SPELL_MOVE         1 //field only
#define SPELL_GUARD        2
#define SPELL_PROTECT      3
#define SPELL_FLARE        4
#define SPELL_FLARE_WALL   5
#define SPELL_FLARE_STORM  6
#define SPELL_VOLCANO      7
#define SPELL_GROWTH       8 //field + battle
#define SPELL_QUAKE        9
#define SPELL_EARTHQUAKE   10
#define SPELL_QUAKE_SPHERE 11
#define SPELL_SPIRE        12
#define SPELL_WHIRLWIND    13 //field + battle
#define SPELL_TORNADO      14
#define SPELL_IMPACT       15
#define SPELL_HIGH_IMPACT  16
#define SPELL_REVIVE       17 //field + battle
#define SPELL_FROST        18 //field + battle
#define SPELL_TUNDRA       19
#define SPELL_GLACIER      20
#define SPELL_PLY          21 //field + battle
#define SPELL_PLY_WELL     22 //field + battle
#define SPELL_WISH         23 //field + battle

#define SPELL_NONE        255

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
    u8 turnUser; //when fighting
    u8 turnActionProgress;
    u8 camState;
    u8 selectedUser; //when in menus
    u8 lastSeq;
    s8 turnOrder[7];
    struct Enemy enemy[3];
    struct BattlePlayer player[4];
};

struct Spell
{
    const char name[12];
    const char tooltip[32];
    u8 sprite;
    u8 damage;
    u8 baseLevel;
    u8 PP;
};

//extern u8 MarsPool[7];
extern u8 VenusPool[6];
extern u8 JupiterPool[6];
extern u8 MercuryPool[8];
//extern u32 SpellPool[4];

#endif

extern struct BattleInfo gBattleInfo;

void initialize_battle(void);
void render_battle(void);