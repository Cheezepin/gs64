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
#include "levels/bob/header.h"

const LevelScript level_bob_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_YAY0(0xa, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _grass_yay0SegmentRomStart, _grass_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group1_yay0SegmentRomStart, _group1_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group1_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CASTLE_DOOR, castle_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_LIGHTHOUSE_GATE, lighthouse_gate_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_ICYBLOCK, icyblock_geo), 

	AREA(1, bob_area_1),
		WARP_NODE(0x01, LEVEL_CASTLE_GROUNDS, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_BOB, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0b, LEVEL_BOB, 0x01, 0x0b, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_CASTLE_GROUNDS, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CHEST, 12, 250, 14527, 0, -180, 0, 0x05000000, bhvChest),
		OBJECT(MODEL_STAR, 3014, 2500, 6982, 0, 0, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, 75, 1000, 20012, 0, -180, 0, 0x00010000, bhvDoorWarp),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, -80, 1000, 20012, 0, 0, 0, 0x00010000, bhvDoorWarp),
		OBJECT(MODEL_HEART, 0, 63, 19000, 0, 0, 0, 0x00000000, bhvRecoveryHeart),
		OBJECT(MODEL_LIFTROCK, 40, -1250, 11789, 0, 0, 0, 0x00000019, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, 40, -1250, 10577, 0, 0, 0, 0x00000019, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, 40, -1250, 9182, 0, 0, 0, 0x00000019, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, 2325, 250, 6127, 0, 0, 0, 0x00000005, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, 3746, 250, 6533, 0, 0, 0, 0x00000005, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, 3355, 250, 7667, 0, 0, 0, 0x00000005, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, 2291, -11000, -572, 0, 0, 0, 0x00000000, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, 690, -11000, 1139, 0, 0, 0, 0x00000000, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, -1065, -11000, 674, 0, 0, 0, 0x00000000, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, -998, -11000, -2258, 0, 0, 0, 0x00000000, bhvLiftRock),
		OBJECT(MODEL_LIFTROCK, 1889, 250, 6889, 0, 0, 0, 0x0000000a, bhvLiftRock),
		OBJECT(MODEL_NONE, 14, 1000, 19750, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 14, 250, 5857, 0, -180, 0, 0x000B0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 375, 5357, 0, 0, 0, 0x20020000, bhvWarp),
		TERRAIN(bob_area_1_collision),
		MACRO_OBJECTS(bob_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_CREDITS),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(2, bob_area_2),
		WARP_NODE(0x01, LEVEL_BOB, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_BOB, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x02, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x02, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_BOB, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CHEST, 967, 844, 9334, 0, 90, 0, 0x06000000, bhvChest),
		OBJECT(MODEL_CHEST, -967, 844, 9334, 0, -90, 0, 0x07010000, bhvChest),
		OBJECT(MODEL_STAR, 1070, 1625, 18148, 0, 0, 0, 0x01010000, bhvStar),
		OBJECT(MODEL_PLANT, 883, -562, 18148, 0, 0, 0, 0x00000000, bhvPlant),
		OBJECT(MODEL_PLANT, 0, 125, 21607, 0, -180, 0, 0x00000000, bhvPlant),
		OBJECT(MODEL_PLANT, 1865, -8875, 1847, 0, 0, 0, 0x00000000, bhvPlant),
		OBJECT(MODEL_PLANT, -1473, -8875, 744, 0, 0, 0, 0x00000000, bhvPlant),
		OBJECT(MODEL_PLANT, -482, -9000, -1535, 0, 0, 0, 0x00000000, bhvPlant),
		OBJECT(MODEL_NONE, 14, 250, 5857, 0, -180, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 14, 1250, 21979, 0, -180, 0, 0x000B0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 30, 94, 5232, 0, 0, 0, 0x20010000, bhvWarp),
		OBJECT(MODEL_NONE, 30, 1375, 22604, 0, 0, 0, 0x20020000, bhvWarp),
		TERRAIN(bob_area_2_collision),
		MACRO_OBJECTS(bob_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LIGHTHOUSE),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(3, bob_area_3),
		WARP_NODE(0x01, LEVEL_BOB, 0x02, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_BOB, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x03, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x03, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_BOB, 0x02, 0x0B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CHEST, 1142, 1563, 6061, 0, -90, 0, 0x08010000, bhvChest),
		OBJECT(MODEL_CHEST, 1125, 1250, 8377, 0, -90, 0, 0x09010000, bhvChest),
		OBJECT(MODEL_STAR, -1410, 500, 383, 0, 0, 0, 0x02020000, bhvStar),
		OBJECT(MODEL_RED_FLAME, -437, 563, 3129, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 437, 563, 3129, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -677, 563, 20718, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 677, 563, 20718, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 744, -10688, -1120, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 2238, -10688, 1325, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 1714, -10688, -1779, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -142, -10688, -2202, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -1428, -10688, -1127, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -2269, -10688, 1486, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, -138, -10688, 1230, 0, 0, 90, 0x00000000, bhvFlame),
		OBJECT(MODEL_NONE, 687, 250, 1713, 0, 0, 0, 0x00010000, bhvOpenableGrill),
		OBJECT(MODEL_LEAF, 0, 250, 6432, 0, -90, 0, 0x00000000, bhvLeaf),
		OBJECT(MODEL_LEAF, 164, 238, 3431, 0, 0, 90, 0x00000000, bhvLeaf),
		OBJECT(MODEL_LEAF, 834, 237, -125, 0, 0, 90, 0x00000000, bhvLeaf),
		OBJECT(MODEL_NONE, 0, 250, 22895, 0, -180, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 14, 250, -3153, 0, -180, 0, 0x000b0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_PURPLE_SWITCH, -46, -250, 3411, 0, 0, 0, 0x00000000, bhvFloorSwitchGrills),
		OBJECT(MODEL_NONE, 30, 156, 23395, 0, 0, 0, 0x20010000, bhvWarp),
		OBJECT(MODEL_NONE, 30, 94, 5232, 0, 0, 0, 0x20020000, bhvWarp),
		OBJECT(MODEL_NONE, 30, 245, -3718, 0, 0, 0, 0x20020000, bhvWarp),
		TERRAIN(bob_area_3_collision),
		MACRO_OBJECTS(bob_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LIGHTHOUSE),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(4, bob_area_4),
		WARP_NODE(0x01, LEVEL_BOB, 0x03, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_BOB, 0x05, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x04, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x04, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_BOB, 0x03, 0x0B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CHEST, 0, -594, 11436, 0, -180, 0, 0x0B020000, bhvChest),
		OBJECT(MODEL_STAR, -611, -344, 13880, 0, 0, 0, 0x03030000, bhvStar),
		OBJECT(MODEL_ICYBLOCK, 249, 0, 3874, 0, 0, 0, 0x00000000, bhvIcyBlock),
		OBJECT(MODEL_LIGHTHOUSE_GATE, 61, 250, 5958, 0, -180, 0, 0x00000000, bhvLighthouseGate),
		OBJECT(MODEL_NONE, -975, 1000, 2789, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -622, 1500, 3095, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 0, 1500, 3178, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 316, 1375, 3857, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -18, 1500, 4339, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_CHEST, -1, 1500, 4812, 0, -180, 0, 0x0A020000, bhvChest),
		OBJECT(MODEL_NONE, 739, 1000, 19247, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 670, 1000, 19637, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 437, 1000, 19973, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 506, 1000, 20460, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 303, 1000, 21160, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 636, 1000, 21787, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 207, 1000, 22321, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -23, 1000, 22932, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 526, 1000, 23313, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 40, 1000, 24025, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 298, 1000, 24459, 0, 90, 0, 0x007F0000, bhvPoleGrabbing),
		OBJECT(MODEL_PUDDLE, -251, 0, 5137, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PUDDLE, 711, -1844, 17444, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PUDDLE, 0, -2750, 17444, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PUDDLE, -720, -1844, 8030, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PUDDLE, 0, -2750, 8030, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PUDDLE, -1381, -11000, 1192, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PUDDLE, 1267, -11000, -796, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PUDDLE, -994, -11000, -728, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PUDDLE, 1846, -11000, 2165, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_FROST_SPIRE, 2152, -10008, 207, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_FROST_SPIRE, -2004, -10317, -801, 0, 90, 0, 0x00000000, bhvPuddle),
		OBJECT(MODEL_PURPLE_SWITCH, -626, 250, 3249, 0, -180, 0, 0x003200000, bhvFloorSwitchHardcodedModel),
		OBJECT(MODEL_NONE, 30, 250, 26310, 0, 0, 0, 0x000B0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 250, 1146, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 0, 352, 26834, 0, -180, 0, 0x20020000, bhvWarp),
		OBJECT(MODEL_NONE, 0, 156, 646, 0, -180, 0, 0x20010000, bhvWarp),
		TERRAIN(bob_area_4_collision),
		MACRO_OBJECTS(bob_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LIGHTHOUSE),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(5, bob_area_5),
		WARP_NODE(0x01, LEVEL_BOB, 0x04, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x05, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x05, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_BOB, 0x04, 0x0B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_CHEST, 10, 250, 18276, 0, 0, 0, 0x0C030000, bhvChest),
		OBJECT(MODEL_NONE, 8, 250, 19192, 0, -180, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 10, 1375, 14442, 0, -180, 0, 0x000B0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, 8, 156, 19692, 0, 0, 0, 0x20010000, bhvWarp),
		OBJECT(MODEL_NONE, 28, 2174, 13929, 0, 0, 0, 0x50020000, bhvWarp),
		TERRAIN(bob_area_5_collision),
		MACRO_OBJECTS(bob_area_5_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LIGHTHOUSE),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(6, bob_area_6),
		WARP_NODE(0x01, LEVEL_BOB, 0x05, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_BOB, 0x07, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x03, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_BOB, 0x05, 0x0B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_KING_BOBOMB, 0, -5000, -2500, 0, 0, 0, 0x00000000, bhvBoss),
		OBJECT(MODEL_HEART, 0, -4938, 0, 0, 0, 0, 0x00000000, bhvRecoveryHeart),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, -1000, -5000, 0, 0, 0, 0, 0x00030000, bhvSecretDoor),
		OBJECT(MODEL_NONE, 199, -5000, 1818, 0, -180, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_NONE, -585, -7500, 1923, 0, 0, 0, 0x2A010000, bhvWarp),
		TERRAIN(bob_area_6_collision),
		MACRO_OBJECTS(bob_area_6_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_SOUND_PLAYER),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	AREA(7, bob_area_7),
		WARP_NODE(0x01, LEVEL_BOB, 0x05, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x02, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x03, LEVEL_BOB, 0x06, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x07, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x03, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(240, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(241, LEVEL_BOB, 0x05, 0x0B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_PORKY, 0, -5000, -2500, 0, 0, 0, 0x00010000, bhvPorkyBoss),
		OBJECT(MODEL_HEART, 0, -4938, 0, 0, 0, 0, 0x00000000, bhvRecoveryHeart),
		OBJECT(MODEL_CASTLE_CASTLE_DOOR, -1000, -5000, 0, 0, 0, 0, 0x00030000, bhvSecretDoor),
		OBJECT(MODEL_NONE, 199, -5000, 1818, 0, -180, 0, 0x000A0000, bhvSpinAirborneWarp),
		TERRAIN(bob_area_7_collision),
		MACRO_OBJECTS(bob_area_7_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_SOUND_PLAYER),
		TERRAIN_TYPE(TERRAIN_GRASS),
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
