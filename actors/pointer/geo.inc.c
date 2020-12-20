#include "src/game/envfx_snow.h"

const GeoLayout pointer_geo[] = {
	GEO_CULLING_RADIUS(32767),
	GEO_OPEN_NODE(),
		GEO_BILLBOARD_WITH_PARAMS_AND_DL(LAYER_OPAQUE, 0, 0, 0, pointer_Cube_mesh),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, pointer_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
