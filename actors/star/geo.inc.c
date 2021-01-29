#include "src/game/envfx_snow.h"

const GeoLayout star_switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_000_displaylist_mesh_mat_override_star_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout star_switch_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_000_displaylist_mesh_mat_override_purple_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout star_switch_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_000_displaylist_mesh_mat_override_blue_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout star_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(0, 155, 100),
		GEO_OPEN_NODE(),
			GEO_SCALE(LAYER_FORCE, 16384),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_ALPHA, star_001_displaylist_mesh),
				GEO_SWITCH_CASE(4, geo_switch_bparam2),
				GEO_OPEN_NODE(),
					GEO_NODE_START(),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, star_000_displaylist_mesh),
					GEO_CLOSE_NODE(),
					GEO_BRANCH(1, star_switch_opt1),
					GEO_BRANCH(1, star_switch_opt2),
					GEO_BRANCH(1, star_switch_opt3),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, star_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, star_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
