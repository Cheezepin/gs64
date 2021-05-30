const Collision ccm_area_1_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(8),
	COL_VERTEX(500, 1000, -500),
	COL_VERTEX(500, 1000, 500),
	COL_VERTEX(-500, 1000, 500),
	COL_VERTEX(-500, 1000, -500),
	COL_VERTEX(500, 0, 500),
	COL_VERTEX(-500, 0, 500),
	COL_VERTEX(-500, 0, -500),
	COL_VERTEX(500, 0, -500),
	COL_TRI_INIT(SURFACE_DEFAULT, 12),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI(4, 5, 2),
	COL_TRI(4, 2, 1),
	COL_TRI(5, 6, 3),
	COL_TRI(5, 3, 2),
	COL_TRI(6, 5, 4),
	COL_TRI(6, 4, 7),
	COL_TRI(7, 4, 1),
	COL_TRI(7, 1, 0),
	COL_TRI(6, 7, 0),
	COL_TRI(6, 0, 3),
	COL_TRI_STOP(),
	COL_END()
};
