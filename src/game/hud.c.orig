#include <PR/ultratypes.h>

#include "sm64.h"
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

#include "s2d_engine/init.h"
#include "s2d_engine/s2d_draw.h"
#include "s2d_engine/s2d_print.h"
#include <PR/gs2dex.h>
#include "src/s2d_engine/icons/icons.c"
#include "src/s2d_engine/icons/icons.h"
#include "src/s2d_engine/icons/bar.h"
#include "src/s2d_engine/icons/barscripts/bar.h"

/* @file hud.c
 * This file implements HUD rendering and power meter animations.
 * That includes stars, lives, coins, camera status, power meter, timer
 * cannon reticle, and the unused keys.
 **/

struct PowerMeterHUD {
    s8 animation;
    s16 x;
    s16 y;
    f32 unused;
};

struct UnusedHUDStruct {
    u32 unused1;
    u16 unused2;
    u16 unused3;
};

struct CameraHUD {
    s16 status;
};

// Stores health segmented value defined by numHealthWedges
// When the HUD is rendered this value is 8, full health.
static s16 sPowerMeterStoredHealth;

static struct PowerMeterHUD sPowerMeterHUD = {
    POWER_METER_HIDDEN,
    140,
    166,
    1.0,
};

// Power Meter timer that keeps counting when it's visible.
// Gets reset when the health is filled and stops counting
// when the power meter is hidden.
s32 sPowerMeterVisibleTimer = 0;

static struct UnusedHUDStruct sUnusedHUDValues = { 0x00, 0x0A, 0x00 };

static struct CameraHUD sCameraHUD = { CAM_STATUS_NONE };

/**
 * Renders a rgba16 16x16 glyph texture from a table list.
 */
void render_hud_tex_lut(s32 x, s32 y, u8 *texture) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gSPDisplayList(gDisplayListHead++, &dl_hud_img_load_tex_block);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 15) << 2, (y + 15) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders a rgba16 8x8 glyph texture from a table list.
 */
void render_hud_small_tex_lut(s32 x, s32 y, u8 *texture) {
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,
                G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0,
                G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_16b_BYTES));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 7) << 2, (y + 7) << 2, G_TX_RENDERTILE,
                        0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders power meter health segment texture using a table list.
 */
void render_power_meter_health_segment(s16 numHealthWedges) {
    u8 *(*healthLUT)[];

    healthLUT = segmented_to_virtual(&power_meter_health_segments_lut);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,
                       (*healthLUT)[numHealthWedges - 1]);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES));
    gSP1Triangle(gDisplayListHead++, 0, 1, 2, 0);
    gSP1Triangle(gDisplayListHead++, 0, 2, 3, 0);
}

/**
 * Renders power meter display lists.
 * That includes the "POWER" base and the colored health segment textures.
 */
