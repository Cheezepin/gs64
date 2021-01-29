void scroll_halo_Sphere_mesh_vtx_0() {
	int i = 0;
	int count = 163;
	int width = 16 * 0x20;
	int height = 16 * 0x20;

	static int currentY = 0;
	int deltaY;
	Vtx *vertices = segmented_to_virtual(halo_Sphere_mesh_vtx_0);

	deltaY = (int)(-2.0 * 0x20) % height;

	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[1] += deltaY;
	}
	currentY += deltaY;

}
void scroll_actor_geo_halo() {
	scroll_halo_Sphere_mesh_vtx_0();

}
