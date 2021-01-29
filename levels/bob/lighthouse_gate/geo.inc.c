#include "src/game/envfx_snow.h"

const GeoLayout lighthouse_gate_geo[] = {
	GEO_CULLING_RADIUS(32767),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, lighthouse_gate_000_displaylist_mesh),
		GEO_DISPLAY_LIST(LAYER_ALPHA, lighthouse_gate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