void render_dl_power_meter(s16 numHealthWedges) {
    Mtx *mtx;

    mtx = alloc_display_list(sizeof(Mtx));

    if (mtx == NULL) {
        return;
    }

    guTranslate(mtx, (f32) sPowerMeterHUD.x, (f32) sPowerMeterHUD.y, 0);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx++),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(gDisplayListHead++, &dl_power_meter_base);

    if (numHealthWedges != 0) {
        gSPDisplayList(gDisplayListHead++, &dl_power_meter_health_segments_begin);
        render_power_meter_health_segment(numHealthWedges);
        gSPDisplayList(gDisplayListHead++, &dl_power_meter_health_segments_end);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

/**
 * Power meter animation called when there's less than 8 health segments
 * Checks its timer to later change into deemphasizing mode.
 */
void animate_power_meter_emphasized(void) {
    s16 hudDisplayFlags;
    hudDisplayFlags = gHudDisplay.flags;

    if (!(hudDisplayFlags & HUD_DISPLAY_FLAG_EMPHASIZE_POWER)) {
        if (sPowerMeterVisibleTimer == 45.0) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
        }
    } else {
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Power meter animation called after emphasized mode.
 * Moves power meter y pos speed until it's at 200 to be visible.
 */
static void animate_power_meter_deemphasizing(void) {
    s16 speed = 5;

    if (sPowerMeterHUD.y >= 181) {
        speed = 3;
    }

    if (sPowerMeterHUD.y >= 191) {
        speed = 2;
    }

    if (sPowerMeterHUD.y >= 196) {
        speed = 1;
    }

    sPowerMeterHUD.y += speed;

    if (sPowerMeterHUD.y >= 201) {
        sPowerMeterHUD.y = 200;
        sPowerMeterHUD.animation = POWER_METER_VISIBLE;
    }
}

/**
 * Power meter animation called when there's 8 health segments.
 * Moves power meter y pos quickly until it's at 301 to be hidden.
 */
static void animate_power_meter_hiding(void) {
    sPowerMeterHUD.y += 20;
    if (sPowerMeterHUD.y >= 301) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Handles power meter actions depending of the health segments values.
 */
void handle_power_meter_actions(s16 numHealthWedges) {
    // Show power meter if health is not full, less than 8
    if (numHealthWedges < 8 && sPowerMeterStoredHealth == 8 && sPowerMeterHUD.animation == POWER_METER_HIDDEN) {
        sPowerMeterHUD.animation = POWER_METER_EMPHASIZED;
        sPowerMeterHUD.y = 166;
    }

    // Show power meter if health is full, has 8
    if (numHealthWedges == 8 && sPowerMeterStoredHealth == 7) {
        sPowerMeterVisibleTimer = 0;
    }

    // After health is full, hide power meter
    if (numHealthWedges == 8 && sPowerMeterVisibleTimer > 45.0) {
        sPowerMeterHUD.animation = POWER_METER_HIDING;
    }

    // Update to match health value
    sPowerMeterStoredHealth = numHealthWedges;

    // If Mario is swimming, keep power meter visible
    if (gPlayerCameraState->action & ACT_FLAG_SWIMMING) {
        if (sPowerMeterHUD.animation == POWER_METER_HIDDEN
            || sPowerMeterHUD.animation == POWER_METER_EMPHASIZED) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
            sPowerMeterHUD.y = 166;
        }
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Renders the power meter that shows when Mario is in underwater
 * or has taken damage and has less than 8 health segments.
 * And calls a power meter animation function depending of the value defined.
 */
void render_hud_power_meter(void) {
    s16 shownHealthWedges = gHudDisplay.wedges;

    if (sPowerMeterHUD.animation != POWER_METER_HIDING) {
        handle_power_meter_actions(shownHealthWedges);
    }

    if (sPowerMeterHUD.animation == POWER_METER_HIDDEN) {
        return;
    }

    switch (sPowerMeterHUD.animation) {
        case POWER_METER_EMPHASIZED:
            animate_power_meter_emphasized();
            break;
        case POWER_METER_DEEMPHASIZING:
            animate_power_meter_deemphasizing();
            break;
        case POWER_METER_HIDING:
            animate_power_meter_hiding();
            break;
        default:
            break;
    }

    render_dl_power_meter(shownHealthWedges);

    sPowerMeterVisibleTimer += 1;
}

#ifdef VERSION_JP
#define HUD_TOP_Y 210
#else
#define HUD_TOP_Y 209
#endif

/**
 * Renders the amount of lives Mario has.
 */
void render_hud_mario_lives(void) {
    print_text(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(22), HUD_TOP_Y, ","); // 'Mario Head' glyph
    print_text(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(38), HUD_TOP_Y, "*"); // 'X' glyph
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(54), HUD_TOP_Y, "%d", gHudDisplay.lives);
}

/**
 * Renders the amount of coins collected.
 */
void render_hud_coins(void) {
    print_text(168, HUD_TOP_Y, "+"); // 'Coin' glyph
    print_text(184, HUD_TOP_Y, "*"); // 'X' glyph
    print_text_fmt_int(198, HUD_TOP_Y, "%d", gHudDisplay.coins);
}

#ifdef VERSION_JP
#define HUD_STARS_X 73
#else
#define HUD_STARS_X 78
#endif

/**
 * Renders the amount of stars collected.
 * Disables "X" glyph when Mario has 100 stars or more.
 */
void render_hud_stars(void) {
    s8 showX = 0;

    if (gHudFlash == 1 && gGlobalTimer & 0x08) {
        return;
    }

    if (gHudDisplay.stars < 100) {
        showX = 1;
    }

    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X), HUD_TOP_Y, "-"); // 'Star' glyph
    if (showX == 1) {
        print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X) + 16, HUD_TOP_Y, "*"); // 'X' glyph
    }
    print_text_fmt_int((showX * 14) + GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X - 16),
                       HUD_TOP_Y, "%d", gHudDisplay.stars);
}

