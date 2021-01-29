#include "src/game/envfx_snow.h"

const GeoLayout plant_geo[] = {
	GEO_CULLING_RADIUS(32767),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, plant_render_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, plant_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
