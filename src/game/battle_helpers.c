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
#include "actors/group0.h"
#include "src/engine/math_util.h"
#include "mario.h"

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
#include "src/s2d_engine/icons/portraits.c"
#include "src/s2d_engine/icons/portraits.h"
#include "src/s2d_engine/icons/players.c"
#include "src/s2d_engine/icons/players.h"
#include "src/s2d_engine/icons/items.c"
#include "src/s2d_engine/icons/items.h"
#include "src/s2d_engine/icons/djinn.c"
#include "src/s2d_engine/icons/djinn.h"
#include "src/s2d_engine/icons/stats.c"
#include "src/s2d_engine/icons/stats.h"

extern u32 gGetScreenCoords;
extern Vec3f g3DtoScreenCoords;
extern u32 gScreenX;
extern u32 gScreenY;

extern s16 gCutsceneTimer;

struct BattleInfo gBattleInfo;

extern struct SaveBuffer gSaveBuffer;

extern s16 gMenuMode;
extern s16 gPauseScreenMode;

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
    1,
    3,
    RANGE_SINGLE_PARTY,
};

struct Spell Protect = {
    "Protect",
    "Boost party's Defense.",
    SPELL_PROTECT,
    5,
    6,
    8,
    RANGE_ALL_PARTY,
};

struct Spell Flare = {
    "Flare",
    "Attack with flaring flames.",
    SPELL_FLARE,
    3,
    0,
    4,
    RANGE_ALL_ENEMIES,
};

struct Spell FlareWall = {
    "Flare Wall",
    "Attack with searing flames.",
    SPELL_FLARE_WALL,
    6,
    4,
    8,
    RANGE_ALL_ENEMIES,
};

struct Spell FlareStorm = {
    "Flare Storm",
    "Attack with incinerating flames.",
    SPELL_FLARE_STORM,
    10,
    10,
    12,
    RANGE_ALL_ENEMIES,
};

struct Spell Volcano = {
    "Volcano",
    "Attack with volcanic might.",
    SPELL_VOLCANO,
    8,
    8,
    6,
    RANGE_SINGLE_ENEMY,
};

struct Spell Growth = {
    "Growth",
    "Attack with wild plants.",
    SPELL_GROWTH,
    6,
    0,
    3,
    RANGE_SINGLE_ENEMY,
};

struct Spell Quake = {
    "Quake",
    "Attack with a powerful quake.",
    SPELL_QUAKE,
    4,
    0,
    5,
    RANGE_ALL_ENEMIES,
};

struct Spell Earthquake = {
    "Earthquake",
    "Attack with a mighty tremor.",
    SPELL_EARTHQUAKE,
    8,
    6,
    10,
    RANGE_ALL_ENEMIES,
};

struct Spell QuakeSphere = {
    "Quake Sphere",
    "Attack with a massive quake.",
    SPELL_QUAKE_SPHERE,
    15,
    11,
    22,
    RANGE_ALL_ENEMIES,
};

struct Spell Spire = {
    "Spire",
    "Attack with an earthen spire.",
    SPELL_SPIRE,
    12,
    8,
    15,
    RANGE_SINGLE_ENEMY,
};

struct Spell Whirlwind = {
    "Whirlwind",
    "Attack with a swirling tornado.",
    SPELL_WHIRLWIND,
    4,
    0,
    3,
    RANGE_ALL_ENEMIES,
};

struct Spell Tornado = {
    "Tornado",
    "Attack with a mighty tornado.",
    SPELL_TORNADO,
    12,
    6,
    10,
    RANGE_ALL_ENEMIES,
};

struct Spell Impact = {
    "Impact",
    "Boost ally's attack.",
    SPELL_IMPACT,
    0,
    2,
    3,
    RANGE_SINGLE_PARTY,
};

struct Spell HighImpact = {
    "High Impact",
    "Boost party's attack.",
    SPELL_HIGH_IMPACT,
    0,
    9,
    8,
    RANGE_ALL_PARTY,
};

struct Spell Revive = {
    "Revive",
    "Revive a downed ally.",
    SPELL_REVIVE,
    0,
    4,
    20,
    RANGE_SINGLE_PARTY,
};

struct Spell Frost = {
    "Frost",
    "Attack with icy blasts.",
    SPELL_FROST,
    3,
    0,
    3,
    RANGE_SINGLE_ENEMY,
};

struct Spell Tundra = {
    "Tundra",
    "Attack with frigid blasts.",
    SPELL_TUNDRA,
    6,
    4,
    8,
    RANGE_ALL_ENEMIES,
};

struct Spell Glacier = {
    "Glacier",
    "Attack with subzero blasts.",
    SPELL_GLACIER,
    10,
    10,
    12,
    RANGE_ALL_ENEMIES,
};

struct Spell Ply = {
    "Ply",
    "Restore 50 HP with faith's power.",
    SPELL_PLY,
    50,
    2,
    7,
    RANGE_SINGLE_PARTY,
};

struct Spell PlyWell = {
    "Ply Well",
    "Restore 150 HP with faith's power.",
    SPELL_PLY_WELL,
    150,
    6,
    12,
    RANGE_SINGLE_PARTY,
};

struct Spell Wish = {
    "Wish",
    "Restore 80 HP to the whole party.",
    SPELL_WISH,
    80,
    8,
    15,
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

struct Spell *BobombPool[4] = {
    &Flare,
    &None,
    &None,
    &None,
};

struct Spell **EnemySpellPool[12] = {
    0,
    0,              //goomba
    &BobombPool,    //bobomb
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

struct Spell Lift = {
    "Lift",
    "Lift a nearby object.",
    SPELL_LIFT,
    0,
    0,
    1,
    RANGE_SINGLE_ENEMY,
};

struct Spell Move = {
    "Move",
    "Move a nearby object.",
    SPELL_MOVE,
    0,
    0,
    1,
    RANGE_SINGLE_ENEMY,
};

struct Spell *MarsFieldPool[2] = {
    &Lift,
    //&Move,
    &None,
};

struct Spell *VenusFieldPool[2] = {
    //&Move,
    &Growth,
    &None,
};

struct Spell *JupiterFieldPool[3] = {
    &Whirlwind,
    &Revive,
    &None,
};

struct Spell *MercuryFieldPool[5] = {
    &Frost,
    &Ply,
    &PlyWell,
    &Wish,
    &None,
};

struct Spell **FieldSpellPool[4] = {
    &MarsFieldPool,
    &VenusFieldPool,
    &JupiterFieldPool,
    &MercuryFieldPool,
};

struct Djinni DjinnAtkDown = {
    "Bonfire",
    "Burn away an enemy's attack.",
    DJINN_ATKDOWN,
    MARS,
    RANGE_SINGLE_ENEMY,
};

struct Djinni DjinnDefDown = {
    "Clay",
    "Tear down an enemy's defense.",
    DJINN_DEFDOWN,
    VENUS,
    RANGE_SINGLE_ENEMY,
};

struct Djinni DjinnAgiUp = {
    "Monsoon",
    "Speed up using the winds.",
    DJINN_AGIUP,
    JUPITER,
    RANGE_SINGLE_PARTY,
};

struct Djinni DjinnPPUp = {
    "Puddle",
    "Recover some PP.",
    DJINN_PPUP,
    MERCURY,
    RANGE_SINGLE_PARTY,
};

struct Djinni *djinniPool[4] = {
    &DjinnAtkDown,
    &DjinnDefDown,
    &DjinnAgiUp,
    &DjinnPPUp,
};

struct Summon MarsSummon = {
    "Mars",
    "The elemental power of fire.",
    1, 0, 0, 0,
    SUMMON_MARS,
    MARS,
    4,
    RANGE_ALL_ENEMIES,
};

struct Summon VenusSummon = {
    "Venus",
    "The elemental power of earth.",
    0, 1, 0, 0,
    SUMMON_VENUS,
    VENUS,
    4,
    RANGE_ALL_ENEMIES,
};

struct Summon JupiterSummon = {
    "Jupiter",
    "The elemental power of wind.",
    0, 0, 1, 0,
    SUMMON_JUPITER,
    JUPITER,
    4,
    RANGE_ALL_ENEMIES,
};

struct Summon MercurySummon = {
    "Mercury",
    "The elemental power of water.",
    0, 0, 0, 1,
    SUMMON_MERCURY,
    MERCURY,
    4,
    RANGE_ALL_ENEMIES,
};

struct Summon *summonPool[4] = {
    &MarsSummon,
    &VenusSummon,
    &JupiterSummon,
    &MercurySummon,
};

#define GRASS_POOL_MAX 9
u8 GrassEnemyPool[GRASS_POOL_MAX][3] = {
    ENEMY_GOOMBA,  ENEMY_GOOMBA,  ENEMY_NONE,
    ENEMY_GOOMBA,  ENEMY_GOOMBA,  ENEMY_GOOMBA,
    ENEMY_BOBOMB,  ENEMY_BOBOMB,  ENEMY_NONE, 
    ENEMY_BOBOMB,  ENEMY_BOBOMB,  ENEMY_BOBOMB,
    ENEMY_GOOMBA,  ENEMY_BOBOMB,  ENEMY_GOOMBA,
    ENEMY_BOBOMB,  ENEMY_GOOMBA,  ENEMY_BOBOMB,
    ENEMY_BOBOMB,  ENEMY_GOOMBA,  ENEMY_GOOMBA,
    ENEMY_GOOMBA,  ENEMY_CHUCKYA, ENEMY_NONE,
    ENEMY_GOOMBA,  ENEMY_CHUCKYA, ENEMY_GOOMBA,
};

#define AREA_1_POOL_MAX 5 //chuckya, amp, whomp
u8 Area1EnemyPool[AREA_1_POOL_MAX][3] = {
    ENEMY_AMP,     ENEMY_AMP,     ENEMY_AMP,
    //ENEMY_AMP,     ENEMY_THWOMP,  ENEMY_AMP,
    ENEMY_AMP,     ENEMY_WHOMP,   ENEMY_AMP,
    ENEMY_WHOMP,   ENEMY_AMP,     ENEMY_WHOMP,
    ENEMY_WHOMP,   ENEMY_AMP,     ENEMY_CHUCKYA,
    ENEMY_CHUCKYA, ENEMY_WHOMP,   ENEMY_CHUCKYA,
    //ENEMY_THWOMP,  ENEMY_NONE,    ENEMY_NONE,
};

#define AREA_2_POOL_MAX 8 //amp, whomp, thwomp, koopa
u8 Area2EnemyPool[AREA_2_POOL_MAX][3] = {
    ENEMY_AMP,     ENEMY_THWOMP,  ENEMY_AMP,
    ENEMY_AMP,     ENEMY_WHOMP,   ENEMY_AMP,
    ENEMY_WHOMP,   ENEMY_AMP,     ENEMY_WHOMP,
    ENEMY_WHOMP,   ENEMY_AMP,     ENEMY_THWOMP,
    ENEMY_WHOMP,   ENEMY_THWOMP,  ENEMY_NONE,
    ENEMY_KOOPA,   ENEMY_WHOMP,   ENEMY_KOOPA,
    ENEMY_KOOPA,   ENEMY_THWOMP,  ENEMY_KOOPA,
    ENEMY_KOOPA,   ENEMY_KOOPA,   ENEMY_KOOPA,
};

#define AREA_3_POOL_MAX 7 //whomp, thwomp, koopa, bully
u8 Area3EnemyPool[AREA_3_POOL_MAX][3] = {
    ENEMY_WHOMP,   ENEMY_THWOMP,  ENEMY_WHOMP,
    ENEMY_KOOPA,   ENEMY_WHOMP,   ENEMY_KOOPA,
    ENEMY_KOOPA,   ENEMY_THWOMP,  ENEMY_KOOPA,
    ENEMY_KOOPA,   ENEMY_KOOPA,   ENEMY_KOOPA,
    ENEMY_KOOPA,   ENEMY_BULLY,   ENEMY_KOOPA,
    ENEMY_BULLY,   ENEMY_WHOMP,   ENEMY_KOOPA,
    ENEMY_BULLY,   ENEMY_THWOMP,  ENEMY_BULLY,
};

#define AREA_4_POOL_MAX 8 //bully, thwomp, koopa, scuttle
u8 Area4EnemyPool[AREA_4_POOL_MAX][3] = {
    ENEMY_BULLY,   ENEMY_THWOMP,  ENEMY_BULLY,
    ENEMY_KOOPA,   ENEMY_THWOMP,  ENEMY_KOOPA,
    ENEMY_KOOPA,   ENEMY_KOOPA,   ENEMY_KOOPA,
    ENEMY_KOOPA,   ENEMY_BULLY,   ENEMY_KOOPA,
    ENEMY_BULLY,   ENEMY_THWOMP,  ENEMY_KOOPA,
    ENEMY_SCUTTLEBUG, ENEMY_THWOMP,  ENEMY_SCUTTLEBUG,
    ENEMY_SCUTTLEBUG, ENEMY_BULLY,  ENEMY_SCUTTLEBUG,
    ENEMY_BULLY,   ENEMY_SCUTTLEBUG, ENEMY_BULLY,
};

#define AREA_5_POOL_MAX 8 //whomp, thwomp, scuttle, piranha
u8 Area5EnemyPool[AREA_5_POOL_MAX][3] = {
    ENEMY_WHOMP,   ENEMY_THWOMP,  ENEMY_WHOMP,
    ENEMY_WHOMP,   ENEMY_PIRANHA, ENEMY_WHOMP,
    ENEMY_PIRANHA, ENEMY_WHOMP,   ENEMY_PIRANHA,
    ENEMY_SCUTTLEBUG, ENEMY_WHOMP, ENEMY_SCUTTLEBUG,
    ENEMY_PIRANHA, ENEMY_SCUTTLEBUG, ENEMY_PIRANHA,
    ENEMY_SCUTTLEBUG, ENEMY_PIRANHA, ENEMY_SCUTTLEBUG,
    ENEMY_THWOMP, ENEMY_PIRANHA, ENEMY_THWOMP,
    ENEMY_PIRANHA, ENEMY_PIRANHA, ENEMY_PIRANHA,
};

#define AREA_6_POOL_MAX 1
u8 Area6EnemyPool[AREA_6_POOL_MAX][3] = {
    ENEMY_KING_BOBOMB, ENEMY_NONE, ENEMY_NONE,
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

void call_portrait_sprite_dl(int idx, int x, int y, uObjMtx *buffer) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gDPSetTextureLUT(gDisplayListHead++, G_TT_RGBA16);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &portrait_tex[idx]);
	gSPObjLoadTxtr(gDisplayListHead++, &portrait_pal_TLUT[idx]);
	setup_mtx(&buffer[0], x, y, 1);
	gSPObjMatrix(gDisplayListHead++, &buffer[0]);
	gSPObjSprite(gDisplayListHead++, &portrait_obj);
}

void call_player_icon_sprite_dl(int idx, int x, int y, uObjMtx *buffer) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gDPSetTextureLUT(gDisplayListHead++, G_TT_RGBA16);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &player_icon_tex[idx]);
	gSPObjLoadTxtr(gDisplayListHead++, &player_icon_pal_TLUT[idx]);
	setup_mtx(&buffer[0], x, y, 1);
	gSPObjMatrix(gDisplayListHead++, &buffer[0]);
	gSPObjSprite(gDisplayListHead++, &player_icon_obj);
}

void call_djinn_sprite_dl(int idx, int x, int y, uObjMtx *buffer) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gDPSetTextureLUT(gDisplayListHead++, G_TT_RGBA16);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &djinn_tex[idx]);
	gSPObjLoadTxtr(gDisplayListHead++, &djinn_pal_TLUT[idx]);
	setup_mtx(&buffer[0], x, y, 1);
	gSPObjMatrix(gDisplayListHead++, &buffer[0]);
	gSPObjSprite(gDisplayListHead++, &djinn_obj);
}

void call_stats_sprite_dl(int idx, int x, int y, uObjMtx *buffer) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gDPSetTextureLUT(gDisplayListHead++, G_TT_RGBA16);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &stats_tex[idx]);
	gSPObjLoadTxtr(gDisplayListHead++, &stats_pal_TLUT[idx]);
	setup_mtx(&buffer[0], x, y, 1);
	gSPObjMatrix(gDisplayListHead++, &buffer[0]);
	gSPObjSprite(gDisplayListHead++, &stats_obj);
}

uObjMtx buf[10];
uObjMtx elbuf[6];

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
s8 selectedDjinn;
u8 displayedSelectedPsynergy = 0;
s8 selectedSummon;
u8 displayedSelectedSummon = 0;
s8 pointerSelectedTarget = 0;
u8 fieldPsynergyMenuState = 0;
s8 selectedItem = 0;
s8 trueSelectedItem = 0;