/**
 * Unused function that renders the amount of keys collected.
 * Leftover function from the beta version of the game.
 */
void render_hud_keys(void) {
    s16 i;

    for (i = 0; i < gHudDisplay.keys; i++) {
        print_text((i * 16) + 220, 142, "/"); // unused glyph - beta key
    }
}

/**
 * Renders the timer when Mario start sliding in PSS.
 */
void render_hud_timer(void) {
    u8 *(*hudLUT)[58];
    u16 timerValFrames;
    u16 timerMins;
    u16 timerSecs;
    u16 timerFracSecs;

    hudLUT = segmented_to_virtual(&main_hud_lut);
    timerValFrames = gHudDisplay.timer;
#ifdef VERSION_EU
    switch (eu_get_language()) {
        case LANGUAGE_ENGLISH:
            print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(150), 185, "TIME");
            break;
        case LANGUAGE_FRENCH:
            print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(155), 185, "TEMPS");
            break;
        case LANGUAGE_GERMAN:
            print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(150), 185, "ZEIT");
            break;
    }
#endif
    timerMins = timerValFrames / (30 * 60);
    timerSecs = (timerValFrames - (timerMins * 1800)) / 30;

    timerFracSecs = ((timerValFrames - (timerMins * 1800) - (timerSecs * 30)) & 0xFFFF) / 3;
#ifndef VERSION_EU
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(150), 185, "TIME");
#endif
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(91), 185, "%0d", timerMins);
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(71), 185, "%02d", timerSecs);
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(37), 185, "%d", timerFracSecs);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(81), 32, (*hudLUT)[GLYPH_APOSTROPHE]);
    render_hud_tex_lut(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(46), 32, (*hudLUT)[GLYPH_DOUBLE_QUOTE]);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

/**
 * Sets HUD status camera value depending of the actions
 * defined in update_camera_status.
 */
void set_hud_camera_status(s16 status) {
    sCameraHUD.status = status;
}

/**
 * Renders camera HUD glyphs using a table list, depending of
 * the camera status called, a defined glyph is rendered.
 */
void render_hud_camera_status(void) {
    u8 *(*cameraLUT)[6];
    s32 x;
    s32 y;

    cameraLUT = segmented_to_virtual(&main_hud_camera_lut);
    x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(54);
    y = 205;

    if (sCameraHUD.status == CAM_STATUS_NONE) {
        return;
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(x, y, (*cameraLUT)[GLYPH_CAM_CAMERA]);

    switch (sCameraHUD.status & CAM_STATUS_MODE_GROUP) {
        case CAM_STATUS_MARIO:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_MARIO_HEAD]);
            break;
        case CAM_STATUS_LAKITU:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_LAKITU_HEAD]);
            break;
        case CAM_STATUS_FIXED:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_FIXED]);
            break;
    }

    switch (sCameraHUD.status & CAM_STATUS_C_MODE_GROUP) {
        case CAM_STATUS_C_DOWN:
            render_hud_small_tex_lut(x + 4, y + 16, (*cameraLUT)[GLYPH_CAM_ARROW_DOWN]);
            break;
        case CAM_STATUS_C_UP:
            render_hud_small_tex_lut(x + 4, y - 8, (*cameraLUT)[GLYPH_CAM_ARROW_UP]);
            break;
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

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

void determine_menu_switch(void) {
    switch(menuState) {
        case MENU_START:
            if(overIcon == OVER_FIGHT && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_FIGHT;
                overIcon = OVER_ATTACK;
                play_sound(SOUND_MENU_CLICK_FILE_SELECT, gGlobalSoundSource);
            } else if(overIcon == OVER_FLEE && gPlayer1Controller->buttonPressed & A_BUTTON) {
                menuState = MENU_NONE;
                overIcon = OVER_FIGHT;
                play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gGlobalSoundSource);
                set_mario_action(gMarioState, ACT_IDLE, 0);
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_LEVEL_GRASS), 0);
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
        sbuf = alloc_display_list(sizeof(uObjMtx) * 8);
        sprintf(tbuf, COLOR"0 0 0 255%s", str);
        s2d_print(x, y + 1, tbuf, sbuf);
    }
    sbuf = alloc_display_list(sizeof(uObjMtx) * 8);
    sprintf(tbuf, COLOR"255 255 255 255%s", str);
    s2d_print(x, y, tbuf, sbuf);
}


