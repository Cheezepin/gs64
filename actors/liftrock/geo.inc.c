#include "src/game/envfx_snow.h"

const GeoLayout liftrock_geo[] = {
	GEO_CULLING_RADIUS(32767),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 191, 300),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, liftrock_render_mesh),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, liftrock_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