void determine_joystick_increment(s8 initSprite, u8 maxSprite, u8 range) {
    u8 oldOverIcon;

    switch(menuState) {
        case MENU_START:
        case MENU_FIGHT:
        case MENU_PAUSE:
        case MENU_STATUS:
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
        case MENU_FIELD_PSYNERGY:
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
        case MENU_ITEM:
            if(gPlayer1Controller->stickY > 20.0f && fU == 0) {
                fU = 5;
                selectedItem -= 1;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            } else if(gPlayer1Controller->stickY < -20.0f && fD == 0) {
                fD = 5;
                selectedItem += 1;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            }
            break;
        case MENU_FIELD_ITEM:
            if(gPlayer1Controller->stickY > 20.0f && fU == 0) {
                fU = 5;
                selectedItem -= 1;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            } else if(gPlayer1Controller->stickY < -20.0f && fD == 0) {
                fD = 5;
                selectedItem += 1;
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
        case MENU_SUMMON:
            if(gPlayer1Controller->stickY > 20.0f && fU == 0) {
                fU = 5;
                selectedSummon -= 1;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            } else if(gPlayer1Controller->stickY < -20.0f && fD == 0) {
                fD = 5;
                selectedSummon += 1;
                play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
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
u8 turnUserUsingAnim = 0xFF;
void determine_turn_order(void) {
    u8 i, j, k;
    
    gBattleInfo.turnActionProgress = 0;
    gBattleInfo.turnUser = 0;
    turnUserUsingAnim = 0xFF;

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

    if(gBattleInfo.exitTimer > 35) {
        if(menuState == MENU_LOSE) {
            gBattleInfo.player[0].HP = 1;
            level_trigger_warp(gMarioState, WARP_OP_DEATH);
        }
        if(menuState == MENU_WIN && gCurrAreaIndex == 6) {
            level_trigger_warp(gMarioState, WARP_OP_CREDITS_END);
        }
        menuState = MENU_NONE;
        overIcon = OVER_FIGHT;
        set_mario_action(gMarioState, ACT_IDLE, 0);
        stop_background_music(sBackgroundMusicQueue[0].seqId);
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, gBattleInfo.lastSeq), 0);
        for(i = 0; i < 3; i++) {
            if(gBattleInfo.enemy[i].obj != 0) {
                gBattleInfo.enemy[i].obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            gBattleInfo.enemy[i].obj = gBattleInfo.enemy[i].baseHP = gBattleInfo.enemy[i].HP = 0;
            gBattleInfo.enemy[i].target[0] = gBattleInfo.enemy[i].target[1] = gBattleInfo.enemy[i].target[2] = gBattleInfo.enemy[i].target[3] = 0xFF;
        }
        gHudDisplay.flags = HUD_DISPLAY_DEFAULT;
        rngFrame = 0;
        while(rngFrame < 300) {
            rngFrame = random_u16() % 900;
        }
        
        gBattleInfo.exitTimer = 0;
    } else {
        gBattleInfo.exitTimer++;
        if(gBattleInfo.exitTimer == 18) {
            gCamera->cutscene = 0;
            vec3f_copy(gMarioState->pos, gBattleInfo.lastPos);
            vec3f_copy(gMarioObject->header.gfx.pos, gMarioState->pos);
            vec3f_copy(gCamera->pos, gBattleInfo.lastCamPos);
            gCutsceneTimer = 0;
            //reset_camera(gCamera);
            if(menuState == MENU_LOSE) {
                gBattleInfo.player[0].HP = 1;
            }
            for(i = 0; i < 4; i++) {
                if(gBattleInfo.player[i].obj != 0) {
                    gBattleInfo.player[i].obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                    gBattleInfo.player[i].obj = 0;
                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP = gBattleInfo.player[i].HP;
                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].PP = gBattleInfo.player[i].PP;
                }
            }
            if(gCurrCourseNum != 1)
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].lastFloor = 0;
            else
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].lastFloor = gCurrAreaIndex;
            save_file_do_save(gCurrSaveFileNum - 1);
        }
    }
}

void determine_next_selecting_player(void) {
    if(gBattleInfo.selectingUser < gCharactersUnlocked) {
        gBattleInfo.selectingUser++;
        menuState = MENU_FIGHT;
        overIcon = OVER_ATTACK;
    } else {
        determine_turn_order();
        menuState = MENU_TURN;
    }
}

u8 fauxInventory[8][2] = {
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
};