void render_battle_icons(void) {
    uObjMtx *sbuf;
    u8 i, frontLayerIcon, frontLayerXval, globalTimerMod, initSprite, maxSprite;
    u8 xval;
    f32 iconScale;

    iconScale = 0;
    s2d_init();

    determine_menu_switch();

    switch(menuState) {
            case MENU_START:
                initSprite = 0;
                maxSprite = 2;
                xval = 112;
                break;
            case MENU_FIGHT:
                initSprite = 3;
                maxSprite = 8;
                xval = 80;
                break;
        }

        determine_joystick_increment(initSprite, maxSprite);

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
    } else if (menuState == MENU_ATTACK) {
        call_icons_sprite_dl(OVER_ATTACK, (s32) 80, 208, &buf[0], 0, 1.0f);
        render_bar_wh(112, 208, 128, 32);
        gs_print(148, 220, "Attack", SHADOW);
    }

    s2d_stop();
}

void render_battle_text(void) {
    uObjMtx *sbuf;
    switch(atkr) {
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
        break;
    }
    s2d_init();
    //sbuf = alloc_display_list(sizeof(uObjMtx) * 64);
    sprintf(cbuf, "%s attacks!", enemyString);
    gs_print(0, 212, cbuf, NO_SHADOW);
    //s2d_print(0, 212, cbuf, sbuf);
    //sbuf = alloc_display_list(sizeof(uObjMtx) * 64);
    //sprintf(cbuf, "Goomba takes %i damage", 5);
    //s2d_print(0, 224, cbuf, sbuf);
    s2d_stop();
    if(gPlayer1Controller->buttonPressed & A_BUTTON)
        menuState = MENU_START;
}

void render_battle(void) {
    barsRendered = 0;
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
    render_battle_fill_rect(0, 208, 320, 240, 0, 0, 0);
    if(menuState == MENU_NONE)
        render_battle_text();
    else
        render_battle_icons();
    gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0x3000);
}

/**
 * Render HUD strings using hudDisplayFlags with it's render functions,
 * excluding the cannon reticle which detects a camera preset for it.
 */

void render_hud(void) {
    s16 hudDisplayFlags;
#ifdef VERSION_EU
    Mtx *mtx;
#endif

    hudDisplayFlags = gHudDisplay.flags;

    if (hudDisplayFlags == HUD_DISPLAY_NONE) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterStoredHealth = 8;
        sPowerMeterVisibleTimer = 0;
    } else {
#ifdef VERSION_EU
        // basically create_dl_ortho_matrix but guOrtho screen width is different

        mtx = alloc_display_list(sizeof(*mtx));
        if (mtx == NULL) {
            return;
        }
        create_dl_identity_matrix();
        guOrtho(mtx, -16.0f, SCREEN_WIDTH + 16, 0, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx),
                G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
#else
        create_dl_ortho_matrix();
#endif

        if (gCurrentArea != NULL && gCurrentArea->camera->mode == CAMERA_MODE_INSIDE_CANNON) {
            render_hud_cannon_reticle();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_LIVES) {
            render_hud_mario_lives();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_COIN_COUNT) {
            render_hud_coins();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_STAR_COUNT) {
            render_hud_stars();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_KEYS) {
            render_hud_keys();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_CAMERA_AND_POWER) {
            render_hud_power_meter();
            render_hud_camera_status();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_TIMER) {
            render_hud_timer();
        }

        if (gPlayer1Controller->buttonPressed & L_TRIG) {
            set_mario_action(gMarioState, ACT_BATTLE, 0);
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_BATTLE), 0);
        }
        
        if (gMarioState->action == ACT_BATTLE)
            render_battle();
    }
}
