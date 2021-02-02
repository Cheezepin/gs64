/* clang-format off */
/*
 * mem_error_screen.inc.c
 *
 * This enhancement should be used for ROM hacks that require the expansion pak.
 *
 */
/* clang-format on */

#include <types.h>
#include "segments.h"
#include "text_strings.h"
#include "game_init.h"
#include "main.h"
#include "print.h"
#include "ingame_menu.h"
#include "segment2.h"
#include "../engine/level_script.h"
#include "audio/external.h"
#include "seq_ids.h"
#include "game/battle_helpers.h"
#include "src/s2d_engine/init.h"
#include "src/s2d_engine/s2d_draw.h"
#include "src/s2d_engine/s2d_print.h"
#include <PR/gs2dex.h>
#include "src/s2d_engine/icons/sample.c"
#include "src/s2d_engine/icons/sample.h"

// Ensure that USE_EXT_RAM is defined.
#ifndef USE_EXT_RAM
#error You have to define USE_EXT_RAM in 'include/segments.h'
#endif

// Require 8 MB of RAM, even if the pool doesn't go into extended memory.
// Change the '8' to whatever MB limit you want.
// Note: only special emulators allow for RAM sizes above 8 MB.
#define REQUIRED_MIN_MEM_SIZE 1048576 * 8

extern void gs_print(int x, int y, const char *str, int shadow, int color);

u8 gNotEnoughMemory = FALSE;
u8 gDelayForErrorMessage = 0;

u8 does_pool_end_lie_out_of_bounds(void *end) {
    u32 endPhy = ((u32) end) & 0x1FFFFFFF;
    u32 memSize = *((u32 *) 0x80000318);

    if (endPhy > memSize) {
        gNotEnoughMemory = TRUE;
        return TRUE;
    } else {
        if (memSize < REQUIRED_MIN_MEM_SIZE) {
            gNotEnoughMemory = TRUE;
        }
        return FALSE;
    }
}

// If you're using an N64 console, then you will need to buy an\nexpansion pak to play this ROM hack.
u8 text_console_8mb[] = { TEXT_CONSOLE_8MB };

// If you are using PJ64 1.6, go to: Options ► Settings ► Rom Settings Tab ► Memory Size then select 8
// MB from the drop-down box.
u8 text_pj64[] = { TEXT_PJ64 };

uObjMtx lebuf[6];

// If you are using PJ64 2.X, go to: Options ► Settings ► Config: ► Memory Size, select 8 MB
u8 text_pj64_2[] = { TEXT_PJ64_2 };
u8 elbuffer[12];

u8 error1[] = { TEXT_ERROR1 };
u8 error2[] = { TEXT_ERROR2 };
u8 error3[] = { TEXT_ERROR3 };
u8 memscreen1[] = { TEXT_MEMSCREEN1 };
u8 memscreen2[] = { TEXT_MEMSCREEN2 };
u8 memscreen3[] = { TEXT_MEMSCREEN3 };
u8 console[] = { TEXT_CONSOLE };

Gfx *geo18_display_error_message(u32 run, UNUSED struct GraphNode *sp44, UNUSED u32 sp48) {
    u8 i;
    if (run) {
        if (gDelayForErrorMessage > 0) {
            gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0);
            if(gDelayForErrorMessage == 1) {
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(0, SEQ_MENU), 0);
                gDelayForErrorMessage = 2;
            }
            // Draw color text title.
            // print_text(10, 210, "ERROR    Need more memory");

            // Init generic text rendering
            create_dl_ortho_matrix();

            gSPDisplayList(gDisplayListHead++,
                           dl_ia_text_begin); // Init rendering stuff for generic text

            // Set text color to white
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

            if(gCounterFactor > 0 && gCounterFactor < 7) {

                //print_generic_string(8, 170, text_console_8mb);
                //print_generic_string(8, 120, text_pj64);
                //print_generic_string(8, 54, text_pj64_2);

                print_generic_string(8, 220, memscreen1);
                i = 0;
                if(gNotEnoughMemory) {
                    print_generic_string(8, 205 - i, error1);
                    i += 15;
                }
                if(gCounterFactor != 1) {
                    print_generic_string(8, 205 - i, error2);
                    i += 15;
                }
                if(gEepromValue != 2) {
                    print_generic_string(8, 205 - i, error3);
                    i += 15;
                }
                print_generic_string(8, 205 - i, memscreen2);

                print_generic_string(8, 120, memscreen3);

            } else {
                print_generic_string(8, 220, console);
            }

            // Cleanup
            gSPDisplayList(gDisplayListHead++,
                           dl_ia_text_end); // Reset back to default render settings.
            gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

            s2d_init();
            gSPDisplayList(gDisplayListHead++, sample_bg_dl);
            s2d_stop();

            gSPSetOtherMode(gDisplayListHead++, G_SETOTHERMODE_H, G_MDSFT_TEXTFILT, 2, 0x3000);
        } else {
            gDelayForErrorMessage += 1;
        }
    }

    return 0;
}

// Basic main loop for the error screen. Note that controllers are not enabled here.
void thread5_mem_error_message_loop(UNUSED void *arg) {
    struct LevelCommand *addr;

    setup_game_memory();
    set_vblank_handler(2, &gGameVblankHandler, &gGameVblankQueue, (OSMesg) 1);

    addr = segmented_to_virtual(level_script_entry_error_screen);

    rendering_init();

    while (1) {
        config_gfx_pool();
        addr = level_script_execute(addr);
        display_and_vsync();
    }
}