void determine_menu_switch(void) {
    u8 i;
    switch(menuState) {
        case MENU_START:
            if(overIcon == OVER_FIGHT && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_FIGHT;
                overIcon = OVER_ATTACK;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else if(overIcon == OVER_FLEE && gPlayer1Controller->buttonPressed & A_BUTTON) {
                if(gCurrAreaIndex != 6) {
                    menuState = MENU_FLEE;
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                }
            } else if(overIcon == OVER_STATUS && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_STATUS;
                overIcon = 0;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            }
            break;
        case MENU_FIGHT:
            gBattleInfo.player[gBattleInfo.selectingUser].action = 0;
            gBattleInfo.player[gBattleInfo.selectingUser].subAction = 0;
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                while(gBattleInfo.player[gBattleInfo.selectingUser - 1].HP <= 0 && gBattleInfo.selectingUser > 0) {
                    gBattleInfo.selectingUser--;
                }
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
            } else if(overIcon == OVER_DJINN && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_DJINN;
                selectedDjinn = 0;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else if(overIcon == OVER_SUMMON && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_SUMMON;
                selectedDjinn = 0;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else if(overIcon == OVER_DEFEND && gPlayer1Controller->buttonPressed & A_BUTTON) {
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                gBattleInfo.player[gBattleInfo.selectingUser].action = ACT_DEFEND;
                determine_next_selecting_player();
            } else if(overIcon == OVER_ITEM && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_ITEM;
                selectedItem = 0;
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
                u8 i = 0;
                struct Spell **movePool = SpellPool[gBattleInfo.selectingUser];
                if(movePool[displayedSelectedPsynergy]->PP <= gBattleInfo.player[gBattleInfo.selectingUser].PP) {
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                    menuState = MENU_SELECT;
                    gBattleInfo.prevMenu = MENU_PSYNERGY;
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }
            break;
        case MENU_DJINN:
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                menuState = MENU_FIGHT;
                overIcon = OVER_DJINN;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(gPlayer1Controller->buttonPressed & A_BUTTON) {
                u8 i = 0;
                if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[gBattleInfo.selectingUser].activeState == DJINN_ACTIVE && gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[gBattleInfo.selectingUser].turnsUntilActive == 0 && (gSaveBuffer.files[gCurrSaveFileNum - 1][0].courseStars[0] & (1 << gBattleInfo.selectingUser)) != 0) {
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                    menuState = MENU_SELECT;
                    gBattleInfo.prevMenu = MENU_DJINN;
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }
            break;
        case MENU_SUMMON:
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                menuState = MENU_FIGHT;
                overIcon = OVER_SUMMON;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(gPlayer1Controller->buttonPressed & A_BUTTON) {
                u8 i = 0;
                if(gBattleInfo.djinnUsed[0] != 0 || gBattleInfo.djinnUsed[1] != 0 || gBattleInfo.djinnUsed[2] != 0 || gBattleInfo.djinnUsed[3] != 0) {
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                    menuState = MENU_SELECT;
                    gBattleInfo.prevMenu = MENU_SUMMON;
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }
            break;
        case MENU_SELECT:
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                menuState = gBattleInfo.prevMenu;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(gPlayer1Controller->buttonPressed & A_BUTTON) {
                u8 i = 0;
                if(gBattleInfo.prevMenu == MENU_PSYNERGY) {
                    struct Spell **movePool = SpellPool[gBattleInfo.selectingUser];
                    switch(movePool[displayedSelectedPsynergy]->sprite) {
                        case SPELL_GUARD:
                        case SPELL_IMPACT:
                        case SPELL_PLY:
                        case SPELL_PLY_WELL:
                            if(gBattleInfo.player[gBattleInfo.selectingUser].HP <= 0)
                                i = 1;
                            break;
                        case SPELL_REVIVE:
                            if(gBattleInfo.player[gBattleInfo.selectingUser].HP > 0)
                                i = 1;
                            break;    
                    }
                } else if(gBattleInfo.prevMenu == MENU_ITEM) {
                    gBattleInfo.player[gBattleInfo.selectingUser].action = ACT_ITEM;
                    gBattleInfo.player[gBattleInfo.selectingUser].subAction = gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[trueSelectedItem].id;
                } else if(gBattleInfo.prevMenu == MENU_DJINN) {

                } else if(gBattleInfo.prevMenu == MENU_SUMMON) {
                    gBattleInfo.player[gBattleInfo.selectingUser].action = ACT_SUMMON;
                    gBattleInfo.player[gBattleInfo.selectingUser].subAction = displayedSelectedSummon;
                }
                if(i == 0) {
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                    determine_next_selecting_player();
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }
            break;
        case MENU_ITEM:
            if(gPlayer1Controller->buttonPressed & B_BUTTON) {
                menuState = MENU_FIGHT;
                overIcon = OVER_ITEM;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if(gPlayer1Controller->buttonPressed & A_BUTTON) {
                for(i = 0; i < 8; i++) {
                    if(fauxInventory[selectedItem][0] == gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].id) {
                        trueSelectedItem = i;
                    }
                }
                if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[trueSelectedItem].id != ITEM_SACRED_FEATHER && gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[0].number > 0) {
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                    menuState = MENU_SELECT;
                    gBattleInfo.prevMenu = MENU_ITEM;
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }
            break;
    }

    if(menuState != MENU_SELECT && menuState != MENU_ATTACK) {
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

void gs_print(int x, int y, const char *str, int shadow, int color) {
    uObjMtx *sbuf;
    if(shadow == SHADOW) {
        sbuf = alloc_display_list(sizeof(uObjMtx) * s2d_strlen(str));
        sprintf(tbuf, COLOR"0 0 0 255%s", str);
        s2d_print(x, y + 1, tbuf, sbuf);
    }
    sbuf = alloc_display_list(sizeof(uObjMtx) * (s2d_strlen(str) + 0x14));
    switch(color) {
        case WHITE:
            sprintf(tbuf, COLOR"255 255 255 255" "%s", str);
            break;
        case YELLOW:
            sprintf(tbuf, COLOR"255 255 0 255" "%s", str);
            break;
        case RED:
            sprintf(tbuf, COLOR"175 0 0 255" "%s", str);
            break;
    }
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
            pointer[0]->oPosY = gBattleInfo.enemy[pointerSelectedTarget].obj->hitboxHeight - 10900.0f;
            pointer[0]->oPosZ = gBattleInfo.enemy[pointerSelectedTarget].obj->oPosZ;
            for(i = 1; i < 4; i++) {
                if(pointer[i] != 0) {
                    pointer[i]->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                    pointer[i] = 0;
                }
            }
            gBattleInfo.player[gBattleInfo.selectingUser].target[0] = pointerSelectedTarget + 4;
            gBattleInfo.player[gBattleInfo.selectingUser].target[1] = gBattleInfo.player[gBattleInfo.selectingUser].target[2] = 0xFF;
        } else if(rangeType == RANGE_ALL_ENEMIES) {
            for(i = 0; i < 3; i++) {
                if(gBattleInfo.enemy[i].obj != 0) {
                    if(pointer[i] == 0) {
                        pointer[i] = spawn_object(gMarioObject, MODEL_POINTER, bhvPointer);
                    }
                    pointer[i]->oPosX = gBattleInfo.enemy[i].obj->oPosX;
                    pointer[i]->oPosY = gBattleInfo.enemy[i].obj->hitboxHeight - 10900.0f;
                    pointer[i]->oPosZ = gBattleInfo.enemy[i].obj->oPosZ;
                    gBattleInfo.player[gBattleInfo.selectingUser].target[i] = i + 4;
                }
            }
            if(pointer[3] != 0) {
                pointer[3]->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                pointer[3] = 0;
            }
        } else if(rangeType == RANGE_SINGLE_PARTY) {
            if(pointer[0] == 0) {
                pointer[0] = spawn_object(gMarioObject, MODEL_POINTER, bhvPointer);
            }
            pointer[0]->oPosX = gBattleInfo.player[pointerSelectedTarget].obj->oPosX;
            pointer[0]->oPosY = -10850.0f;
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
                if(gBattleInfo.player[i].obj != 0) {
                    if(pointer[i] == 0) {
                        pointer[i] = spawn_object(gMarioObject, MODEL_POINTER, bhvPointer);
                    }
                    pointer[i]->oPosX = gBattleInfo.player[i].obj->oPosX;
                    pointer[i]->oPosY = -10850.0f;
                    pointer[i]->oPosZ = gBattleInfo.player[i].obj->oPosZ;
                    gBattleInfo.player[gBattleInfo.selectingUser].target[i] = i;
                } else {
                    if(pointer[i] != 0) {
                        pointer[i]->activeFlags = ACTIVE_FLAG_DEACTIVATED;
                        pointer[i] = 0;
                    }
                }
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
                call_portrait_sprite_dl(gBattleInfo.selectingUser, 0, 176, &elbuf[5]);
                break;
        }

        determine_joystick_increment(initSprite, maxSprite, 0);

    if(menuState == MENU_START || menuState == MENU_FIGHT) {
        determine_over_icon();

        render_bar_wh(256, 212, 64, 24);
        sprintf(cbuf, "%s", overString);
        gs_print(254, 220, cbuf, SHADOW, WHITE);

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

uObjMtx ebuf[8];
uObjMtx hebuf2[6];
char spbuf[512];
u8 psynergyMax = 0;

void render_psynergy_menu(void) {
    struct Spell **movePool;
    u8 i, j = 0;
    determine_menu_switch();
    determine_joystick_increment(0, 255, 0);
    s2d_init();
    call_portrait_sprite_dl(gBattleInfo.selectingUser, 0, 176, &elbuf[5]);
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
                gs_print(136, 100 + j*24, spbuf, SHADOW, WHITE);
                sprintf(spbuf, "PP %d", movePool[i]->PP);
                gs_print(232, 100 + j*24, spbuf, SHADOW, WHITE);
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
    gs_print(4, 68, spbuf, SHADOW, WHITE);
    s2d_stop();
}

void render_djinn_menu(void) {
    struct Djinni *djinni;
    u8 i, j, color = 0;
    determine_menu_switch();
    determine_joystick_increment(0, 255, 0);
    s2d_init();
    render_bar_wh(224, 120, 96, 120);
    render_bar_wh(0, 88, 224, 152);
    render_bar_wh(0, 56, 320, 32);
    djinni = djinniPool[gBattleInfo.selectingUser];
    if((gSaveBuffer.files[gCurrSaveFileNum - 1][0].courseStars[0] & (1 << gBattleInfo.selectingUser)) != 0) {
        if(selectedDjinn > psynergyMax)
            selectedDjinn = 0;
        if(selectedDjinn < 0)
            selectedDjinn = psynergyMax;
        j = 0;
        render_battle_fill_rect(228, 124 + selectedDjinn*24, 316, 148 + selectedDjinn*24, 0x00, 0x97, 0xE2);
        call_element_sprite_dl(djinni->element, 232, 132 + j*24, &hebuf2[j]);
        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[gBattleInfo.selectingUser].activeState == DJINN_INACTIVE) {
            color = RED;
        } else if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[gBattleInfo.selectingUser].turnsUntilActive > 0) {
            color = YELLOW;
            sprintf(spbuf, " %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[gBattleInfo.selectingUser].turnsUntilActive);
            gs_print(292, 132 + j*24, spbuf, SHADOW, color);
        } else {
            color = WHITE;
        }
        sprintf(spbuf, "%s", djinni->name);
        gs_print(240, 132 + j*24, spbuf, SHADOW, color);
        sprintf(spbuf, "%s", djinni->tooltip);
        gs_print(4, 68, spbuf, SHADOW, WHITE);
    }
    call_portrait_sprite_dl(gBattleInfo.selectingUser, 0, 176, &elbuf[5]);
    call_icons_sprite_dl(OVER_DJINN, 200, 208, &buf[0], 0, 1.0f);
    s2d_stop();
}

u8 summonMax = 0;
void render_summon_menu(void) {
    struct Spell **movePool;
    u8 i, j, k, l, m, n = 0;
    determine_menu_switch();
    determine_joystick_increment(0, 255, 0);
    s2d_init();
    call_portrait_sprite_dl(gBattleInfo.selectingUser, 0, 176, &elbuf[5]);
    call_icons_sprite_dl(OVER_SUMMON, 128, 208, &buf[0], 0, 1.0f);
    render_bar_wh(112, 88, 208, 152);
    render_bar_wh(0, 56, 320, 32);
    movePool = SpellPool[gBattleInfo.selectingUser];
    summonMax = 0;
    for(i = 0; i < 4; i++) {
        l = 0;
        for(k = 0; k < 4; k++) {
            if(gBattleInfo.djinnUsed[k] >= summonPool[i]->elements[k]) {
                l++;
            }
        }
        if(l >= 4) {
            summonMax++;
        }
    }
    
    i = 0;
    if(selectedSummon > summonMax - 1)
        selectedSummon = 0;
    if(selectedSummon < 0)
        selectedSummon = summonMax - 1;
    j = 0;
    if(summonMax != 0) {
        render_battle_fill_rect(116, 92 + selectedSummon*24, 316, 116 + selectedSummon*24, 0x00, 0x97, 0xE2);
        while(i < 4) {
            l = 0;
            for(k = 0; k < 4; k++) {
                if(gBattleInfo.djinnUsed[k] >= summonPool[i]->elements[k]) {
                    l++;
                }
            }
            if(l >= 4) {
                call_djinn_sprite_dl(summonPool[i]->element, 120, 96 + j*24, &ebuf[j]);
                n = 0;
                for(m = 0; m < 4; m++) {
                    if(summonPool[i]->elements[m] > 0) {
                        call_element_sprite_dl(m, 280 - (n*24), 100 + j*24, &hebuf2[j]);
                        sprintf(spbuf, " %d", summonPool[i]->elements[m]);
                        gs_print(280 - (n*24), 100 + j*24, spbuf, SHADOW, WHITE);
                        n++;
                    }
                }
                sprintf(spbuf, "%s", summonPool[i]->name);
                gs_print(136, 100 + j*24, spbuf, SHADOW, WHITE);
                if(selectedSummon == j)
                    displayedSelectedSummon = i;
                j++;
            }
            i++;
        }
        sprintf(spbuf, "%s", summonPool[displayedSelectedSummon]->tooltip);
        gs_print(4, 68, spbuf, SHADOW, WHITE);
    } else {
        sprintf(spbuf, "You have no summons available.");
        gs_print(4, 68, spbuf, SHADOW, WHITE);
    }
    s2d_stop();
}

const char *items[6] = {
    "Herb",
    "Corn",
    "Nut",
    "Psy Crystal",
    "Sacred Feather",
    "Water of Life",
};

const char *itemTooltips[6] = {
    "Replenishes 25 HP to a party member.",
    "Replenishes 50 HP to a party member.",
    "Replenishes 150 HP to a party member.",
    "Replenishes all PP to a party member.",
    "Reduces enemy encounter rate temporarily.",
    "Revives a downed party memeber.",
};

void call_item_sprite_dl(int idx, int x, int y, uObjMtx *buffer, f32 scale) {
	gDPPipeSync(gDisplayListHead++);
	gSPDisplayList(gDisplayListHead++, s2d_init_dl);
	gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
	gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2);
	gDPSetTextureLUT(gDisplayListHead++, G_TT_RGBA16);
	gSPObjRenderMode(gDisplayListHead++, G_OBJRM_XLU | G_OBJRM_BILERP);
	gSPObjLoadTxtr(gDisplayListHead++, &item_tex[idx]);
	gSPObjLoadTxtr(gDisplayListHead++, &item_pal_TLUT[idx]);
	setup_mtx(&buffer[0], x, y, scale);
	gSPObjMatrix(gDisplayListHead++, &buffer[0]);
	gSPObjSprite(gDisplayListHead++, &item_obj);
}

void render_select_menu(void) {
    struct Spell **movePool = SpellPool[gBattleInfo.selectingUser];
    struct Djinni *djinni = djinniPool[gBattleInfo.selectingUser];
    u8 range;
    if(gBattleInfo.prevMenu == MENU_PSYNERGY) {
        range = movePool[displayedSelectedPsynergy]->range;
    } else if(gBattleInfo.prevMenu == MENU_DJINN) {
        range = djinni->range;
    } else if(gBattleInfo.prevMenu == MENU_SUMMON) {
        range = RANGE_ALL_ENEMIES;
    } else {
        range = RANGE_SINGLE_PARTY;
    }
    print_pointer(range);
    determine_menu_switch();
    determine_joystick_increment(0, 255, range);

    s2d_init();
    call_portrait_sprite_dl(gBattleInfo.selectingUser, 0, 176, &elbuf[5]);
    render_bar_wh(112, 208, 208, 32);
    if(gBattleInfo.prevMenu == MENU_PSYNERGY) {
        call_icons_sprite_dl(OVER_PSYNERGY, 80, 208, &buf[0], 0, 1.0f);
        call_spell_sprite_dl(movePool[displayedSelectedPsynergy]->sprite, 120, 216, &ebuf[0]);
        call_element_sprite_dl(gBattleInfo.selectingUser, 280, 220, &hebuf2[0]);
        sprintf(spbuf, "%s", movePool[displayedSelectedPsynergy]->name);
        gs_print(136, 220, spbuf, SHADOW, WHITE);
        sprintf(spbuf, "PP %d", movePool[displayedSelectedPsynergy]->PP);
        gs_print(232, 220, spbuf, SHADOW, WHITE);
        gBattleInfo.player[gBattleInfo.selectingUser].action = ACT_PSYNERGY;
        gBattleInfo.player[gBattleInfo.selectingUser].subAction = displayedSelectedPsynergy;
    } else if(gBattleInfo.prevMenu == MENU_ITEM) {
        call_icons_sprite_dl(OVER_ITEM, 80, 208, &buf[0], 0, 1.0f);
        call_item_sprite_dl(gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[trueSelectedItem].id, 120, 216, &ebuf[0], 1.0f);
        sprintf(cbuf, "  %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[trueSelectedItem].number);
        gs_print(108, 224, cbuf, SHADOW, WHITE);
        sprintf(cbuf, "%s", items[gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[trueSelectedItem].id]);
        gs_print(132, 220, cbuf, SHADOW, WHITE);
    } else if(gBattleInfo.prevMenu == MENU_DJINN) {
        call_icons_sprite_dl(OVER_DJINN, 80, 208, &buf[0], 0, 1.0f);
        gBattleInfo.player[gBattleInfo.selectingUser].action = ACT_DJINN;
        gBattleInfo.player[gBattleInfo.selectingUser].subAction = djinni->id;
    } else {
        call_icons_sprite_dl(OVER_SUMMON, 80, 208, &buf[0], 0, 1.0f);
        if(gBattleInfo.player[gBattleInfo.selectingUser].action != ACT_SUMMON) {
            gBattleInfo.player[gBattleInfo.selectingUser].action = 0;
            gBattleInfo.player[gBattleInfo.selectingUser].subAction = 0;
        }
    }
    s2d_stop();
}

void render_select_attack_menu(void) {
    determine_menu_switch();
    print_pointer(0);
    determine_joystick_increment(0, 255, 0);
    s2d_init();
    call_portrait_sprite_dl(gBattleInfo.selectingUser, 0, 176, &elbuf[5]);
    call_icons_sprite_dl(OVER_ATTACK, 80, 208, &buf[0], 0, 1.0f);
    render_bar_wh(112, 208, 128, 32);
    gs_print(148, 220, "Attack", SHADOW, WHITE);
    s2d_stop();
}

void render_item_menu(void) {
    struct InventoryItem *inventory = &gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory;
    u8 i, j = 0;
    u8 itemMax = 0;
    determine_menu_switch();
    if(/*inventory[0].number*/ fauxInventory[0][1] > 0) {
        determine_joystick_increment(0, 255, 0);
    } else {
        selectedItem = 0;
    }
    gBattleInfo.player[gBattleInfo.selectingUser].action = 0;
    s2d_init();
    call_portrait_sprite_dl(gBattleInfo.selectingUser, 0, 176, &elbuf[5]);
    call_icons_sprite_dl(OVER_ITEM, 112, 208, &buf[0], 0, 1.0f);
    render_bar_wh(144, 88, 176, 152);
    render_bar_wh(0, 56, 320, 32);
    itemMax = 0;
    j = 0;
    for(i = 0; i < 8; i++) {
        if(/*inventory[i].number*/ fauxInventory[i][1] != 0) {
            itemMax++;
        }
    }
    
    i = 0;
    if(selectedItem >= itemMax)
        selectedItem = 0;
    if(selectedItem < 0)
        selectedItem = itemMax - 1;
    j = 0;
    render_battle_fill_rect(148, 92 + selectedItem*24, 316, 116 + selectedItem*24, 0x00, 0x97, 0xE2);
    while(i < itemMax) {
        call_item_sprite_dl(/*inventory[i].id*/ fauxInventory[i][0], 152, 96 + i*24, &ebuf[i], 1.0f);
        sprintf(cbuf, "  %d", /*inventory[i].number*/ fauxInventory[i][1]);
        gs_print(140, 104 + i*24, cbuf, SHADOW, WHITE);
        sprintf(cbuf, "%s", items[/*inventory[i].id*/fauxInventory[i][0]]);
        gs_print(168, 100 + i*24, cbuf, SHADOW, WHITE);
        i++;
    }
    if(/*inventory[0].number*/ fauxInventory[0][1] > 0) {
        sprintf(spbuf, "%s", itemTooltips[/*inventory[selectedItem].id*/ fauxInventory[selectedItem][0]]);
    } else {
        sprintf(spbuf, "You have no items.");
    }
    gs_print(4, 68, spbuf, SHADOW, WHITE);
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
        gs_print(0, 212, cbuf, NO_SHADOW, WHITE);
    } else {
        gs_print(0, 212, cbuf_prev, NO_SHADOW, WHITE);
        gs_print(0, 228, cbuf, NO_SHADOW, WHITE);
    }
}

void render_battle_init_text(void) {
    uObjMtx *sbuf;
    enemyString = gBattleInfo.enemy[0].name;
    s2d_init();
    sprintf(cbuf, "%s attacks!", enemyString);
    gs_print(0, 212, cbuf, NO_SHADOW, WHITE);
    s2d_stop();
    if(gPlayer1Controller->buttonPressed & A_BUTTON)
        menuState = MENU_START;
}

u8 enemy_select_target(u8 element) {
    u8 target;
    u8 counterElement = (element + 2) % 4;
    do{
        target = random_u16() % 4;
    } while (target > gCharactersUnlocked && gBattleInfo.player[target].HP > 0);
    if(gCharactersUnlocked >= counterElement && random_u16() % 4 == 0 && gBattleInfo.player[counterElement].HP > 0) {
        target = counterElement;
    }
    return target;
}

s16 calculate_damage(s16 attack, s16 defense, u8 attackerElement, u8 defenderElement) {
    s16 damage;

    if(attackerElement == (defenderElement + 2) % 4)
        attack += (attack / 4);
    if(attackerElement == defenderElement)
        defense += (defense / 4);
    damage = attack - defense;

    if(damage <= 0)
        damage = 1;

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
    u8 i, j;
    if(targetObj != 0) {
        if(targetObj->header.gfx.scale[0] > 0.0f) {
            obj_scale(targetObj, targetObj->header.gfx.scale[0] - 0.0625f);
            targetDead = 0;
            return 1;
        } else {
            targetObj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            gBattleInfo.enemy[target].obj = 0;
            // for(i = 0; i < 7; i++) {
            //     if(turnOrder[i] == target + 4) {
            //         turnOrder[i] == 0xFF;
            //     }
            // }
            // for(i = 0; i < 4; i++) {
            //     for(j = 0; j < 3; j++) {
            //         if(gBattleInfo.player[i].target[j] == target + 4) {
            //             if(j == 0) {
            //                 gBattleInfo.player[i].target[0] = gBattleInfo.player[i].target[1];
            //             }
            //             if(j <= 1) {
            //                 gBattleInfo.player[i].target[1] = gBattleInfo.player[i].target[2];
            //             }
            //             gBattleInfo.player[i].target[2] = 0xFF;
            //         }
            //     }
            // }
        }
    }
    return 0;
}

u8 attackAnimDone, attackAnimPlaying;
u16 attackAnimTimer;
f32 attackVar;
void reset_attack_anim(void) {
    attackAnimDone = 0;
    attackAnimTimer = 0;
    attackAnimPlaying = 0;
}

void obj_move_xz_using_fvel_and_yaw(struct Object *obj) {
    obj->oVelX = obj->oForwardVel * sins(obj->oMoveAngleYaw);
    obj->oVelZ = obj->oForwardVel * coss(obj->oMoveAngleYaw);

    obj->oPosX += obj->oVelX;
    obj->oPosZ += obj->oVelZ;
}

void reset_player(u8 turnUserID) {
    struct Object *playerObj = gBattleInfo.player[turnUserID].obj;
    if(playerObj != 0) {
        if(gBattleInfo.player[turnUserID].HP != 0) {
            geo_obj_init_animation(&playerObj->header.gfx, &playerObj->oAnimations[ANIM_IDLE]);
        }
        playerObj->oPosX = (-62.5*gCharactersUnlocked) + (125.0f*turnUserID);
        playerObj->oPosZ = (-62.5*gCharactersUnlocked) + (125.0f*turnUserID);
        playerObj->oPosY = -11000.0f;
        playerObj->oMoveAngleYaw = 0x6000;
        playerObj->oMoveAnglePitch = 0, playerObj->oMoveAngleRoll = 0;
        playerObj->oOpacity = 0;
    }
}

void reset_enemy(u8 turnUserID) {
    struct Object *playerObj = gBattleInfo.enemy[turnUserID - 4].obj;
    if(playerObj != 0) {
        if(playerObj->oAnimations != 0)
            geo_obj_init_animation(&playerObj->header.gfx, &playerObj->oAnimations[playerObj->oInitialAnim]);
        playerObj->oPosX = 375.0f + (150.0f*(turnUserID - 4)) - (gBattleInfo.totalEnemies*75.0f);
        playerObj->oPosZ = -375.0f + (150.0f*(turnUserID - 4)) - (gBattleInfo.totalEnemies*75.0f);
        playerObj->oPosY = -11000.0f;
        playerObj->oVelY = 0;
        playerObj->oMoveAngleYaw = 0xE000;
        playerObj->oOpacity = 0;
    }
}

u8 player_attack_anim(u8 target, u8 turnUserID, u8 attackAnimType) {
    struct Object *targetObj = gBattleInfo.enemy[target].obj;
    struct Object *playerObj = gBattleInfo.player[turnUserID].obj;
    if(attackAnimDone == 0) {
        switch(attackAnimType) {
            case ATTACK_ANIM:
                switch(turnUserID) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        geo_obj_init_animation(&playerObj->header.gfx, &playerObj->oAnimations[1]);
                        if(attackAnimTimer == 0) {
                            playerObj->oForwardVel = lateral_dist_between_objects(playerObj, targetObj) / 15.0f;
                            //playerObj->oVelY = targetObj->hitboxHeight / 15.0f;
                            playerObj->oVelY = (targetObj->hitboxHeight + 120.0f) / 120.0f;
                            playerObj->oMoveAngleYaw = obj_angle_to_object(playerObj, targetObj);
                        }
                        if(attackAnimTimer < 15) {
                            playerObj->oPosY += (playerObj->oVelY*(15 - attackAnimTimer));
                            obj_move_xz_using_fvel_and_yaw(playerObj);
                        }
                        else if(attackAnimTimer < 30) {
                            playerObj->oPosY -= (f32)(attackAnimTimer - 15);
                        }
                        else if(attackAnimTimer < 45) {
                            if(attackAnimTimer == 30) {
                                playerObj->oMoveAngleYaw += 0x8000;
                                targetObj->oOpacity = 1;
                                targetObj->oTimer = 0;
                            }
                            playerObj->oPosY += 20.0f;
                            if(playerObj->oPosY >= -10880.0f + targetObj->hitboxHeight) {
                                attackAnimTimer = 44;
                            }
                        }
                        else if(attackAnimTimer < 60) {
                            playerObj->oPosY -= (playerObj->oVelY*(attackAnimTimer - 45));
                            obj_move_xz_using_fvel_and_yaw(playerObj);
                        }
                        attackAnimPlaying = 1;
                        if(attackAnimTimer == 60) {
                            attackAnimDone = 1;
                            attackAnimPlaying = 0;
                            reset_player(turnUserID);
                        }
                        if(playerObj->header.gfx.animInfo.animFrame > 10)
                            playerObj->header.gfx.animInfo.animFrame = 10;
                        break;
                }
                break;
        }
    }
    attackAnimTimer++;
    return attackAnimPlaying;
}

u8 enemy_attack_anim(u8 target, u8 turnUserID, u8 attackAnimType) {
    struct Object *targetObj = gBattleInfo.player[target].obj;
    struct Object *playerObj = gBattleInfo.enemy[turnUserID - 4].obj;
    if(attackAnimDone == 0) {
        switch(attackAnimType) {
            case ATTACK_ANIM:
                switch(gBattleInfo.enemy[turnUserID - 4].id) {
                    case ENEMY_NONE:
                    case ENEMY_GOOMBA:
                    case ENEMY_BOBOMB:
                    case ENEMY_CHUCKYA:
                    case ENEMY_AMP:
                    case ENEMY_PIRANHA:
                    case ENEMY_KING_BOBOMB:
                        switch(gBattleInfo.enemy[turnUserID - 4].id) {
                            case ENEMY_CHUCKYA:
                                play_sound(SOUND_AIR_CHUCKYA_MOVE, gGlobalSoundSource);
                                break;
                            case ENEMY_AMP:
                                play_sound(SOUND_AIR_AMP_BUZZ, gGlobalSoundSource);
                                break;
                            case ENEMY_KING_BOBOMB:
                                geo_obj_init_animation(&playerObj->header.gfx, &playerObj->oAnimations[4]);
                                break;
                        }
                        if(attackAnimTimer == 0) {
                            reset_enemy(turnUserID);
                            playerObj->oForwardVel = lateral_dist_between_objects(playerObj, targetObj) / 16.0f;
                            playerObj->oMoveAngleYaw = obj_angle_to_object(playerObj, targetObj);
                        }
                        if(attackAnimTimer < 15) {
                            obj_move_xz_using_fvel_and_yaw(playerObj);
                        }
                        else if(attackAnimTimer < 30) {
                            if(attackAnimTimer == 15) {
                                targetObj->oOpacity = 1;
                                targetObj->oTimer = 0;
                                playerObj->oMoveAngleYaw += 0x8000;
                            }
                            obj_move_xz_using_fvel_and_yaw(playerObj);
                        }
                        attackAnimPlaying = 1;
                        if(attackAnimTimer == 30) {
                            attackAnimDone = 1;
                            attackAnimPlaying = 0;
                            reset_enemy(turnUserID);
                        }
                        break;
                    case ENEMY_WHOMP:
                        if(attackAnimTimer == 0) {
                            reset_enemy(turnUserID);
                            playerObj->oForwardVel = lateral_dist_between_objects(playerObj, targetObj) / 36.0f;
                            playerObj->oMoveAngleYaw = obj_angle_to_object(playerObj, targetObj);
                        }
                        if(attackAnimTimer < 30) {
                            obj_move_xz_using_fvel_and_yaw(playerObj);
                            if(attackAnimTimer >= 20) {
                                playerObj->oPosY += 20.0f;
                                playerObj->oMoveAnglePitch += 0x666;
                            }
                        } else if(attackAnimTimer >= 30 && attackAnimTimer < 40) {
                            if(attackAnimTimer == 38) {
                                play_sound(SOUND_OBJ_THWOMP, gGlobalSoundSource);
                            }
                            playerObj->oPosY -= 20.0f;
                        } else if(attackAnimTimer >= 50 && attackAnimTimer < 80) {
                            if(attackAnimTimer == 50) {
                                playerObj->oMoveAngleYaw += 0x8000;
                                targetObj->oOpacity = 1;
                                targetObj->oTimer = 0;
                            }
                            if(playerObj->oMoveAnglePitch > 0) {
                                playerObj->oMoveAnglePitch -= 0x666;
                                if(playerObj->oMoveAnglePitch < 0) {
                                    playerObj->oMoveAnglePitch = 0;
                                }
                            }
                            obj_move_xz_using_fvel_and_yaw(playerObj);
                        }
                        attackAnimPlaying = 1;
                        if(attackAnimTimer == 80) {
                            attackAnimDone = 1;
                            attackAnimPlaying = 0;
                            reset_enemy(turnUserID);
                        }
                        break;
                    case ENEMY_THWOMP:
                        if(attackAnimTimer == 0) {
                            reset_enemy(turnUserID);
                            playerObj->oForwardVel = lateral_dist_between_objects(playerObj, targetObj) / 21.0f;
                            playerObj->oMoveAngleYaw = obj_angle_to_object(playerObj, targetObj);
                        }
                        if(attackAnimTimer < 20) {
                            obj_move_xz_using_fvel_and_yaw(playerObj);
                            playerObj->oPosY += 10.0f;
                        } else if(attackAnimTimer >= 30 && attackAnimTimer < 40) {
                            if(attackAnimTimer == 38) {
                                play_sound(SOUND_OBJ_THWOMP, gGlobalSoundSource);
                            }
                            playerObj->oPosY -= 20.0f;
                        } else if(attackAnimTimer >= 50 && attackAnimTimer < 70) {
                            if(attackAnimTimer == 50) {
                                playerObj->oMoveAngleYaw += 0x8000;
                                targetObj->oOpacity = 1;
                                targetObj->oTimer = 0;
                            }
                            obj_move_xz_using_fvel_and_yaw(playerObj);
                        }
                        attackAnimPlaying = 1;
                        if(attackAnimTimer == 70) {
                            attackAnimDone = 1;
                            attackAnimPlaying = 0;
                            reset_enemy(turnUserID);
                        }
                        break;
                }
                break;
        }
    }
    attackAnimTimer++;
    return attackAnimPlaying;
}

u8 isAttackDone;
u8 animPlaying, animAboutToPlay;
s16 damage;
s8 target, targetNo;
u8 turnUserID;

u8 search_for_next_player(u8 range) {
    u8 l = 1;
    u8 counter = 0;
    u8 initialTarget = target;
    while(l == 1 && counter < 9) {
        target++;
        if(target > 3) {
            if(range == RANGE_ALL_PARTY) {
                counter = 9;
                target = 3;
            } else
                target = 0;
        }
        if(gBattleInfo.player[target].HP != 0) {
            l = 0;
        }
        if(target == initialTarget) {
            counter = 9;
            target = 3;
        }
        counter++;
    }
    if(counter >= 9 && l == 1)
        isAttackDone = 1;
    return l;
}

struct Object *psynergyObj;
u8 psynergy_anim(u8 target, u8 turnUserID, u8 psynergyAnimType) {
    struct Object *targetObj;
    struct Object *playerObj;
    u8 i;

    if(turnUserID < 4) {
        if(gBattleInfo.enemy[target].obj == 0) {
            for(i = 0; i < 2; i++) {
                if(gBattleInfo.enemy[i].obj != 0) {
                    targetObj = gBattleInfo.enemy[i].obj;
                    i = 3;
                }
            }
        } else {
            targetObj = gBattleInfo.enemy[target].obj;
        }
        playerObj = gBattleInfo.player[turnUserID].obj;
    } else {
        targetObj = gBattleInfo.player[target].obj;
        playerObj = gBattleInfo.enemy[turnUserID - 4].obj;
    }
    if(attackAnimDone == 0 && turnUserUsingAnim != turnUserID) {
        f32 tempFloat = 0.0f;
        attackAnimPlaying = 1;
        switch(psynergyAnimType) {
            case SPELL_WHIRLWIND:
                if(attackAnimTimer == 0) {
                    psynergyObj = spawn_object(targetObj, MODEL_TORNADO, bhvPsynergy);
                    psynergyObj->oPosX -= 750.0f;
                    psynergyObj->oPosZ -= 750.0f;
                    psynergyObj->oBehParams2ndByte = SPELL_WHIRLWIND;
                }
                if(attackAnimTimer == 60) {
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                }
                gBattleInfo.camFocus = 8;
                break;
            case SPELL_TORNADO:
                if(attackAnimTimer == 0 || attackAnimTimer == 8 || attackAnimTimer == 16) {
                    psynergyObj = spawn_object(targetObj, MODEL_TORNADO, bhvPsynergy);
                    psynergyObj->oPosX -= 750.0f;
                    psynergyObj->oPosZ -= 750.0f;
                    obj_scale(psynergyObj, 1.5f);
                    psynergyObj->oBehParams2ndByte = SPELL_WHIRLWIND;
                }
                if(attackAnimTimer == 90) {
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                }
                gBattleInfo.camFocus = 8;
                break;
            case SPELL_GROWTH:
                if(attackAnimTimer == 0) {
                    psynergyObj = spawn_object(targetObj, MODEL_GROWTH, bhvPsynergy);
                    obj_scale(psynergyObj, 0.5f);
                    psynergyObj->oPosY -= 250.0f;
                    psynergyObj->oBehParams2ndByte = SPELL_GROWTH;
                }
                if(attackAnimTimer == 60) {
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                }
                gBattleInfo.camFocus = target + 5;
                break;
            case SPELL_SPIRE:
                if(attackAnimTimer == 0) {
                    psynergyObj = spawn_object(targetObj, MODEL_SPIRE, bhvPsynergy);
                    obj_scale(psynergyObj, 0.25f);
                    psynergyObj->oPosY -= 250.0f;
                    psynergyObj->oBehParams2ndByte = SPELL_SPIRE;
                }
                if(attackAnimTimer == 60) {
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                }
                gBattleInfo.camFocus = target + 5;
                break;
            case SPELL_FLARE_STORM:
                if(tempFloat == 0) {
                    tempFloat = 10.0f;
                }
                if(attackAnimTimer % 3 == 1 && attackAnimTimer < 21) {
                    psynergyObj = spawn_object(targetObj, MODEL_RED_FLAME, bhvPsynergy);
                    obj_scale(psynergyObj, tempFloat);
                    psynergyObj->oPosY += 550.0f;
                    psynergyObj->oBehParams2ndByte = SPELL_FLARE;
                    psynergyObj->oPosX -= 750.0f;
                    psynergyObj->oPosZ -= 750.0f;
                }
            case SPELL_FLARE_WALL:
                if(tempFloat == 0) {
                    tempFloat = 7.5f;
                }
                if(attackAnimTimer % 3 == 2 && attackAnimTimer < 21) {
                    psynergyObj = spawn_object(targetObj, MODEL_RED_FLAME, bhvPsynergy);
                    obj_scale(psynergyObj, tempFloat);
                    psynergyObj->oPosY += 30.0f*tempFloat;
                    psynergyObj->oBehParams2ndByte = SPELL_FLARE;
                    psynergyObj->oPosX -= 750.0f;
                    psynergyObj->oPosZ -= 750.0f;
                }
            case SPELL_FLARE:
                if(tempFloat == 0) {
                    tempFloat = 5.0f;
                }
                if(attackAnimTimer % 3 == 0 && attackAnimTimer < 21) {
                    psynergyObj = spawn_object(targetObj, MODEL_RED_FLAME, bhvPsynergy);
                    obj_scale(psynergyObj, tempFloat);
                    psynergyObj->oBehParams2ndByte = SPELL_FLARE;
                    psynergyObj->oPosX -= 750.0f;
                    psynergyObj->oPosZ -= 750.0f;
                    psynergyObj->oPosY += 5.0f*tempFloat;
                }
                if(attackAnimTimer == 60) {
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                }
                gBattleInfo.camFocus = 8;
                break;
            case SPELL_VOLCANO:
                if(attackAnimTimer < 15) {
                    for(i = 0; i < 3; i++) {
                        psynergyObj = spawn_object(targetObj, MODEL_RED_FLAME, bhvPsynergy);
                        obj_scale(psynergyObj, 5.0f);
                        psynergyObj->oBehParams2ndByte = SPELL_VOLCANO;
                        psynergyObj->oPosX += (((f32)((s16)random_u16())) / 500.0f);
                        psynergyObj->oPosZ += (((f32)((s16)random_u16())) / 500.0f);
                        psynergyObj->oPosY -= 50.0f;
                    }
                }
                if(attackAnimTimer == 60) {
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                }
                gBattleInfo.camFocus = target + 5;
                break;
            case SPELL_FROST:
            case SPELL_TUNDRA:
            case SPELL_GLACIER:
                if(attackAnimTimer == 0) {
                    psynergyObj = spawn_object(targetObj, MODEL_GLACIER, bhvPsynergy);
                    obj_scale(psynergyObj, 0.25f);
                    if(psynergyAnimType == SPELL_FROST) {
                        psynergyObj->oPosY -= 375.0f;
                        psynergyObj->oOpacity = target;
                        psynergyObj->oBehParams2ndByte = SPELL_FROST;
                        gBattleInfo.camFocus = target + 5;
                    } else if(psynergyAnimType == SPELL_TUNDRA) {
                        psynergyObj->header.gfx.scale[0] = 1.0f;
                        psynergyObj->header.gfx.scale[1] = 0.375f;
                        psynergyObj->oPosY -= 375.0f;
                        psynergyObj->oPosX = 375.0f;
                        psynergyObj->oPosZ = -375.0f;
                        psynergyObj->oBehParams2ndByte = SPELL_TUNDRA;
                        gBattleInfo.camFocus = 8;
                    } else if(psynergyAnimType == SPELL_GLACIER) {
                        psynergyObj->header.gfx.scale[0] = 1.5f;
                        psynergyObj->header.gfx.scale[1] = psynergyObj->header.gfx.scale[2] = 0.5f;
                        psynergyObj->oPosY -= 750.0f;
                        psynergyObj->oPosX = 375.0f;
                        psynergyObj->oPosZ = -375.0f;
                        psynergyObj->oBehParams2ndByte = SPELL_GLACIER;
                        gBattleInfo.camFocus = 8;
                    }
                }
                if(attackAnimTimer == 90) {
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                }
                break;
            case SPELL_GUARD:
            case SPELL_IMPACT:
            case SPELL_REVIVE:
            case SPELL_PLY:
            case SPELL_PLY_WELL:
                targetObj = gBattleInfo.player[target].obj;
                if(attackAnimTimer % 3 == 0) {
                    psynergyObj = spawn_object(targetObj, MODEL_NONE, bhvSparkleSpawn);
                    psynergyObj->oPosY += 150.0f;
                }
                if(attackAnimTimer == 30) {
                    u8 tempVal = 0;
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                    tempVal = 0;
                    if(psynergyAnimType != SPELL_REVIVE && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP == 0)
                        tempVal = search_for_next_player(RANGE_SINGLE_PARTY);
                    if(tempVal == 0) {
                        switch(psynergyAnimType) {
                            case SPELL_GUARD:
                                //gBattleInfo.player[target].defense = gBattleInfo.player[target].baseDefense + (gBattleInfo.player[target].baseDefense / 4) + 1;
                                gBattleInfo.player[target].defenseOffset = (gBattleInfo.player[target].baseDefense / 4) + 1;
                                gBattleInfo.player[target].ttDefenseR = 3;
                                break;
                            case SPELL_IMPACT:
                                //gBattleInfo.player[target].attack = gBattleInfo.player[target].baseAttack + (gBattleInfo.player[target].baseAttack / 4) + 1;
                                gBattleInfo.player[target].attackOffset = (gBattleInfo.player[target].baseAttack / 4) + 1;
                                gBattleInfo.player[target].ttAttackR = 3;
                                break;
                            case SPELL_REVIVE:
                                if(gBattleInfo.player[target].HP <= 0)
                                    gBattleInfo.player[target].HP = gBattleInfo.player[target].baseHP / 2;
                                break;
                            case SPELL_PLY_WELL:
                                    gBattleInfo.player[target].HP += PLY_WELL_HEALTH_RECOVERED - PLY_HEALTH_RECOVERED;
                            case SPELL_PLY:
                                gBattleInfo.player[target].HP += PLY_HEALTH_RECOVERED;
                                if(gBattleInfo.player[target].HP > gBattleInfo.player[target].baseHP) {
                                    gBattleInfo.player[target].HP = gBattleInfo.player[target].baseHP;
                                    attackAnimPlaying = 2;
                                }
                                break;
                        }
                    }
                }
                gBattleInfo.camFocus = target + 1;
                break;
            case SPELL_PROTECT:
            case SPELL_HIGH_IMPACT:
            case SPELL_WISH:
                if(attackAnimTimer % 3 == 0) {
                    for(i = 0; i < 4; i++) {
                        targetObj = gBattleInfo.player[i].obj;
                        psynergyObj = spawn_object(targetObj, MODEL_NONE, bhvSparkleSpawn);
                        psynergyObj->oPosY += 150.0f;
                    }
                }
                if(attackAnimTimer == 30) {
                    u8 tempVal = 0;
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                    switch(psynergyAnimType) {
                        case SPELL_WISH:
                            for(i = 0; i < 4; i++) {
                                if(gBattleInfo.player[i].HP > 0) {
                                    gBattleInfo.player[i].HP += WISH_HEALTH_RECOVERED;
                                    if(gBattleInfo.player[i].HP > gBattleInfo.player[i].baseHP) {
                                        gBattleInfo.player[i].HP = gBattleInfo.player[i].baseHP;
                                        attackAnimPlaying = 2;
                                    }
                                }
                            }
                            break;
                        case SPELL_HIGH_IMPACT:
                            for(i = 0; i < 4; i++) {
                                if(gBattleInfo.player[i].HP != 0) {
                                    //gBattleInfo.player[i].attack = gBattleInfo.player[i].baseAttack + (gBattleInfo.player[i].baseAttack / 8) + 1;
                                    gBattleInfo.player[i].attackOffset = (gBattleInfo.player[target].baseAttack / 8) + 1;
                                    gBattleInfo.player[i].ttAttackR = 3;
                                }
                            }
                            break;
                        case SPELL_PROTECT:
                            for(i = 0; i < 4; i++) {
                                if(gBattleInfo.player[i].HP != 0) {
                                    //gBattleInfo.player[i].defense = gBattleInfo.player[i].baseDefense + (gBattleInfo.player[i].baseDefense / 8) + 1;
                                    gBattleInfo.player[i].defenseOffset = (gBattleInfo.player[target].baseDefense / 8) + 1;
                                    gBattleInfo.player[i].ttDefenseR = 3;
                                }
                            }
                            break;
                    }
                }
                gBattleInfo.camFocus = 9;
                break;
            case SPELL_QUAKE:
            case SPELL_EARTHQUAKE:
            case SPELL_QUAKE_SPHERE:
                if(attackAnimTimer % 5 == 0 && attackAnimTimer / 5 < 3) {
                        targetObj = gBattleInfo.enemy[attackAnimTimer / 5].obj;
                        if(targetObj != 0) {
                            psynergyObj = spawn_object(targetObj, MODEL_GROUND, bhvPsynergy);
                            psynergyObj->oBehParams2ndByte = SPELL_QUAKE;
                            obj_scale(psynergyObj, (f32)(psynergyAnimType - 8));
                            psynergyObj->oVelY = (psynergyAnimType - 8)*10.0f;
                            targetObj->oVelY = psynergyObj->oVelY*1.5f;
                        }
                }
                if(attackAnimTimer == 60) {
                    attackAnimDone = 1;
                    attackAnimPlaying = 0;
                    turnUserUsingAnim = turnUserID;
                }
                gBattleInfo.camFocus = 8;
                break;
        }
    } else {
        attackAnimPlaying = 0;
    }
    attackAnimTimer++;

    if(turnUserID >= 4 && gBattleInfo.camFocus == 8) {
        gBattleInfo.camFocus = 9;
    }
    return attackAnimPlaying;
}

u8 item_anim(u8 target, u8 turnUserID, u8 itemType) {
    struct Object *targetObj = gBattleInfo.player[target].obj;
    struct Object *playerObj = gBattleInfo.player[turnUserID].obj;
    u8 i;
    if(attackAnimDone == 0 && turnUserUsingAnim != turnUserID) {
        attackAnimPlaying = 1;
        if(attackAnimTimer % 3 == 0) {
            psynergyObj = spawn_object(targetObj, MODEL_NONE, bhvSparkleSpawn);
            psynergyObj->oPosY += 150.0f;
        }
        if(attackAnimTimer == 30) {
            u8 tempVal = 0;
            attackAnimDone = 1;
            attackAnimPlaying = 0;
            turnUserUsingAnim = turnUserID;
            tempVal = 0;
            if((itemType == ITEM_HERB || itemType == ITEM_CORN || itemType == ITEM_NUT) && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP == 0)
                tempVal = search_for_next_player(RANGE_SINGLE_PARTY);
            if(tempVal == 0) {
                switch(itemType) {
                    case ITEM_WATER_OF_LIFE:
                        if(gBattleInfo.player[target].HP <= 0)
                            gBattleInfo.player[target].HP = gBattleInfo.player[target].baseHP / 2;
                        break;
                    case ITEM_NUT:
                        gBattleInfo.player[target].HP += NUT_HEALTH_RECOVERED - CORN_HEALTH_RECOVERED - HERB_HEALTH_RECOVERED;
                    case ITEM_CORN:
                        gBattleInfo.player[target].HP += CORN_HEALTH_RECOVERED - HERB_HEALTH_RECOVERED;
                    case ITEM_HERB:
                        gBattleInfo.player[target].HP += HERB_HEALTH_RECOVERED;
                        if(gBattleInfo.player[target].HP > gBattleInfo.player[target].baseHP) {
                            gBattleInfo.player[target].HP = gBattleInfo.player[target].baseHP;
                            attackAnimPlaying = 2;
                        }
                        break;
                    case ITEM_PSY_CRYSTAL:
                        gBattleInfo.player[target].PP = gBattleInfo.player[target].basePP;
                        break;
                }
            }
        }
    gBattleInfo.camFocus = target + 1;
    } else {
        attackAnimPlaying = 0;
    }
    attackAnimTimer++;
    return attackAnimPlaying;
}

u8 djinn_anim(u8 inputTarget, u8 turnUserID, u8 djinnType, u8 range) {
    struct Object *targetObj;
    struct Object *playerObj = gBattleInfo.player[turnUserID].obj;
    u8 i;

    if(range == RANGE_SINGLE_PARTY || range == RANGE_ALL_PARTY) {
        targetObj = gBattleInfo.player[inputTarget].obj;
        gBattleInfo.camFocus = inputTarget + 1;
    } else {
        targetObj = gBattleInfo.enemy[inputTarget].obj;
        gBattleInfo.camFocus = inputTarget + 5;
    }
    if(attackAnimDone == 0 && turnUserUsingAnim != turnUserID) {
        attackAnimPlaying = 1;
        if(range == RANGE_SINGLE_PARTY && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[inputTarget].HP == 0) {
            search_for_next_player(RANGE_SINGLE_PARTY);
            inputTarget = target;
            targetObj = gBattleInfo.player[inputTarget].obj;
        }
        if(attackAnimTimer % 3 == 0) {
            psynergyObj = spawn_object(targetObj, MODEL_NONE, bhvSparkleSpawn);
            psynergyObj->oPosY += 150.0f;
        }
        if(attackAnimTimer == 30) {
            u8 tempVal = 0;
            attackAnimDone = 1;
            attackAnimPlaying = 0;
            turnUserUsingAnim = turnUserID;
            tempVal = 0;
            if(tempVal == 0) {
                switch(djinnType) {
                    case DJINN_ATKDOWN:
                        gBattleInfo.enemy[inputTarget].attack -= gBattleInfo.enemy[inputTarget].attack / 4;
                        break;
                    case DJINN_DEFDOWN:
                        gBattleInfo.enemy[inputTarget].defense -= gBattleInfo.enemy[inputTarget].defense / 4;
                        break;
                    case DJINN_AGIUP:
                        gBattleInfo.player[inputTarget].agilityOffset = gBattleInfo.player[inputTarget].baseAgility / 4;
                        break;
                    case DJINN_PPUP:
                        gBattleInfo.player[inputTarget].PP += gBattleInfo.player[inputTarget].basePP / 4;
                        if(gBattleInfo.player[inputTarget].PP > gBattleInfo.player[inputTarget].basePP)
                            gBattleInfo.player[inputTarget].PP = gBattleInfo.player[inputTarget].basePP;
                        break;
                }
            }
        }
    } else {
        attackAnimPlaying = 0;
    }
    attackAnimTimer++;
    return attackAnimPlaying;
}

u8 summon_anim(u8 summonType) {
    struct Object *summonObj;
    u8 i;

    if(attackAnimDone == 0 && turnUserUsingAnim != turnUserID) {
        attackAnimPlaying = 1;
        if(attackAnimTimer == 0) {
            summonObj = spawn_object(gBattleInfo.player[0].obj, MODEL_STAR, bhvSummonStar);
            summonObj->oBehParams2ndByte = summonType;
            summonObj->oPosY += 625.0f + gBattleInfo.enemy[0].obj->hitboxHeight;
            summonObj->oPosX = summonObj->oPosZ = 0;
            summonObj->oMoveAngleYaw = random_u16();
        }
        if(attackAnimTimer > 15 && attackAnimTimer % 4 == 0) {
            summonObj = spawn_object(gBattleInfo.player[0].obj, MODEL_STAR, bhvSummonStar);
            summonObj->oPosY -= 100.0f;
            summonObj->oPosX = 375.0f + ((f32)(random_u16() - 0x7FFF) / 200.0f);
            summonObj->oPosZ = -375.0f + ((f32)(random_u16() - 0x7FFF) / 200.0f);
            summonObj->oBehParams2ndByte = summonType;
            summonObj->oBehParams |= 0x00000001;
            summonObj->oMoveAngleYaw = random_u16();
        }
        if(attackAnimTimer == 90) {
            u8 tempVal = 0;
            attackAnimDone = 1;
            attackAnimPlaying = 0;
            turnUserUsingAnim = turnUserID;
        }
        gBattleInfo.camFocus = 8;
    } else {
        attackAnimPlaying = 0;
    }
    attackAnimTimer++;
    return attackAnimPlaying;
}

get_party_member_string(u8 switchBy) {
    switch(switchBy % 4) {
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

u8 search_for_next_enemy(u8 range) {
    u8 l = 1;
    u8 counter = 0;
    u8 trueTarget;
    u8 initialTarget = target;
    //target = -1;
    while(l == 1 && counter < 9) {
        target++;
        if(target > 2) {
            if(range == RANGE_ALL_ENEMIES) {
                counter = 9;
                target = 2;
            } else
                target = 0;
        }
        if(gBattleInfo.enemy[target].obj != 0) {
            l = 0;
        }
        if(target == initialTarget) {
            counter = 9;
            target = 2;
        }
        counter++;
    }
    if(counter >= 9 && l == 1)
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

const char *atkrStringTemp = "Mario";
const char *conjugation = "an ";

void conjugate_item(u8 item) {
    switch(item) {
        case ITEM_NUT:
        case ITEM_PSY_CRYSTAL:
        case ITEM_SACRED_FEATHER:
        case ITEM_WATER_OF_LIFE:
            conjugation = "a ";
        break;
        case ITEM_HERB:
            conjugation = "an ";
            break;
        case ITEM_CORN:
            conjugation = "";
            break;
    }
}

//message, player, param1, param2
//messages:
//00: djinn is set to (param1 = djinn)
//01: attack reverts to normal
//02: defense reverts to normal
//03: agility reverts to normal

u8 queued_messages[16][4] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

void add_queued_message(u8 msg, u8 player, u8 param1, u8 param2) {
    u8 i, j, queuePlacement = 0;
    for(i = 0; i < 16; i++) {
        if(queued_messages[i][0] == 0x00) {
            queuePlacement = i;
            i = 25;
        }
    }
    if(i == 16) {
        return;
    }
    queued_messages[queuePlacement][0] = msg;
    queued_messages[queuePlacement][1] = player;
    queued_messages[queuePlacement][2] = param1;
    queued_messages[queuePlacement][3] = param2;

    menuState = MENU_MESSAGES;
}

void render_queued_messages(void) {
    u8 i, j;
    s2d_init();
    switch(queued_messages[0][0]) {
        case MSG_DJINN_SET:
            get_party_member_string(queued_messages[0][1]);
            sprintf(cbuf, "%s is set to %s!", djinniPool[queued_messages[0][2]]->name, atkrString);
            break;
        case MSG_ATK_REVERT:
            get_party_member_string(queued_messages[0][1]);
            sprintf(cbuf, "%s's attack reverts to normal!", atkrString);
            break;
        case MSG_DEF_REVERT:
            get_party_member_string(queued_messages[0][1]);
            sprintf(cbuf, "%s's defense reverts to normal!", atkrString);
            break;
        case MSG_AGI_REVERT:
            get_party_member_string(queued_messages[0][1]);
            sprintf(cbuf, "%s's agility reverts to normal!", atkrString);
            break;
    }

    print_battle_text();

    if(gPlayer1Controller->buttonPressed & A_BUTTON) {
        render_previous_text();
        if(queued_messages[1][0] != 0) {
            for(i = 0; i < 14; i++) {
                for(j = 0; j < 4; j++) {
                    queued_messages[i][j] = queued_messages[i + 1][j];
                }
            }
        } else {
            menuState = MENU_START;
        }
    }
    s2d_stop();
}

void render_flee_text(void) {
    s2d_init();

    cbuf_prev[0] = 0;
    sprintf(cbuf, "The party flees!");
    print_battle_text();
    if(gPlayer1Controller->buttonPressed & A_BUTTON) {
        play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
        exit_battle();
    }
    s2d_stop();
}

u8 targetingParty = 0;
u8 winTextProgress = 0;
u8 winTextDone = 0;
struct Spell **movePool;
u8 spellUsed, itemUsed;
struct Djinni *djinnUsed;
struct Summon *summonUsed;
struct Enemy *currEnemy;

void render_battle_attack_text(void) {
    u8 k, l, i, j;

    gBattleInfo.camState = CAMERA_ACTION;
    s2d_init();
    turnUserID = turnOrder[gBattleInfo.turnUser];
    gBattleInfo.camFocus = 0;
    if(isAttackDone == 0) {
        if(turnUserID < 4) {
            get_party_member_string(turnUserID);
            if(targetingParty == 1) {
                target = gBattleInfo.player[turnUserID].target[targetNo];
            } else {
                target = gBattleInfo.player[turnUserID].target[targetNo] - 4;
            }
            switch(gBattleInfo.player[turnUserID].action) {
                case ACT_ATTACK:
                    switch(gBattleInfo.turnActionProgress) {
                        case 0:
                            if(gBattleInfo.enemy[target].obj == 0) {
                                search_for_next_enemy(0);
                            }
                            else {
                                sprintf(cbuf, "%s attacks!", atkrString);
                                animAboutToPlay = 1;
                            }
                            break;
                        case 1:
                            animPlaying = player_attack_anim(target, turnUserID, 0);
                            if(animPlaying == 0) {
                                if(animAboutToPlay == 1) {
                                    render_previous_text();
                                }
                                animAboutToPlay = 0;
                                damage = calculate_damage(gBattleInfo.player[turnUserID].attack + (gSaveBuffer.files[gCurrSaveFileNum - 1][0].level), gBattleInfo.enemy[target].defense, 0, 1);
                                sprintf(cbuf, "%s takes %d damage!", gBattleInfo.enemy[target].name, damage);
                            }
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
                                if(movePool[spellUsed]->range == RANGE_SINGLE_PARTY || movePool[spellUsed]->range == RANGE_ALL_PARTY)
                                    targetingParty = 1;
                                else
                                    targetingParty = 0;
                                if(gBattleInfo.enemy[target].obj == 0 && targetingParty == 0) {
                                    search_for_next_enemy(movePool[spellUsed]->range);
                                }
                                else {
                                    sprintf(cbuf, "%s casts %s!", atkrString, movePool[spellUsed]->name);
                                    animAboutToPlay = 1;
                                }
                                break;
                            case 1:
                                animPlaying = psynergy_anim(target, turnUserID, movePool[spellUsed]->sprite);
                                if(animPlaying != 1) {
                                    if(animAboutToPlay == 1) {
                                        gBattleInfo.player[turnUserID].PP -= movePool[spellUsed]->PP;
                                        render_previous_text();
                                    }
                                    animAboutToPlay = 0;
                                    if(targetingParty == 0) {
                                        damage = calculate_damage(gBattleInfo.player[turnUserID].attack + movePool[spellUsed]->damage, gBattleInfo.enemy[target].defense, gBattleInfo.player[turnUserID].element, gBattleInfo.enemy[target].element);
                                        sprintf(cbuf, "%s takes %d damage!", gBattleInfo.enemy[target].name, damage);
                                    } else {
                                        get_party_member_string(target);
                                        switch(movePool[spellUsed]->sprite) {
                                            case SPELL_GUARD:
                                                sprintf(cbuf, "%s's defense is raised!", atkrString);
                                                break;
                                            case SPELL_IMPACT:
                                                sprintf(cbuf, "%s's attack is raised!", atkrString);
                                                break;
                                            case SPELL_PLY:
                                                if(animPlaying == 2)
                                                    sprintf(cbuf, "%s recovered all HP!", atkrString);
                                                else
                                                    sprintf(cbuf, "%s recovered 50 HP!", atkrString);
                                                break;
                                            case SPELL_PLY_WELL:
                                                if(animPlaying == 2)
                                                    sprintf(cbuf, "%s recovered all HP!", atkrString);
                                                else
                                                    sprintf(cbuf, "%s recovered 150 HP!", atkrString);
                                                break;
                                            case SPELL_PROTECT:
                                                sprintf(cbuf, "The party's defense is raised!");
                                                break;
                                            case SPELL_HIGH_IMPACT:
                                                sprintf(cbuf, "The party's attack is raised!");
                                                break;
                                            case SPELL_REVIVE:
                                                sprintf(cbuf, "%s is revived!", atkrString);
                                                break;
                                            case SPELL_WISH:
                                                sprintf(cbuf, "The party recovered 80 HP!");
                                                break;
                                        }
                                        animPlaying = 0;
                                    }
                                }
                                break;
                            case 2:
                                if(targetingParty == 0) {
                                    apply_damage(damage, target + 4);
                                    if(targetDead == 0)
                                        isAttackDone = 1;
                                    else {
                                        animPlaying = enemy_death(target);
                                        sprintf(cbuf, "You felled %s!", gBattleInfo.enemy[target].name);
                                    }
                                } else {
                                    isAttackDone = 1;
                                }
                                break;
                            case 3:
                                isAttackDone = 1;
                                break;
                    }
                    break;
                case ACT_DEFEND:
                    switch(gBattleInfo.turnActionProgress) {
                        case 0:
                            sprintf(cbuf, "%s is defending!", atkrString);
                            break;
                        case 1:
                            isAttackDone = 1;
                            break;
                    }
                    break;
                case ACT_ITEM:
                    itemUsed = gBattleInfo.player[turnUserID].subAction;
                    switch(gBattleInfo.turnActionProgress) {
                        case 0:
                            targetingParty = 1;
                            if(gBattleInfo.player[target].HP == 0) {
                                search_for_next_player(RANGE_SINGLE_PARTY);
                            }
                            conjugate_item(itemUsed);
                            sprintf(cbuf, "%s used %s%s!", atkrString, conjugation, items[itemUsed]);
                            animAboutToPlay = 1;
                            break;
                        case 1:
                            animPlaying = item_anim(target, turnUserID, itemUsed);
                            if(animPlaying != 1) {
                                if(animAboutToPlay == 1) {
                                    for(j = 0; j < 8; j++) {
                                        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[j].id == itemUsed) {
                                            i = j;
                                            j = 0xFE;
                                        }
                                    }
                                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].number--;
                                    render_previous_text();
                                }
                                animAboutToPlay = 0;
                                get_party_member_string(target);
                                switch(itemUsed) {
                                    case ITEM_HERB:                                      
                                        if(animPlaying == 2)
                                            sprintf(cbuf, "%s recovered all HP!", atkrString);
                                        else
                                            sprintf(cbuf, "%s recovered 25 HP!", atkrString);
                                        break;
                                    case ITEM_CORN:                                      
                                        if(animPlaying == 2)
                                            sprintf(cbuf, "%s recovered all HP!", atkrString);
                                        else
                                            sprintf(cbuf, "%s recovered 50 HP!", atkrString);
                                        break;
                                    case ITEM_NUT:                                      
                                        if(animPlaying == 2)
                                            sprintf(cbuf, "%s recovered all HP!", atkrString);
                                        else
                                            sprintf(cbuf, "%s recovered 150 HP!", atkrString);
                                        break;
                                    case ITEM_PSY_CRYSTAL:
                                        sprintf(cbuf, "%s recovered all PP!", atkrString);
                                        break;
                                    case ITEM_WATER_OF_LIFE:
                                        sprintf(cbuf, "%s is revived!", atkrString);
                                        break;
                                    }
                                    animPlaying = 0;
                                }
                            break;
                        case 2:
                            isAttackDone = 1;
                            break;
                        case 3:
                            isAttackDone = 1;
                            break;
                        }
                    break;
                case ACT_DJINN:
                    djinnUsed = djinniPool[gBattleInfo.player[turnUserID].subAction];
                    switch(gBattleInfo.turnActionProgress) {
                        case 0:
                            if(djinnUsed->range == RANGE_SINGLE_PARTY || djinnUsed->range == RANGE_ALL_PARTY)
                                targetingParty = 1;
                            else
                                targetingParty = 0;
                            if(gBattleInfo.enemy[target].obj == 0 && targetingParty == 0) {
                                search_for_next_enemy(djinnUsed->range);
                            }
                            else if(gBattleInfo.player[target].HP == 0 && targetingParty == 1) {
                                search_for_next_player(RANGE_SINGLE_PARTY);
                            } else {
                                sprintf(cbuf, "%s unleashes %s!", atkrString, djinnUsed->name);
                                animAboutToPlay = 1;
                            }
                            break;
                        case 1:
                            animPlaying = djinn_anim(target, turnUserID, djinnUsed->id, djinnUsed->range);
                            if(animPlaying != 1) {
                                if(animAboutToPlay == 1) {
                                    render_previous_text();
                                }
                                animAboutToPlay = 0;
                                get_party_member_string(target);
                                switch(djinnUsed->id) {
                                    case DJINN_ATKDOWN:
                                        sprintf(cbuf, "%s's attack is lowered!", gBattleInfo.enemy[target].name);
                                        break;
                                    case DJINN_DEFDOWN:
                                        sprintf(cbuf, "%s's defense is lowered!", gBattleInfo.enemy[target].name);
                                        break;
                                    case DJINN_AGIUP:
                                        sprintf(cbuf, "%s's agility is raised!", atkrString);
                                        break;
                                    case DJINN_PPUP:
                                        sprintf(cbuf, "%s recovered some PP!", atkrString);
                                        break;
                                    }
                                    animPlaying = 0;
                                }
                            break;
                        case 2:
                            gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[turnUserID].activeState = DJINN_INACTIVE;
                            isAttackDone = 1;
                            break;
                        case 3:
                            isAttackDone = 1;
                            break;
                    }
                    break;
                case ACT_SUMMON:
                    summonUsed = summonPool[gBattleInfo.player[turnUserID].subAction];
                    switch(gBattleInfo.turnActionProgress) {
                        case 0:
                            targetingParty = 0;
                            sprintf(cbuf, "%s summons %s!", atkrString, summonUsed->name);
                            animAboutToPlay = 1;
                            break;
                        case 1:
                            animPlaying = summon_anim(summonUsed->id);
                            if(animPlaying != 1) {
                                if(animAboutToPlay == 1) {
                                    render_previous_text();
                                }
                                animAboutToPlay = 0;
                                damage = calculate_damage(gBattleInfo.player[turnUserID].attack + summonUsed->damage, gBattleInfo.enemy[target].defense, summonUsed->element, gBattleInfo.enemy[target].element);
                                sprintf(cbuf, "%s takes %d damage!", gBattleInfo.enemy[target].name, damage);
                                animPlaying = 0;
                            }
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
            currEnemy = &gBattleInfo.enemy[turnUserID - 4];
            target = currEnemy->target[targetNo];
            switch(currEnemy->action) {
                case ACT_ATTACK:
                    switch(gBattleInfo.turnActionProgress) {
                        case 0:
                            sprintf(cbuf, "%s attacks!", currEnemy->name);
                            animAboutToPlay = 1;
                            break;
                        case 1:
                            animPlaying = enemy_attack_anim(target, turnUserID, 0);
                            if(animPlaying == 0) {
                                if(animAboutToPlay == 1) {
                                    render_previous_text();
                                }
                                animAboutToPlay = 0;
                                get_party_member_string(target);
                                damage = calculate_damage(currEnemy->attack, gBattleInfo.player[target].defense, 0, 1);
                                sprintf(cbuf, "%s takes %d damage!", atkrString, damage);
                            }
                            break;
                        case 2:
                            if(targetDead == 0) {
                                get_party_member_string(target);
                                atkrStringTemp = atkrString;
                                apply_damage(damage, target);
                            }
                            if(targetDead == 0)
                                isAttackDone = 1;
                            else {
                                sprintf(cbuf, "%s goes down...", atkrStringTemp);
                            }
                            break;
                        case 3:
                            isAttackDone = 1;
                            break;
                    }
                    break;
                case ACT_PSYNERGY:
                    movePool = EnemySpellPool[currEnemy->id];
                    spellUsed = gBattleInfo.enemy[turnUserID - 4].subAction;
                        switch(gBattleInfo.turnActionProgress) {
                            case 0:
                                if(movePool[spellUsed]->range == RANGE_SINGLE_PARTY || movePool[spellUsed]->range == RANGE_ALL_PARTY)
                                    targetingParty = 1;
                                else
                                    targetingParty = 0;

                                sprintf(cbuf, "%s casts %s!", currEnemy->name, movePool[spellUsed]->name);
                                animAboutToPlay = 1;
                                break;
                            case 1:
                                animPlaying = psynergy_anim(target, turnUserID, movePool[spellUsed]->sprite);
                                if(animPlaying != 1) {
                                    if(animAboutToPlay == 1) {
                                        render_previous_text();
                                    }
                                    animAboutToPlay = 0;
                                    if(targetingParty == 0) {
                                        damage = calculate_damage(currEnemy->attack + movePool[spellUsed]->damage, gBattleInfo.player[target].defense, currEnemy->element, gBattleInfo.player[target].element);
                                        get_party_member_string(target);
                                        sprintf(cbuf, "%s takes %d damage!", atkrString, damage);
                                    } else {
                                        get_party_member_string(target);
                                        switch(movePool[spellUsed]->sprite) {
                                            case SPELL_GUARD:
                                                sprintf(cbuf, "%s's defense is raised!", atkrString);
                                                break;
                                            case SPELL_IMPACT:
                                                sprintf(cbuf, "%s's attack is raised!", atkrString);
                                                break;
                                            case SPELL_PLY:
                                                if(animPlaying == 2)
                                                    sprintf(cbuf, "%s recovered all HP!", atkrString);
                                                else
                                                    sprintf(cbuf, "%s recovered 50 HP!", atkrString);
                                                break;
                                            case SPELL_PLY_WELL:
                                                if(animPlaying == 2)
                                                    sprintf(cbuf, "%s recovered all HP!", atkrString);
                                                else
                                                    sprintf(cbuf, "%s recovered 150 HP!", atkrString);
                                                break;
                                            case SPELL_PROTECT:
                                                sprintf(cbuf, "The party's defense is raised!");
                                                break;
                                            case SPELL_HIGH_IMPACT:
                                                sprintf(cbuf, "The party's attack is raised!");
                                                break;
                                            case SPELL_REVIVE:
                                                sprintf(cbuf, "%s is revived!", atkrString);
                                                break;
                                            case SPELL_WISH:
                                                sprintf(cbuf, "The party recovered 80 HP!");
                                                break;
                                        }
                                        animPlaying = 0;
                                    }
                                }
                                break;
                            case 2:
                                if(targetDead == 0) {
                                    get_party_member_string(target);
                                    atkrStringTemp = atkrString;
                                    apply_damage(damage, target);
                                }
                                if(targetDead == 0)
                                    isAttackDone = 1;
                                else {
                                    sprintf(cbuf, "%s goes down...", atkrStringTemp);
                                }
                                break;
                            case 3:
                                isAttackDone = 1;
                                break;
                    }
                    break;
                }
        }
    }
    if(isAttackDone == 0) {
        print_battle_text();
    }
    s2d_stop();
    if((gPlayer1Controller->buttonPressed & A_BUTTON || isAttackDone == 1) && animPlaying != 1) {
        u16 i, tempTargetNo;
        reset_attack_anim();
        for(i = 0; i < 4; i++) {
            reset_player(i);
        }
        for(i = 4; i < 7; i++) {
            reset_enemy(i);
        }
        if(isAttackDone == 1) {
            targetNo++;
            if(turnUserID < 4 && (targetNo >= 3 || gBattleInfo.player[turnUserID].target[targetNo] == 0xFF || gBattleInfo.player[turnUserID].target[targetNo] < 4)) {
                k = 1;
            } else if(turnUserID >= 4 && (targetNo >= 4 || gBattleInfo.enemy[turnUserID - 4].target[targetNo] == 0xFF)) {
                k = 1;
            } else if (turnUserID < 4 && gBattleInfo.player[turnUserID].target[targetNo] > 3 && gBattleInfo.player[turnUserID].target[targetNo] != 0xFF && gBattleInfo.enemy[gBattleInfo.player[turnUserID].target[targetNo] - 4].obj == 0) {
                if(gBattleInfo.player[turnUserID].action == ACT_PSYNERGY) {
                    movePool = SpellPool[turnUserID];
                    spellUsed = gBattleInfo.player[turnUserID].subAction;
                    k = search_for_next_enemy(movePool[spellUsed]->range);
                }
                else
                    k = search_for_next_enemy(0);
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
                    winTextProgress = 0;
                    stop_background_music(sBackgroundMusicQueue[0].seqId);
                    play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, SEQ_VICTORY), 0);
                    render_previous_text();
                }
                if(gBattleInfo.player[0].HP == 0 && gBattleInfo.player[1].HP == 0 && gBattleInfo.player[2].HP == 0 && gBattleInfo.player[3].HP == 0) {
                    menuState = MENU_LOSE;
                    render_previous_text();
                }
                if(gBattleInfo.player[turnUserID].action == ACT_SUMMON) {
                    summonUsed = summonPool[gBattleInfo.player[turnUserID].subAction];
                    for(i = 0; i < 4; i++) {
                        if(summonUsed->elements[i] != 0) {
                            k = 0;
                            for(j = 0; j < 4; j++) {
                                if(djinniPool[j]->element == i && gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[j].activeState == DJINN_INACTIVE) {
                                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[j].turnsUntilActive = k + 2;
                                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[j].activeState = DJINN_ACTIVE;
                                    k++;
                                }
                                if(k >= summonUsed->elements[i]) {
                                    j = 4;
                                }
                            }
                        }
                    }
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
                if(animAboutToPlay == 0)
                    render_previous_text();
            }
            else {
                    isAttackDone = 1;
                    render_previous_text();
            }
        }
        while(turnOrder[gBattleInfo.turnUser] == 0xFF && gBattleInfo.turnUser < 7) {
            if(gBattleInfo.turnUser == 7) {

                //??? what does this do
                menuState = MENU_START;
                
            } else {
                gBattleInfo.turnUser++;
                targetNo = 0;
                if(gBattleInfo.player[0].HP == 0 && gBattleInfo.player[1].HP == 0 && gBattleInfo.player[2].HP == 0 && gBattleInfo.player[3].HP == 0) {
                    menuState = MENU_LOSE;
                    render_previous_text();
                }
            }
        }
        if(gBattleInfo.turnUser == 7 && menuState == MENU_TURN) {
                menuState = MENU_START;
                gBattleInfo.selectingUser = 0;
                for(i = 0; i < 4; i++) {
                    gBattleInfo.player[i].target[0] = gBattleInfo.player[i].target[1] = gBattleInfo.player[i].target[2] = 0xFF;
                    if(gBattleInfo.player[i].ttAttackR > 0) {
                        gBattleInfo.player[i].ttAttackR--;
                        if(gBattleInfo.player[i].ttAttackR == 0) {
                            gBattleInfo.player[i].attackOffset = 0;
                            add_queued_message(MSG_ATK_REVERT, i, 0, 0);
                        }
                    }
                    if(gBattleInfo.player[i].ttDefenseR > 0) {
                        gBattleInfo.player[i].ttDefenseR--;
                        if(gBattleInfo.player[i].ttDefenseR == 0) {
                            gBattleInfo.player[i].defenseOffset = 0;
                            add_queued_message(MSG_DEF_REVERT, i, 0, 0);
                        }
                    }
                    if(gBattleInfo.player[i].ttAgilityR > 0) {
                        gBattleInfo.player[i].ttAgilityR--;
                        if(gBattleInfo.player[i].ttAgilityR == 0) {
                            gBattleInfo.player[i].agilityOffset = 0;
                            add_queued_message(MSG_AGI_REVERT, i, 0, 0);
                        }
                    }
                }
                for(i = 0; i < 3; i++) {
                    gBattleInfo.enemy[i].target[0] = gBattleInfo.enemy[i].target[1] = gBattleInfo.enemy[i].target[2] = gBattleInfo.enemy[i].target[3] = 0xFF;
                }
                for(i = 0; i < 4; i++) {
                    if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].turnsUntilActive > 0) {
                        gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].turnsUntilActive--;
                        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].turnsUntilActive == 0) {
                            add_queued_message(MSG_DJINN_SET, i, i, 0);
                        }
                    }
                }
        }
    }
}

u16 stat_calc(u8 modValue, u8 player, u8 boostCase1, u8 boostCase2) {
    u16 tempStat = (random_u16() % modValue);
    if(player == boostCase1 || player == boostCase2) {
        if(tempStat > modValue - 1)
        tempStat = modValue - 1;
    } else {
        tempStat = random_u16() % (modValue - 1);
    }
    return tempStat;
}

u8 rngBoost = 0;
void calculate_new_stats(u8 newLevel, u8 oldLevel) {
    u8 i, j;
    u16 tempStat;
    struct Player *player;
    struct BattlePlayer *bPlayer;
    for(i = 0; i < newLevel - oldLevel; i++) {
        for(j = 0; j < 4; j++) {
            player = &gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[j];
            bPlayer = &gBattleInfo.player[j];
            tempStat = stat_calc(4, j, 3, 3);
            bPlayer->baseHP = player->baseHP = player->trueBaseHP += (tempStat + 1);
            if(bPlayer->HP > 0) {
                bPlayer->HP += (tempStat + 1);
            }
            player->HP = bPlayer->HP;
            tempStat = stat_calc(3, j, 2, 3);
            bPlayer->basePP = player->basePP = player->trueBasePP += (tempStat + 1);
            player->PP = bPlayer->PP += (tempStat + 1);
            tempStat = stat_calc(3, j, 0, 0);
            player->attack += (tempStat + 1);
            tempStat = stat_calc(3, j, 1, 1);
            player->defense += (tempStat + 1);
            tempStat = stat_calc(3, j, 2, 2);
            player->agility += (tempStat + 1);

        }
    }
}

u8 testValue = 0;
u8 tempLevel = 0;
u8 calculate_level(u32 expEarned) {
    u8 oldLevel = gSaveBuffer.files[gCurrSaveFileNum - 1][0].level;
    gSaveBuffer.files[gCurrSaveFileNum - 1][0].exp += expEarned;
    testValue = 0;
    tempLevel = 0;
    while(testValue == 0 && tempLevel < 99) {
        if((tempLevel*6)*(tempLevel*3) >= gSaveBuffer.files[gCurrSaveFileNum - 1][0].exp) {
            testValue = 1;
        } else {
            tempLevel++;
        }
    }
    gSaveBuffer.files[gCurrSaveFileNum - 1][0].level = tempLevel;
    if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].level != oldLevel) {
        calculate_new_stats(gSaveBuffer.files[gCurrSaveFileNum - 1][0].level, oldLevel);
        return 1;
    } else {
        return 0;
    }
}

