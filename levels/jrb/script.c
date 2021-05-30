#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/jrb/header.h"

const LevelScript level_jrb_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _jrb_segment_7SegmentRomStart, _jrb_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(0, 0x00000001, bhvWarpPipe), 

	AREA(1, jrb_area_1),
		WARP_NODE(0x0A, LEVEL_JRB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x01, LEVEL_CCM, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, 0, 0, 0),
		OBJECT(MODEL_NONE, 0, 0, 0, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		TERRAIN(jrb_area_1_collision),
		//MACRO_OBJECTS(jrb_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CREDITS),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
