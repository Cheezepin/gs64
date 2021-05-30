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

#define MENU_NONE           0
#define MENU_START          1
#define MENU_FIGHT          2
#define MENU_ATTACK         3
#define MENU_TURN           4
#define MENU_WIN            5
#define MENU_PSYNERGY       6
#define MENU_SELECT         7
#define MENU_PAUSE          8
#define MENU_STATUS         9
#define MENU_FIELD_PSYNERGY 10
#define MENU_LOSE           11
#define MENU_ITEM           12
#define MENU_FIELD_ITEM     13
#define MENU_DJINN          14
#define MENU_SUMMON         15
#define MENU_MESSAGES       16
#define MENU_FLEE           17
#define MENU_PASSWORD       18

#define PMENU_ICONS    0
#define PMENU_PSYNERGY 1
#define PMENU_DJINN    2
#define PMENU_ITEM     3
#define PMENU_STATUS   4
#define PMENU_NONE  0xFF

#define SHADOW    0
#define NO_SHADOW 1

#define ENEMY_NONE         0
#define ENEMY_GOOMBA       1
#define ENEMY_BOBOMB       2
#define ENEMY_WHOMP        3
#define ENEMY_THWOMP       4
#define ENEMY_CHUCKYA      5
#define ENEMY_BULLY        6
#define ENEMY_AMP          7
#define ENEMY_KOOPA        8
#define ENEMY_PIRANHA      9
#define ENEMY_SCUTTLEBUG  10
#define ENEMY_KING_BOBOMB 11
#define ENEMY_PORKY       12

#define CAMERA_SIDE   0
#define CAMERA_BACK   1
#define CAMERA_ACTION 2

#define ACT_ATTACK   0
#define ACT_PSYNERGY 1
#define ACT_DEFEND   2
#define ACT_ITEM     3
#define ACT_DJINN    4
#define ACT_SUMMON   5

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

#define DJINN_ATKDOWN     0
#define DJINN_DEFDOWN     1
#define DJINN_AGIUP       2
#define DJINN_PPUP        3

#define DJINN_ACTIVE   0
#define DJINN_INACTIVE 1

#define SUMMON_MARS    0
#define SUMMON_VENUS   1
#define SUMMON_JUPITER 2
#define SUMMON_MERCURY 3

#define PLY_HEALTH_RECOVERED       15
#define PLY_WELL_HEALTH_RECOVERED  35
#define WISH_HEALTH_RECOVERED      30

#define HERB_HEALTH_RECOVERED 25
#define CORN_HEALTH_RECOVERED 50
#define NUT_HEALTH_RECOVERED 150

#define RANGE_SINGLE_ENEMY 0
#define RANGE_ALL_ENEMIES  1
#define RANGE_SINGLE_PARTY 2
#define RANGE_ALL_PARTY    3

#define ANIM_IDLE  0
#define ANIM_JUMP  1
#define ANIM_FALL  2
#define ANIM_DEATH 3

#define ATTACK_ANIM 0

#define WHITE  0
#define YELLOW 1
#define RED    2

#define ITEM_HERB           0
#define ITEM_CORN           1
#define ITEM_NUT            2
#define ITEM_PSY_CRYSTAL    3
#define ITEM_SACRED_FEATHER 4
#define ITEM_WATER_OF_LIFE  5

#define MSG_DJINN_SET  1
#define MSG_ATK_REVERT 2
#define MSG_DEF_REVERT 3
#define MSG_AGI_REVERT 4

#define BOSS_KING_BOBOMB 0x1
#define BOSS_PORKY       0x2

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
    u8 target[4];
    u16 expYield;
    u8 psynergyChance;
};

struct BattlePlayer
{
    struct Object *obj;
    u16 trueBaseHP;
    u16 baseHP;
    s16 HP;
    u16 trueBasePP;
    u16 basePP;
    s16 PP;
    s16 baseAttack;
    s16 attack;
    u8 ttAttackR; //turns till attack revert
    s8 attackOffset;
    s16 baseDefense;
    s16 defense;
    u8 ttDefenseR;
    s8 defenseOffset;
    s16 baseAgility;
    s16 agility;
    u8 ttAgilityR;
    s8 agilityOffset;
    u8 element;
    u8 action;
    u8 subAction;
    u8 target[3];
    u8 actionProgressMax;
};

struct BattleInfo
{
    Vec3f lastPos;
    Vec3f lastCamPos;
    u32 turn;
    u8 turnUser; //when fighting
    u8 turnActionProgress;
    u8 camState;
    u8 selectingUser; //when in menus
    u8 lastSeq;
    u8 prevMenu;
    u8 totalEnemies;
    s8 turnOrder[7];
    u16 exitTimer;
    u8 camFocus;
    u8 djinnUsed[4];
    struct Enemy enemy[3];
    struct BattlePlayer player[4];
};

struct Spell
{
    const char name[15];
    const char tooltip[36];
    u8 sprite;
    u8 damage;
    u8 baseLevel;
    u8 PP;
    u8 range;
};

struct Djinni
{
    const char name[8];
    const char tooltip[32];
    u8 id;
    u8 element;
    u8 range;
};

struct Summon
{
    const char name[8];
    const char tooltip[32];
    u8 elements[4]; //each byte--mars, venus, jupiter, mercury--has # of djinn required to summon for each
    u8 id;
    u8 element;
    u8 damage;
    u8 range;
};

#endif

extern struct BattleInfo gBattleInfo;
extern u8 menuState;
extern u8 barsRendered;

void initialize_battle(void);
void render_battle(void);
void render_item_got(u8 itemGot);
void render_party_member_got(u8 partyMemberGot);
void print_field_psynergy(u8 spell);
void render_password_screen(void);
void render_credits(void);