u32 expGained;
void render_battle_win_text(void) {
    u8 i = 0;
    s2d_init();
    switch(winTextProgress) {
        case 0:
            sprintf(cbuf, "You win!");
            break;
        case 1:
            expGained = 0;
            for(i = 0; i <= gBattleInfo.totalEnemies; i++) {
                expGained += gBattleInfo.enemy[i].expYield;
            }
            sprintf(cbuf, "You got %d EXP!", expGained);
            break;
        case 2:
            sprintf(cbuf, "Everyone has leveled up!");
            break;
    }
    print_battle_text();
    s2d_stop();

    if(gPlayer1Controller->buttonPressed & A_BUTTON) {
        render_previous_text();
        winTextProgress++;
        if(winTextProgress == 2) {
            u8 gainedLevel = 0;
            gainedLevel = calculate_level(expGained);
            if(gainedLevel == 0) {
                exit_battle();
            }
        }
        if(winTextProgress == 3) {
            exit_battle();
        }
    }
}

void render_battle_lose_text(void) {
    s2d_init();
    sprintf(cbuf, "You lost...");
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

u8 color = 0;
void render_health(void) {
    u8 i;

    update_actual_stats();

    s2d_init();
    //for(i = 0; i <= gCharactersUnlocked; i++) {
    //    render_bar_wh(320 - ((i+1)*64), 0, 64, 32);
    //}
    gCharactersUnlocked = gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked;
    render_battle_fill_rect(0, 0, 320, 32, 0x00, 0x00, 0x00);
    render_bar_wh(320 - ((gCharactersUnlocked+2)*64), 0, (gCharactersUnlocked+2)*64, 32);
    for(i = 0; i <= gCharactersUnlocked; i++) {
        render_battle_fill_rect(320 - (i+1)*64, 4, 321 - (i+1)*64, 28, 0x00, 0x97, 0xE2);
        render_battle_fill_rect(319 - (i+1)*64, 4, 320 - (i+1)*64, 28, 0x00, 0x37, 0x41);
        render_battle_fill_rect(261 - (i)*64, 0, 298 - (i)*64, 8, 0x00, 0x5A, 0x84);
        get_party_member_string(gCharactersUnlocked - i);
        sprintf(hbuf, "%s", atkrString);

        if(menuState == MENU_PAUSE) {
            gBattleInfo.player[gCharactersUnlocked - i].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[gCharactersUnlocked - i].HP;
            gBattleInfo.player[gCharactersUnlocked - i].PP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[gCharactersUnlocked - i].PP;
            gBattleInfo.player[gCharactersUnlocked - i].baseHP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[gCharactersUnlocked - i].baseHP;
            gBattleInfo.player[gCharactersUnlocked - i].basePP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[gCharactersUnlocked - i].basePP;
        }

        if(gBattleInfo.player[gCharactersUnlocked - i].HP <= 0) {
            color = RED;
        } else if(gBattleInfo.player[gCharactersUnlocked - i].HP <= (gBattleInfo.player[gCharactersUnlocked - i].baseHP / 4)) {
            color = YELLOW;
        } else {
            color = WHITE;
        }
        gs_print(256 - (i*64), 0, hbuf, SHADOW, color);

        render_battle_fill_rect(260 - (i)*64, 15, 308 - (i)*64, 18, 0xDB, 0x00, 0x00);
        render_battle_fill_rect(260 - (i)*64, 15, 260 - (i)*64 + (s32)(((f32)gBattleInfo.player[gCharactersUnlocked - i].HP / (f32)gBattleInfo.player[gCharactersUnlocked - i].baseHP)*48.0f), 18, 0x00, 0x00, 0xD0);
        sprintf(hbuf, "HP %d", gBattleInfo.player[gCharactersUnlocked - i].HP);
        gs_print(256 - (i*64), 10, hbuf, SHADOW, color);
        render_battle_fill_rect(260 - (i)*64, 25, 308 - (i)*64, 28, 0xDB, 0x00, 0x00);
        render_battle_fill_rect(260 - (i)*64, 25, 260 - (i)*64 + (s32)(((f32)gBattleInfo.player[gCharactersUnlocked - i].PP / (f32)gBattleInfo.player[gCharactersUnlocked - i].basePP)*48.0f), 28, 0x00, 0x00, 0xD0);
        sprintf(hbuf, "PP %d", gBattleInfo.player[gCharactersUnlocked - i].PP);
        if(gBattleInfo.player[gCharactersUnlocked - i].PP <= 0) {
            color = RED;
        } else if(gBattleInfo.player[gCharactersUnlocked - i].PP < (gBattleInfo.player[gCharactersUnlocked - i].basePP / 4)) {
            color = YELLOW;
        } else {
            color = WHITE;
        }
        gs_print(256 - (i*64), 20, hbuf, SHADOW, color);
    }
    call_element_sprite_dl(0, 198 - (gCharactersUnlocked*64), 6, &hebuf[0]);
    call_element_sprite_dl(1, 198 - (gCharactersUnlocked*64), 18, &hebuf[1]);
    call_element_sprite_dl(2, 230 - (gCharactersUnlocked*64), 18, &hebuf[2]);
    call_element_sprite_dl(3, 230 - (gCharactersUnlocked*64), 6, &hebuf[3]);

    sprintf(hbuf, " %d", gBattleInfo.djinnUsed[0]);
    gs_print(196 - (gCharactersUnlocked*64), 6, hbuf, SHADOW, WHITE);
    sprintf(hbuf, " %d", gBattleInfo.djinnUsed[1]);
    gs_print(196 - (gCharactersUnlocked*64), 18, hbuf, SHADOW, WHITE);
    sprintf(hbuf, " %d", gBattleInfo.djinnUsed[2]);
    gs_print(228 - (gCharactersUnlocked*64), 6, hbuf, SHADOW, WHITE);
    sprintf(hbuf, " %d", gBattleInfo.djinnUsed[3]);
    gs_print(228 - (gCharactersUnlocked*64), 18, hbuf, SHADOW, WHITE);
    s2d_stop();
}

void initialize_player(u8 player) {
    u8 modelID;
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
    partyStats->baseHP = partyStats->trueBaseHP = file->baseHP;
    partyStats->basePP = partyStats->trueBasePP = file->basePP;

    // if(player == 0) {
    //     gBattleInfo.player[0].obj = gMarioObject;
    //     gMarioState->pos[0] = gMarioState->pos[2] = gMarioObject->oPosX = gMarioObject->oPosZ = (-62.5*gCharactersUnlocked);
    //     gMarioState->pos[1] = gMarioObject->oPosY = -11000.0f;
    //     vec3f_copy(gMarioObject->header.gfx.pos, gMarioState->pos);
    //     gMarioObject->header.gfx.angle[1] = 0x6000;
    // } else {
        if(partyStats->obj == 0) {
            switch(player) {
                case 1:
                    modelID = MODEL_VERIO;
                    break;
                case 2:
                    modelID = MODEL_JURIO;
                    break;
                case 3:
                    modelID = MODEL_MERIO;
                    break;
                default:
                    modelID = MODEL_MARIO;
                    break;
            }
            partyStats->obj = spawn_object(gMarioObject, modelID, bhvPartyMember);
        }
        partyStats->obj->oPosX = (-62.5*gCharactersUnlocked) + (125.0f*player);
        partyStats->obj->oPosZ = (-62.5*gCharactersUnlocked) + (125.0f*player);
        partyStats->obj->oPosY = -11000.0f;
        partyStats->obj->oMoveAngleYaw = 0x6000;
        partyStats->obj->oMoveAnglePitch = partyStats->obj->oMoveAngleRoll = 0;
        partyStats->obj->oBehParams2ndByte = player;
    //}
}

void initialize_battle(void) {
    u8 i, enemiesSelected, areaIn, maxEnemyTypes;
    u8 (*enemyPool)[3];
    struct Object *enemyTemp;
    gCharactersUnlocked = gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked;
    gBattleInfo.selectingUser = 0;
    gBattleInfo.totalEnemies = 0;
    for(i = 0; i < 7; i++) {
        turnOrder[i] = 0;
    }

    if(gCurrCourseNum != 1)
        areaIn = 0;
    else
        areaIn = gCurrAreaIndex;
    switch(areaIn) {
        case 0:
            enemyPool = GrassEnemyPool;
            maxEnemyTypes = GRASS_POOL_MAX;
            break;
        case 1:
            enemyPool = Area1EnemyPool;
            maxEnemyTypes = AREA_1_POOL_MAX;
            break;
        case 2:
            enemyPool = Area2EnemyPool;
            maxEnemyTypes = AREA_2_POOL_MAX;
            break;
        case 3:
            enemyPool = Area3EnemyPool;
            maxEnemyTypes = AREA_3_POOL_MAX;
            break;
        case 4:
            enemyPool = Area4EnemyPool;
            maxEnemyTypes = AREA_4_POOL_MAX;
            break;
        case 5:
            enemyPool = Area5EnemyPool;
            maxEnemyTypes = AREA_5_POOL_MAX;
            break;
        case 6:
            enemyPool = Area6EnemyPool;
            maxEnemyTypes = AREA_6_POOL_MAX;
    }
    enemiesSelected = random_u16() % maxEnemyTypes;
    for(i = 0; i < 3; i++) {
        if(i <= gCharactersUnlocked && enemyPool[enemiesSelected][i] != ENEMY_NONE) {
            gBattleInfo.enemy[i].obj = enemyTemp = spawn_object(gMarioObject, MODEL_NONE, bhvEnemy);
            gBattleInfo.enemy[i].id = enemyPool[enemiesSelected][i];
            enemyTemp->oBehParams2ndByte = i;
            gBattleInfo.totalEnemies = i;
        }
    }
    targetDead = 0;
    targetNo = 0;
    vec3f_copy(gBattleInfo.lastPos, gMarioState->pos);
    vec3f_copy(gBattleInfo.lastCamPos, gCamera->pos);
    start_cutscene(gCamera, CUTSCENE_BATTLE);
    gBattleInfo.lastSeq = sBackgroundMusicQueue[0].seqId;
    stop_background_music(sBackgroundMusicQueue[0].seqId);
    if(gCurrAreaIndex == 6) {
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, SEQ_SATUROS_MENARDI), 0);
    } else {
        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, SEQ_BATTLE), 0);
    }
    copy_mario_state_to_object();
    for(i = 0; i <= gCharactersUnlocked; i++) {
        initialize_player(i);
    }
}

