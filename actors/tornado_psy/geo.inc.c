#include "src/game/envfx_snow.h"

const GeoLayout tornado_psy_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 191, 100),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, tornado_psy_Circle_mesh),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, tornado_psy_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