void update_inventory(void) {
    u8 i, j;
    for(j = 0; j < 8; j++) {
        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[j].number <= 0) {
            for(i = j; i < 7; i++) {
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].id = gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i + 1].id;
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].number = gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i + 1].number;
            }
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[7].id = 0xFF;
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].number = 0;
        }
    }
}

void update_djinn_used(void) {
    u8 i, j;
    for(i = 0; i < 4; i++) {
        gBattleInfo.djinnUsed[i] = 0;
    }
    for(i = 0; i < 4; i++) {
        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].activeState == DJINN_INACTIVE) {
            gBattleInfo.djinnUsed[djinniPool[i]->element]++;
        }
    }
    if(gMarioState->action == ACT_BATTLE) {
        for(i = 0; i < 4; i++) {
            if(gBattleInfo.player[i].action == ACT_SUMMON) {
                for(j = 0; j < 4; j++) {
                    if(!((menuState == MENU_TURN || menuState == MENU_MESSAGES || menuState == MENU_LOSE || menuState == MENU_WIN)&& gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[j].activeState == DJINN_ACTIVE))
                        gBattleInfo.djinnUsed[j] -= summonPool[gBattleInfo.player[i].subAction]->elements[j];
                }
            }
        }
    }
}

void update_items_used(void) {
    u8 i, j, k, itemMax;
    for(i = 0; i < 8; i++) {
        fauxInventory[i][0] = gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].id;
        fauxInventory[i][1] = gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory[i].number;
    }
    itemMax = 8;
    for(i = 0; i < 4; i++) {
        if(gBattleInfo.player[i].action == ACT_ITEM) {
            for(j = 0; j < itemMax; j++) {
                if(gBattleInfo.player[i].subAction == fauxInventory[j][0] && fauxInventory[j][1] > 0) {
                    fauxInventory[j][1]--;
                    if(fauxInventory[j][1] == 0) {
                        itemMax--;
                        for(k = j; k < itemMax; k++) {
                            fauxInventory[k][0] = fauxInventory[k + 1][0];
                            fauxInventory[k][1] = fauxInventory[k + 1][1];
                        }
                    }
                }
            }
        }
    }
}

void update_actual_stats(void) {
    u8 i, djinnOffset;
    for(i = 0; i < 4; i++) {
        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].turnsUntilActive == 0 && gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].activeState == DJINN_ACTIVE && (gSaveBuffer.files[gCurrSaveFileNum - 1][0].courseStars[0] & (1 << i)) != 0) {
            djinnOffset = (gSaveBuffer.files[gCurrSaveFileNum - 1][0].level / 2) + 1;
        } else {
            djinnOffset = 0;
        }
        if(gMarioState->action == ACT_BATTLE) {
            gBattleInfo.player[i].attack = gBattleInfo.player[i].baseAttack + gBattleInfo.player[i].attackOffset + djinnOffset;
            gBattleInfo.player[i].defense = gBattleInfo.player[i].baseDefense + gBattleInfo.player[i].defenseOffset+ djinnOffset;
            gBattleInfo.player[i].agility = gBattleInfo.player[i].baseAgility + gBattleInfo.player[i].agilityOffset+ djinnOffset;
            if(gBattleInfo.player[i].baseHP < gBattleInfo.player[i].trueBaseHP + djinnOffset*2 && gBattleInfo.player[i].HP != 0) {
                gBattleInfo.player[i].HP += djinnOffset*2;
            }
            gBattleInfo.player[i].baseHP = gBattleInfo.player[i].trueBaseHP + djinnOffset*2;
            if(gBattleInfo.player[i].HP > gBattleInfo.player[i].baseHP) {
                gBattleInfo.player[i].HP = gBattleInfo.player[i].baseHP;
            }
            if(gBattleInfo.player[i].basePP < gBattleInfo.player[i].trueBasePP + djinnOffset*2 && gBattleInfo.player[i].PP != 0) {
                gBattleInfo.player[i].PP += djinnOffset*2;
            }
            gBattleInfo.player[i].basePP = gBattleInfo.player[i].trueBasePP + djinnOffset*2;
            if(gBattleInfo.player[i].PP > gBattleInfo.player[i].basePP) {
                gBattleInfo.player[i].PP = gBattleInfo.player[i].basePP;
            }
        } else {
            // if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].baseHP < gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].trueBaseHP + djinnOffset*2 && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP != 0) {
            //     gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP += djinnOffset*2;
            // }
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].baseHP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].trueBaseHP + djinnOffset*2;
            // if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP > gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].baseHP) {
            //     gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].baseHP;
            // }
            // if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].basePP < gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].trueBasePP + djinnOffset*2 && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].PP != 0) {
            //     gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].PP += djinnOffset*2;
            // }
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].basePP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].trueBasePP + djinnOffset*2;
            // if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].PP > gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].basePP) {
            //     gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].PP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].basePP;
            // }

            //mfw too op Sadge

            if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP > gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].baseHP) {
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].baseHP;
            }
            if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].PP > gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].basePP) {
                gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].PP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].basePP;
            }
        }
    }
}

void clear_queue(void) {
    u8 i, j;
    for(i = 0; i < 16; i++) {
        for(j = 0; j < 4; j++) {
            queued_messages[i][j] = 0;
        }
    }
}

u8 pauseMenuState;
void render_battle(void) {
    u8 j = 0;
    u8 i = 0;
    barsRendered = 0;
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
    render_battle_fill_rect(0, 208, 320, 240, 0, 0, 0);
    pauseMenuState = PMENU_NONE;

    if(gBattleInfo.exitTimer == 0) {
        gCamera->cutscene = CUTSCENE_BATTLE;
        if(menuState != MENU_LOSE && menuState != MENU_WIN) {
            if(menuState == MENU_START)
                i = 1;
            while(gBattleInfo.player[gBattleInfo.selectingUser].HP <= 0 && menuState != MENU_TURN) {
                determine_next_selecting_player();
                j++;
            }
            if(i == 1)
                menuState = MENU_START;
            if(j > gCharactersUnlocked) {
                menuState = MENU_LOSE;
            }
        }

        if(menuState == MENU_START) {
            for(i = 0; i < 4; i++) {
                gBattleInfo.player[i].action = 0;
                gBattleInfo.player[i].subAction = 0;
            }
            clear_queue();
        }

        update_inventory();
        update_djinn_used();

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
            case MENU_STATUS:
                render_status_menu();
                break;
            case MENU_LOSE:
                render_battle_lose_text();
                break;
            case MENU_ITEM:
                render_item_menu();
                break;
            case MENU_DJINN:
                render_djinn_menu();
                break;
            case MENU_SUMMON:
                render_summon_menu();
                break;
            case MENU_MESSAGES:
                render_queued_messages();
                break;
            case MENU_FLEE:
                render_flee_text();
                break;
            default:
                render_battle_icons();
                break;

        }

        update_items_used();
        update_camera(gCamera);
    } else {
        exit_battle();
    }

    render_health();
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0x3000);

    //print_text_fmt_int(25, 50, "%d", gBattleInfo.enemy[0].HP);
    //print_text_fmt_int(50, 50, "%d", gBattleInfo.enemy[1].HP);
    //print_text_fmt_int(75, 50, "%d", gBattleInfo.enemy[2].HP);
}

void determine_pause_over_icon(void) {
    switch(overIcon) {
        case 0:
            overString = "Psynergy";
            break;
        case 1:
            overString = "Djinn";
            break;
        case 2:
            overString = "Item";
            break;
        case 3:
            overString = "Status";
            break;
    }
}

u8 pauseIcons[4] = {4, 5, 7, 2};
u8 exitPause = 0;

u8 fieldItemMenuState = 0;

void render_pause_icon_menu(void) {
    u8 i, globalTimerMod, frontLayerIcon;
    f32 iconScale;
    menuState = MENU_PAUSE;
    pauseMenuState = PMENU_ICONS;
    fieldPsynergyMenuState = 0;
    render_health();
    s2d_init();
    render_battle_fill_rect(0, 208, 320, 240, 0, 0, 0);
    determine_joystick_increment(0, 3, 0);

    determine_pause_over_icon();
    render_bar_wh(224, 212, 96, 24);
    sprintf(cbuf, "%s", overString);
    gs_print(228, 220, cbuf, SHADOW, WHITE);

    for(i = 0; i < 4; i++) {
        globalTimerMod = gGlobalTimer % 8;
        if(overIcon == i) {
            frontLayerIcon = i;
        } else {
            call_icons_sprite_dl(pauseIcons[i], 96 + i*32, 208, &buf[i], 0, 1.0f);
        }
    }
    if(globalTimerMod > 3) {
        globalTimerMod = 8 - globalTimerMod;
    }
    iconScale = ((f32)(globalTimerMod) / 8.0f) + 1.0f;
    call_icons_sprite_dl(pauseIcons[frontLayerIcon], 112 + frontLayerIcon*32 - (s32)(iconScale*16.0f), 224 - (s32)(iconScale*16.0f), &buf[i], 0, iconScale);

    if(gPlayer1Controller->buttonPressed & A_BUTTON) {
        if(overIcon == 0) {
            pauseMenuState = PMENU_PSYNERGY;
            overIcon = 0;
        }
        if(overIcon == 1) {
            if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].courseStars[0] != 0) {
                pauseMenuState = PMENU_DJINN;
                overIcon = 0;
            } else {
                play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
            }
        }
        if(overIcon == 2) {
            pauseMenuState = PMENU_ITEM;
            overIcon = 0;
            selectedItem = 0;
            fieldItemMenuState = 0;
        }
        if(overIcon == 3) {
            pauseMenuState = PMENU_STATUS;
            overIcon = 0;
        }
    }

    s2d_stop();
}

void sick_status_print(struct Spell **movePool) {
    u8 i = 0;
    u8 j = 0;
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
            render_battle_fill_rect(148, 60 + selectedPsynergy*24, 316, 84 + selectedPsynergy*24, 0x00, 0x97, 0xE2);
            while(i < 255) {
                if(movePool[i]->sprite != SPELL_NONE) {
                    if(movePool[i]->baseLevel <= gSaveBuffer.files[gCurrSaveFileNum - 1][0].level) {
                        call_spell_sprite_dl(movePool[i]->sprite, 152, 64 + j*24, &ebuf[j]);
                        sprintf(spbuf, "%s", movePool[i]->name);
                        gs_print(172, 68 + j*24, spbuf, SHADOW, WHITE);
                        sprintf(spbuf, "PP %d", movePool[i]->PP);
                        gs_print(264, 68 + j*24, spbuf, SHADOW, WHITE);
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
            gs_print(4, 216, spbuf, SHADOW, WHITE);
}

epicbuf[64];
u8 frozenSelection = 0;
u8 textTimer = 0;
void render_field_psynergy_menu(void) {
    u8 i, j;
    struct Spell **movePool;
    s2d_init();
    render_bar_wh(0, 32, 144, 48);
    render_bar_wh(144, 32, 176, 24);
    render_bar_wh(0, 80, 144, 128);
    render_bar_wh(144, 56, 176, 152);
    render_bar_wh(0, 208, 320, 24);

    determine_joystick_increment(0, gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked, 0);
    render_battle_fill_rect(8 + overIcon*32, 40, 40 + overIcon*32, 72, 0x00, 0x97, 0xE2);
    for(i = 0; i <= gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked; i++) {
        call_player_icon_sprite_dl(i, 8 + i*32, 40, &elbuf[i]);
    }

    call_portrait_sprite_dl(overIcon, 8, 88, &elbuf[5]);

    get_party_member_string(overIcon);
    sprintf(epicbuf, "%s", atkrString);
    gs_print(72, 92, epicbuf, SHADOW, WHITE);
    sprintf(epicbuf, "Lv    %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].level);
    gs_print(72, 108, epicbuf, SHADOW, WHITE);
    sprintf(epicbuf, "HP     %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP);
    gs_print(8, 158, epicbuf, SHADOW, WHITE);
    sprintf(epicbuf, "/%d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP);
    gs_print(84, 158, epicbuf, SHADOW, WHITE);
    sprintf(epicbuf, "PP     %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].PP);
    gs_print(8, 174, epicbuf, SHADOW, WHITE);
    sprintf(epicbuf, "/%d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].basePP);
    gs_print(84, 174, epicbuf, SHADOW, WHITE);
    sprintf(epicbuf, "Exp         %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].exp);
    gs_print(8, 190, epicbuf, SHADOW, WHITE);

    movePool = FieldSpellPool[overIcon];
    switch(fieldPsynergyMenuState) {
        case 0:
            menuState = MENU_PAUSE;
            for(i = 0; i < 0xF0; i++) {
                if(movePool[i]->sprite == SPELL_NONE) {
                    i = 0xF0;
                } else {
                    call_spell_sprite_dl(movePool[i]->sprite, 152 + (i*20), 64, &ebuf[i]);
                }
            }

            sprintf(epicbuf, "Whose psynergy?");
            gs_print(148, 40, epicbuf, SHADOW, WHITE);

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                pauseMenuState = PMENU_ICONS;
                overIcon = 0;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                fieldPsynergyMenuState = 1;
                selectedPsynergy = 0;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            }
            break;
        case 1:
            menuState = MENU_FIELD_PSYNERGY;
            sprintf(epicbuf, "Which psynergy?");
            gs_print(148, 40, epicbuf, SHADOW, WHITE);

            sick_status_print(movePool);

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                fieldPsynergyMenuState = 0;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].PP >= movePool[displayedSelectedPsynergy]->PP && (movePool[displayedSelectedPsynergy]->sprite != SPELL_WISH || (movePool[displayedSelectedPsynergy]->sprite == SPELL_WISH && (gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[0].HP < gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[0].baseHP && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[1].HP < gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[1].baseHP && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[2].HP < gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[2].baseHP && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[3].HP < gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[3].baseHP)))) {
                    if(movePool[displayedSelectedPsynergy]->range == RANGE_SINGLE_ENEMY || movePool[displayedSelectedPsynergy]->range == RANGE_ALL_ENEMIES) {
                        exitPause = 1;
                        gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].PP -= movePool[displayedSelectedPsynergy]->PP;
                        set_mario_action(gMarioState, ACT_PSYNERGYF, movePool[displayedSelectedPsynergy]->sprite);
                    } else {
                        if(movePool[displayedSelectedPsynergy]->range == RANGE_ALL_PARTY) {
                            fieldPsynergyMenuState = 3;
                        } else {
                            fieldPsynergyMenuState = 2;
                        }
                        frozenSelection = overIcon;
                    }
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                } else {
                    fieldPsynergyMenuState = 3;
                    frozenSelection = overIcon;
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
                textTimer = 0;
            }
            break;
        case 2:
            menuState = MENU_PAUSE;
            movePool = FieldSpellPool[frozenSelection];
            sprintf(epicbuf, "To who?");
            gs_print(148, 40, epicbuf, SHADOW, WHITE);

            sick_status_print(movePool);

            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                fieldPsynergyMenuState = 0;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                if(((movePool[displayedSelectedPsynergy]->sprite == SPELL_PLY && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP < gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP != 0) || movePool[displayedSelectedPsynergy]->sprite != SPELL_PLY) && ((movePool[displayedSelectedPsynergy]->sprite == SPELL_PLY_WELL && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP < gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP != 0) || movePool[displayedSelectedPsynergy]->sprite != SPELL_PLY_WELL) && ((movePool[displayedSelectedPsynergy]->sprite == SPELL_REVIVE && gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP <= 0) || movePool[displayedSelectedPsynergy]->sprite != SPELL_REVIVE)) {
                    fieldPsynergyMenuState = 3;
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
                textTimer = 0;
            }
            break;
        case 3:
            menuState = MENU_NONE;
            movePool = FieldSpellPool[frozenSelection];
            sick_status_print(movePool);
            if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[frozenSelection].PP >= movePool[displayedSelectedPsynergy]->PP) {
                if(textTimer == 0) {
                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[frozenSelection].PP -= movePool[displayedSelectedPsynergy]->PP;
                    switch(movePool[displayedSelectedPsynergy]->sprite) {
                        case SPELL_PLY_WELL:
                            gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP += PLY_WELL_HEALTH_RECOVERED - PLY_HEALTH_RECOVERED;
                        case SPELL_PLY:
                            gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP += PLY_HEALTH_RECOVERED;
                            if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP > gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP) {
                                gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP;
                            }
                            break;
                        case SPELL_WISH:
                            for(i = 0; i < 4; i++) {
                                if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP != 0) {
                                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP += WISH_HEALTH_RECOVERED;
                                    if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP > gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].baseHP) {
                                        gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[i].baseHP;
                                    }
                                }
                            }
                            break;
                        case SPELL_REVIVE:
                            gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP;
                    }
                }
                switch(movePool[displayedSelectedPsynergy]->sprite) {
                    get_party_member_string(overIcon);
                    case SPELL_PLY:
                        sprintf(epicbuf, "%s recovered 50 HP!", atkrString);
                        break;
                    case SPELL_PLY_WELL:
                        sprintf(epicbuf, "%s recovered 150 HP!", atkrString);
                        break;
                    case SPELL_WISH:
                        sprintf(epicbuf, "Party recovered 50 HP!");
                        break;
                    case SPELL_REVIVE:
                        sprintf(epicbuf, "%s is revived!", atkrString);
                        break;
                }
            } else {
                sprintf(epicbuf, "Not enough PP!", atkrString);
            }

            gs_print(148, 40, epicbuf, SHADOW, WHITE);

            if(textTimer >= 45) {
                fieldPsynergyMenuState = 0;
                overIcon = frozenSelection;
            }
            textTimer++;
    }

    s2d_stop();
}

void render_field_djinn_menu(void) {
    u8 i, j, color;
    s2d_init();
    render_bar_wh(0, 0, 144, 48);
    render_bar_wh(144, 0, 176, 48);
    render_bar_wh(0, 48, 320, 144);
    render_bar_wh(0, 192, 320, 48);

    determine_joystick_increment(0, gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked, 0);
    render_battle_fill_rect(36 + overIcon*64, 88, 96 + overIcon*64, 98, 0x00, 0x97, 0xE2);
    for(i = 0; i <= gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked; i++) {
        call_player_icon_sprite_dl(i, 48 + i*64, 56, &elbuf[i]);
    }

    if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].courseStars[0] != 0) {
        for(i = 0; i < 4; i++) {
            if((gSaveBuffer.files[gCurrSaveFileNum - 1][0].courseStars[0] & (1 << i)) != 0) {
                call_element_sprite_dl(i, 36 + i*64, 88, &hebuf2[i]);
                sprintf(epicbuf, "%s", djinniPool[i]->name);
                if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].turnsUntilActive != 0) {
                    gs_print(40 + i*64, 88, epicbuf, SHADOW, YELLOW);
                } else if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].activeState == DJINN_INACTIVE) {
                    gs_print(40 + i*64, 88, epicbuf, SHADOW, RED);
                } else {
                    gs_print(40 + i*64, 88, epicbuf, SHADOW, WHITE);
                }
            }
        }

        get_party_member_string(overIcon);
        sprintf(epicbuf, "%s", atkrString);
        gs_print(8, 8, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "Lv    %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].level);
        gs_print(8, 32, epicbuf, SHADOW, WHITE);

        sprintf(epicbuf, "Choose a Djinni.", atkrString);
        gs_print(152, 8, epicbuf, SHADOW, WHITE);

        if((gSaveBuffer.files[gCurrSaveFileNum - 1][0].courseStars[0] & (1 << overIcon)) != 0) {
            if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[overIcon].turnsUntilActive != 0) {
                sprintf(epicbuf, "It's recovering");
                if(gPlayer1Controller->buttonPressed & R_TRIG) {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            } else if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[overIcon].activeState == DJINN_INACTIVE) {
                sprintf(epicbuf, "[R]: Set");
                if(gPlayer1Controller->buttonPressed & R_TRIG) {
                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[overIcon].activeState = DJINN_ACTIVE;
                }
            } else {
                sprintf(epicbuf, "[R]: Standby");
                if(gPlayer1Controller->buttonPressed & R_TRIG) {
                    gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[overIcon].activeState = DJINN_INACTIVE;
                }
            }
            gs_print(152, 32, epicbuf, SHADOW, WHITE);

            sprintf(epicbuf, "%s", djinniPool[overIcon]->tooltip);
            gs_print(8, 220, epicbuf, SHADOW, WHITE);
        }
        sprintf(epicbuf, "Effect of unleashing in battle:");
        gs_print(8, 204, epicbuf, SHADOW, WHITE);
    }

    s2d_stop();

    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        pauseMenuState = PMENU_ICONS;
        overIcon = 1;
        play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
    }
}

void render_field_item_menu(void) {
    struct InventoryItem *inventory = &gSaveBuffer.files[gCurrSaveFileNum - 1][0].inventory;
    u8 i, j = 0;
    u8 itemMax = 0;
    determine_menu_switch();
    if(inventory[0].number > 0) {
        if(fieldItemMenuState == 1)
            determine_joystick_increment(0, gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked, 0);
        else
            determine_joystick_increment(0, 255, 0);
    } else {
        selectedItem = 0;
    }
    s2d_init();

    render_bar_wh(0, 32, 144, 48);
    render_bar_wh(144, 32, 176, 24);
    render_bar_wh(0, 80, 144, 128);
    render_bar_wh(144, 56, 176, 152);
    render_bar_wh(0, 208, 320, 24);
    
    itemMax = 0;
    j = 0;
    for(i = 0; i < 8; i++) {
        if(inventory[i].number != 0) {
            itemMax++;
        }
    }
    
    i = 0;
    if(selectedItem >= itemMax && fieldItemMenuState != 2)
        selectedItem = 0;
    if(selectedItem < 0)
        selectedItem = itemMax - 1;
    j = 0;
    render_battle_fill_rect(148, 60 + selectedItem*24, 316, 84 + selectedItem*24, 0x00, 0x97, 0xE2);
    while(i < itemMax) {
        call_item_sprite_dl(inventory[i].id, 152, 64 + i*24, &ebuf[i], 1.0f);
        sprintf(cbuf, "  %d", inventory[i].number);
        gs_print(140, 72 + i*24, cbuf, SHADOW, WHITE);
        sprintf(cbuf, "%s", items[inventory[i].id]);
        gs_print(168, 68 + i*24, cbuf, SHADOW, WHITE);
        i++;
    }
    if(inventory[0].number > 0) {
        sprintf(spbuf, "%s", itemTooltips[inventory[selectedItem].id]);
    } else {
        sprintf(spbuf, "You have no items.");
    }
    gs_print(4, 216, spbuf, SHADOW, WHITE);

    switch(fieldItemMenuState) {
        case 0:
            render_battle_fill_rect(8, 40, 40 + gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked*32, 72, 0x00, 0x97, 0xE2);
            menuState = MENU_FIELD_ITEM;
            sprintf(epicbuf, "Which item?");
            gs_print(148, 40, epicbuf, SHADOW, WHITE);
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                pauseMenuState = PMENU_ICONS;
                overIcon = 2;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                if(inventory[0].number > 0) {
                    if(inventory[selectedItem].id == ITEM_HERB || inventory[selectedItem].id == ITEM_CORN || inventory[selectedItem].id == ITEM_NUT || inventory[selectedItem].id == ITEM_PSY_CRYSTAL || inventory[selectedItem].id == ITEM_WATER_OF_LIFE) {
                        fieldItemMenuState = 1;
                    } else {
                        fieldItemMenuState = 2;
                    }
                    play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                    overIcon = 0;
                    textTimer = 0;
                } else {
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);
                }
            }
            break;
        case 1:
            render_battle_fill_rect(8 + overIcon*32, 40, 40 + overIcon*32, 72, 0x00, 0x97, 0xE2);
            menuState = MENU_STATUS;
            sprintf(epicbuf, "For who?");
            gs_print(148, 40, epicbuf, SHADOW, WHITE);
            if (gPlayer1Controller->buttonPressed & B_BUTTON) {
                fieldItemMenuState = 0;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
            } else if (gPlayer1Controller->buttonPressed & A_BUTTON) {
                fieldItemMenuState = 2;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
                textTimer = 0;
            }
            break;
        case 2:
            render_battle_fill_rect(8 + overIcon*32, 40, 40 + overIcon*32, 72, 0x00, 0x97, 0xE2);
            menuState = MENU_NONE;
            get_party_member_string(overIcon);
            if (textTimer == 0) {
                switch(inventory[selectedItem].id) {
                    case ITEM_NUT:
                        gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP += NUT_HEALTH_RECOVERED - CORN_HEALTH_RECOVERED - HERB_HEALTH_RECOVERED;
                    case ITEM_CORN:
                        gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP += CORN_HEALTH_RECOVERED - HERB_HEALTH_RECOVERED;
                    case ITEM_HERB:
                        gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP += HERB_HEALTH_RECOVERED;
                        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP > gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP) {
                            gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP;
                        }
                        break;
                    case ITEM_PSY_CRYSTAL:
                        gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].PP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].basePP;
                        break;
                    case ITEM_SACRED_FEATHER:
                        reducedEncounterFrames += 900;
                        break;
                    case ITEM_WATER_OF_LIFE:
                        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP <= 0)
                            gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP = gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP;
                        break;
                }
            }
            textTimer++;
            switch(inventory[selectedItem].id) {
                case ITEM_NUT:
                    sprintf(epicbuf, "%s recovered 150 HP!", atkrString);
                    break;
                case ITEM_CORN:
                    sprintf(epicbuf, "%s recovered 50 HP!", atkrString);
                    break;
                case ITEM_HERB:
                    sprintf(epicbuf, "%s recovered 25 HP!", atkrString);
                    break;
                case ITEM_PSY_CRYSTAL:
                    sprintf(epicbuf, "%s recovered all PP!", atkrString);
                    break;
                case ITEM_SACRED_FEATHER:
                    sprintf(epicbuf, "Encounter rate is down!");
                    break;
                case ITEM_WATER_OF_LIFE:
                    sprintf(epicbuf, "%s is revived!", atkrString);
                    break;    
            }
            gs_print(148, 40, epicbuf, SHADOW, WHITE);
            if (textTimer >= 45) {
                inventory[selectedItem].number--;
                fieldItemMenuState = 0;
            }
            break;
    }

    if(fieldItemMenuState >= 1 && (inventory[selectedItem].id == ITEM_HERB || inventory[selectedItem].id == ITEM_CORN || inventory[selectedItem].id == ITEM_NUT || inventory[selectedItem].id == ITEM_PSY_CRYSTAL || inventory[selectedItem].id == ITEM_WATER_OF_LIFE)) {
        call_portrait_sprite_dl(overIcon, 8, 88, &elbuf[5]);

        get_party_member_string(overIcon);
        sprintf(epicbuf, "%s", atkrString);
        gs_print(72, 92, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "Lv    %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].level);
        gs_print(72, 108, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "HP     %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP);
        gs_print(8, 158, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "/%d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP);
        gs_print(84, 158, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "PP     %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].PP);
        gs_print(8, 174, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "/%d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].basePP);
        gs_print(84, 174, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "Exp         %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].exp);
        gs_print(8, 190, epicbuf, SHADOW, WHITE);
    }
    for(i = 0; i <= gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked; i++) {
        call_player_icon_sprite_dl(i, 8 + i*32, 40, &elbuf[i]);
    }

    s2d_stop();
}

u8 elPlayer = 0;
void render_status_menu(void) {
    u8 i, djinnOffset;
    if(pauseMenuState == PMENU_ICONS) {
        pauseMenuState = PMENU_STATUS;
    }
    menuState = MENU_STATUS;
    s2d_init();
    render_bar_wh(0, 32, 320, 48);
    render_bar_wh(0, 80, 320, 128);

    determine_joystick_increment(0, gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked, 0);
    render_battle_fill_rect(8 + overIcon*32, 40, 40 + overIcon*32, 72, 0x00, 0x97, 0xE2);
    for(i = 0; i <= gSaveBuffer.files[gCurrSaveFileNum - 1][0].charactersUnlocked; i++) {
        call_player_icon_sprite_dl(i, 8 + i*32, 40, &elbuf[i]);
    }

    call_portrait_sprite_dl(overIcon, 8, 88, &elbuf[5]);

    get_party_member_string(overIcon);
    sprintf(epicbuf, "%s    Lv %d", atkrString, gSaveBuffer.files[gCurrSaveFileNum - 1][0].level);
    gs_print(80, 92, epicbuf, SHADOW, WHITE);
    sprintf(epicbuf, "Exp         %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].exp);
    gs_print(80, 108, epicbuf, SHADOW, WHITE);
    if(pauseMenuState == PMENU_NONE) {
        sprintf(epicbuf, "HP     %d", gBattleInfo.player[overIcon].HP);
        gs_print(80, 124, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "/%d", gBattleInfo.player[overIcon].baseHP);
        gs_print(156, 124, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "PP     %d", gBattleInfo.player[overIcon].PP);
        gs_print(80, 140, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "/%d", gBattleInfo.player[overIcon].basePP);
        gs_print(156, 140, epicbuf, SHADOW, WHITE);

        sprintf(epicbuf, "Attack      %d", gBattleInfo.player[overIcon].attack);
        gs_print(196, 92, epicbuf, SHADOW, WHITE);
        if(gBattleInfo.player[overIcon].attackOffset > 0) {
            call_stats_sprite_dl(0, 300, 88, &buf[0]);
        } else if(gBattleInfo.player[overIcon].attackOffset < 0) {
            call_stats_sprite_dl(1, 300, 88, &buf[0]);
        }
        sprintf(epicbuf, "Defense     %d", gBattleInfo.player[overIcon].defense);
        gs_print(196, 108, epicbuf, SHADOW, WHITE);
        if(gBattleInfo.player[overIcon].defenseOffset > 0) {
            call_stats_sprite_dl(0, 300, 104, &buf[1]);
        } else if(gBattleInfo.player[overIcon].defenseOffset < 0) {
            call_stats_sprite_dl(1, 300, 104, &buf[1]);
        }
        sprintf(epicbuf, "Agility     %d", gBattleInfo.player[overIcon].agility);
        gs_print(196, 124, epicbuf, SHADOW, WHITE);
        if(gBattleInfo.player[overIcon].agilityOffset > 0) {
            call_stats_sprite_dl(0, 300, 120, &buf[2]);
        } else if(gBattleInfo.player[overIcon].agilityOffset < 0) {
            call_stats_sprite_dl(1, 300, 120, &buf[2]);
        }
    } else {
        sprintf(epicbuf, "HP     %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].HP);
        gs_print(80, 124, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "/%d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].baseHP);
        gs_print(156, 124, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "PP     %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].PP);
        gs_print(80, 140, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "/%d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].basePP);
        gs_print(156, 140, epicbuf, SHADOW, WHITE);

        if(gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].turnsUntilActive == 0 && gSaveBuffer.files[gCurrSaveFileNum - 1][0].djinn[i].activeState == DJINN_ACTIVE && (gSaveBuffer.files[gCurrSaveFileNum - 1][0].courseStars[0] & (1 << overIcon)) != 0) {
            djinnOffset = (gSaveBuffer.files[gCurrSaveFileNum - 1][0].level / 2) + 1;
        } else {
            djinnOffset = 0;
        }

        sprintf(epicbuf, "Attack      %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].attack + djinnOffset);
        gs_print(196, 92, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "Defense     %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].defense + djinnOffset);
        gs_print(196, 108, epicbuf, SHADOW, WHITE);
        sprintf(epicbuf, "Agility     %d", gSaveBuffer.files[gCurrSaveFileNum - 1][0].player[overIcon].agility + djinnOffset);
        gs_print(196, 124, epicbuf, SHADOW, WHITE);
    }
    s2d_stop();

    if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        if(pauseMenuState == PMENU_STATUS) {
            pauseMenuState = PMENU_ICONS;
            overIcon = 3;
        } else {
            menuState = MENU_START;
            overIcon = OVER_STATUS;
        }
        play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
    }
}

s16 render_gs_pause(void) {
    barsRendered = 0;
    gHudDisplay.flags = HUD_DISPLAY_NONE;
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
    if(pauseMenuState == PMENU_NONE) {
        pauseMenuState = PMENU_ICONS;
    }
    shade_screen();
    update_inventory();
    update_djinn_used();

    if(gPlayer1Controller->buttonPressed & L_TRIG) {
        if(gCurrCourseNum != 1)
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].lastFloor = 0;
        else
            gSaveBuffer.files[gCurrSaveFileNum - 1][0].lastFloor = gCurrAreaIndex;
        save_file_do_save(gCurrSaveFileNum - 1);
    }

    if ((gPlayer1Controller->buttonPressed & (B_BUTTON | START_BUTTON) && pauseMenuState == PMENU_ICONS) || exitPause == 1) {
        level_set_transition(0, NULL);
        play_sound(SOUND_MENU_PAUSE_2, gGlobalSoundSource);
        gMenuMode = -1;
        overIcon = 0;
        menuState = MENU_NONE;
        pauseMenuState = PMENU_ICONS;
        gHudDisplay.flags = HUD_DISPLAY_DEFAULT;
        exitPause = 0;
        return 1;
    }

    exitPause = 0;

    switch(pauseMenuState) {
        case PMENU_ICONS:
            render_pause_icon_menu();
            break;
        case PMENU_PSYNERGY:
            render_field_psynergy_menu();
            break;
        case PMENU_DJINN:
            render_field_djinn_menu();
            break;
        case PMENU_ITEM:
            render_field_item_menu();
            break;
        case PMENU_STATUS:
            render_status_menu();
            break;
    }

    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0x3000);

    return 0;
}

s32 x, y;
void render_item_got(u8 itemGot) {
    barsRendered = 0;
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
    s2d_init();

    if(gGetScreenCoords != 0 && gScreenX != 0xFFFF0000) {
        g3DtoScreenCoords[0] = gMarioState->pos[0];
        g3DtoScreenCoords[1] = gMarioState->pos[1] + 25.0f;
        g3DtoScreenCoords[2] = gMarioState->pos[2];
        call_item_sprite_dl(itemGot, gScreenX - 16, gScreenY - 16, &ebuf[0], 2.0f);
    }

    render_bar_wh(40, 40, 240, 24);
    conjugate_item(itemGot);
    sprintf(cbuf, "You got %s%s.", conjugation, items[itemGot]);
    gs_print(40, 48, cbuf, SHADOW, WHITE);
    s2d_stop();

    gScreenX = 0xFFFF0000;
    gGetScreenCoords = 1;
}

render_party_member_got(u8 partyMemberGot) {
    barsRendered = 0;
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
    s2d_init();
    render_bar_wh(41, 40, 71, 71);
    render_bar_wh(112, 40, 188, 24);
    call_portrait_sprite_dl(partyMemberGot, 45, 44, &elbuf[5]);
    get_party_member_string(partyMemberGot);
    sprintf(cbuf, "%s joined your party!", atkrString);
    gs_print(116, 48, cbuf, SHADOW, WHITE);
    s2d_stop();
}

const char *spellStr = "Whirlwind";
u8 stringCenterOffset;
print_field_psynergy(u8 spell) {
    barsRendered = 0;
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
    switch(spell) {
        case SPELL_LIFT:
            spellStr = "Lift";
            break;
        case SPELL_GROWTH:
            spellStr = "Growth";
            break;
        case SPELL_WHIRLWIND:
            spellStr = "Whirlwind";
            break;
        case SPELL_FROST:
            spellStr = "Frost";
            break;
    }
    s2d_init();
    stringCenterOffset = s2d_strlen(spellStr)*8 + 4;
    render_bar(156 - stringCenterOffset, 176, 160 + (stringCenterOffset / 2), 200);
    sprintf(cbuf, "%s", spellStr);
    gs_print(160 - stringCenterOffset, 184, cbuf, SHADOW, WHITE);
    s2d_stop();
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0x3000);
}

void render_password_screen(void) {
    u8 i, j;
    set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
    barsRendered = 0;
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
    s2d_init();
    
    render_bar_wh(60, 20, 200, 30);
    gs_print(104, 30, "Password Entry", SHADOW, WHITE);
    render_bar_wh(60, 50, 200, 80);
    render_bar_wh(20, 130, 280, 60);
    gs_print(24, 140, " 0 1 2 3 4 5 6 7 8 9 a b c d e f g h", SHADOW, WHITE);
    gs_print(32, 160, "i j k l m n o p q r s t u v w x y z", SHADOW, WHITE);
    render_bar_wh(20, 190, 280, 30);
    gs_print(28, 200, "[A]: Enter [B]: Delete START: Submit", SHADOW, WHITE);

    s2d_stop();
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0x3000);
}