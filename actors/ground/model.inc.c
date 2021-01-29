Lights1 ground_grass_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 ground_rocks_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx ground_z_midori_ci8_aligner[] = {gsSPEndDisplayList()};
u8 ground_z_midori_ci8[] = {
	0x0, 0x0, 0x1, 0x1, 0x2, 0x2, 0x3, 0x4, 0x5, 
	0x5, 0x6, 0x7, 0x8, 0x9, 0x9, 0xA, 0xB, 0xB, 
	0xB, 0xC, 0xC, 0x6, 0xC, 0xD, 0x6, 0xE, 0xF, 
	0x6, 0x10, 0x10, 0x6, 0x11, 0x12, 0x0, 0x1, 0x0, 
	0x4, 0x13, 0x4, 0x13, 0x5, 0x5, 0x5, 0x7, 0x14, 
	0x8, 0xA, 0xA, 0xB, 0xB, 0xC, 0xC, 0x6, 0xC, 
	0xD, 0xC, 0xF, 0xE, 0x6, 0x6, 0x10, 0x10, 0x15, 
	0x10, 0x0, 0x16, 0x16, 0x1, 0x3, 0x13, 0x13, 0x13, 
	0x7, 0x7, 0x7, 0x7, 0x8, 0x8, 0xA, 0x8, 0xB, 
	0xC, 0x17, 0xC, 0xD, 0xD, 0x6, 0x7, 0x6, 0xE, 
	0xE, 0x6, 0x6, 0x15, 0x15, 0x11, 0x16, 0x16, 0x16, 
	0x16, 0x3, 0x4, 0x4, 0x3, 0x7, 0x6, 0x7, 0x18, 
	0x8, 0x14, 0x14, 0x14, 0xC, 0x19, 0xC, 0xC, 0xD, 
	0x6, 0xD, 0x7, 0x6, 0x1A, 0x1A, 0xF, 0x15, 0x15, 
	0x15, 0x10, 0x1B, 0x1B, 0x1B, 0x1B, 0x0, 0x0, 0x1C, 
	0x1D, 0x1, 0x1, 0x1E, 0x1, 0x1F, 0x20, 0x20, 0x21, 
	0x22, 0x19, 0x19, 0x22, 0x23, 0x23, 0x24, 0x22, 0x7, 
	0x7, 0x7, 0x0, 0x7, 0x25, 0x7, 0x7, 0x1B, 0x26, 
	0x1B, 0x1B, 0x0, 0x0, 0x1C, 0x1C, 0x27, 0x1, 0x1, 
	0x27, 0x20, 0x21, 0x21, 0x21, 0x28, 0x29, 0x29, 0x19, 
	0x22, 0x24, 0x22, 0x2A, 0x7, 0x7, 0x0, 0x0, 0x7, 
	0x25, 0x2B, 0x2C, 0x2D, 0x1B, 0x2D, 0x26, 0x2E, 0x0, 
	0x1D, 0x1D, 0x27, 0x27, 0x27, 0x27, 0x21, 0x21, 0x21, 
	0x2F, 0x29, 0x19, 0x19, 0x22, 0x22, 0x24, 0x2A, 0x2A, 
	0x30, 0x7, 0x7, 0x7, 0x7, 0x25, 0x2B, 0x2C, 0x2D, 
	0x2D, 0x31, 0x31, 0x0, 0x0, 0x1C, 0x1C, 0x27, 0x27, 
	0x27, 0x27, 0x21, 0x2F, 0x2F, 0x21, 0x19, 0x22, 0x22, 
	0x22, 0x22, 0x22, 0x22, 0x22, 0x30, 0x30, 0x0, 0x30, 
	0x2C, 0x2B, 0x2B, 0x2C, 0x32, 0x33, 0x33, 0x6, 0x34, 
	0x14, 0x1C, 0x1C, 0x11, 0x35, 0x36, 0x37, 0x19, 0x19, 
	0x19, 0x19, 0xC, 0xC, 0x38, 0x38, 0x36, 0x39, 0x39, 
	0x21, 0x3A, 0x26, 0x26, 0x3B, 0x6, 0x3C, 0x3D, 0x6, 
	0x32, 0x32, 0x6, 0x6, 0x34, 0x3E, 0x34, 0x1C, 0x36, 
	0x36, 0x11, 0x11, 0x22, 0x19, 0x22, 0x1D, 0xC, 0xC, 
	0xC, 0xC, 0x1, 0x1, 0x1, 0x21, 0x26, 0x26, 0x3A, 
	0x3A, 0xC, 0x6, 0x6, 0x6, 0x3F, 0x6, 0x6, 0x3F, 
	0x34, 0x1C, 0x14, 0x14, 0x11, 0x11, 0x11, 0x11, 0x22, 
	0x22, 0x1D, 0x1D, 0x40, 0x40, 0xC, 0xC, 0x1, 0x1, 
	0x21, 0x1, 0x10, 0x10, 0x26, 0x26, 0xC, 0xC, 0x6, 
	0x6, 0x3F, 0x6, 0x6, 0x3F, 0x34, 0x14, 0x14, 0x1C, 
	0x11, 0x11, 0x11, 0x35, 0x1D, 0x1D, 0x22, 0x1D, 0x40, 
	0x40, 0xC, 0x38, 0x36, 0x1, 0x1, 0x1, 0x10, 0x10, 
	0x3B, 0x10, 0x6, 0x3C, 0x3D, 0x3D, 0x1D, 0x41, 0x42, 
	0x1D, 0x2E, 0x2E, 0x2A, 0x2E, 0x43, 0x43, 0x43, 0x44, 
	0x8, 0xC, 0x8, 0x44, 0x45, 0x45, 0xC, 0xC, 0x3C, 
	0x20, 0x24, 0x20, 0x46, 0xF, 0x46, 0x47, 0x7, 0x48, 
	0x48, 0x49, 0x4A, 0x1D, 0x1D, 0x1D, 0x2A, 0x2A, 0x2E, 
	0x45, 0x44, 0x44, 0x1D, 0x44, 0x8, 0x8, 0x44, 0x44, 
	0x6, 0x45, 0x7, 0xC, 0x3C, 0xF, 0x20, 0xF, 0x46, 
	0x46, 0x4B, 0x46, 0x48, 0x7, 0x7, 0x48, 0x41, 0x42, 
	0x1D, 0x1D, 0x2A, 0x2E, 0x45, 0x2E, 0x1D, 0x1D, 0x43, 
	0x1D, 0x8, 0xC, 0x8, 0x8, 0x6, 0x7, 0x7, 0xC, 
	0x3C, 0xF, 0x24, 0x3C, 0x4B, 0xF, 0x47, 0x47, 0x4C, 
	0x49, 0x7, 0x7, 0x42, 0x1D, 0x42, 0x1D, 0x2A, 0x2A, 
	0x2E, 0x45, 0x1D, 0x44, 0x44, 0x1D, 0x4D, 0x4D, 0xC, 
	0xC, 0x6, 0x6, 0x6, 0x7, 0x24, 0xF, 0x24, 0xF, 
	0xF, 0x4B, 0x46, 0x4B, 0x4C, 0x4C, 0x4C, 0x7, 0x39, 
	0x39, 0x39, 0x22, 0x22, 0x22, 0x22, 0x0, 0x11, 0x40, 
	0x11, 0x36, 0x19, 0x19, 0x19, 0x7, 0x4B, 0x46, 0x3C, 
	0xF, 0x26, 0x7, 0x4E, 0x7, 0x7, 0x6, 0x18, 0x6, 
	0x4C, 0x38, 0x22, 0x22, 0x20, 0x20, 0x22, 0x39, 0x22, 
	0x22, 0x22, 0x0, 0x36, 0x40, 0x11, 0x37, 0x19, 0x22, 
	0x22, 0x22, 0x4B, 0x46, 0x4B, 0x4B, 0x26, 0x1B, 0x1B, 
	0x7, 0x7, 0xD, 0x18, 0x6, 0x4C, 0x4C, 0x22, 0x19, 
	0x20, 0x20, 0x22, 0x20, 0x22, 0x4F, 0x22, 0x0, 0x11, 
	0x40, 0x40, 0x36, 0x22, 0x22, 0x22, 0x22, 0x3C, 0x4B, 
	0xF, 0xF, 0x7, 0x1B, 0x1B, 0x4E, 0xD, 0x18, 0xD, 
	0x7, 0x19, 0x19, 0x22, 0x19, 0x1C, 0x1C, 0x39, 0x39, 
	0x22, 0x50, 0x22, 0x0, 0x11, 0x11, 0x11, 0x36, 0x22, 
	0x22, 0x22, 0x7, 0x4B, 0xF, 0xF, 0xF, 0x1B, 0x1B, 
	0x1B, 0x4E, 0x18, 0x18, 0x6, 0x7, 0x19, 0x22, 0x22, 
	0x4C, 0x1D, 0x1D, 0x1D, 0x3A, 0x5, 0x5, 0x38, 0x38, 
	0x7, 0x7, 0x7, 0x7, 0x1D, 0x36, 0x36, 0x36, 0x1D, 
	0x1D, 0x1D, 0x1, 0x11, 0x11, 0x11, 0x11, 0x6, 0x6, 
	0x21, 0x4F, 0xF, 0xF, 0x51, 0x52, 0x1D, 0x22, 0x1D, 
	0x3A, 0x5, 0x5, 0x5, 0x38, 0xC, 0x0, 0xC, 0x53, 
	0x40, 0x40, 0x1D, 0x2B, 0x1D, 0x16, 0x54, 0x1D, 0xC, 
	0xC, 0x11, 0x11, 0x6, 0x21, 0x21, 0x21, 0xF, 0x51, 
	0x55, 0x55, 0x56, 0x56, 0x22, 0x1D, 0x38, 0x38, 0x38, 
	0x38, 0xC, 0xC, 0x53, 0x53, 0x40, 0x40, 0x36, 0x2B, 
	0x1D, 0x1, 0x1, 0x1D, 0xC, 0xC, 0xC, 0x57, 0x6, 
	0x6, 0x6, 0x6, 0x55, 0x51, 0x51, 0x55, 0x1D, 0x56, 
	0x56, 0x56, 0x1D, 0x38, 0x1D, 0x38, 0xC, 0xC, 0x53, 
	0x53, 0x40, 0x1D, 0x1D, 0x1D, 0x1, 0x54, 0x16, 0x1D, 
	0x11, 0xC, 0xC, 0x4B, 0x6, 0x6, 0x6, 0x6, 0x55, 
	0x51, 0xF, 0x55, 0x3B, 0x24, 0x4B, 0x4B, 0x1, 0x1D, 
	0x1D, 0x1D, 0x40, 0x40, 0x40, 0x40, 0x6, 0x7, 0x6, 
	0x7, 0x8, 0x46, 0x8, 0x8, 0x0, 0x0, 0x0, 0x1D, 
	0x44, 0x39, 0x44, 0x39, 0x58, 0x3A, 0x50, 0x58, 0x3B, 
	0x24, 0x4B, 0x4B, 0x1D, 0x1, 0x59, 0x1, 0x7, 0x30, 
	0x40, 0x30, 0x7, 0x6, 0x6, 0x6, 0x5A, 0x46, 0x8, 
	0x5A, 0x0, 0x0, 0x2E, 0x1D, 0x44, 0x44, 0x39, 0x21, 
	0x3A, 0x3A, 0x3A, 0x58, 0x24, 0x24, 0x4B, 0x4B, 0x1D, 
	0x59, 0x59, 0x59, 0x7, 0x3B, 0x30, 0x7, 0x6, 0x6, 
	0x7, 0x6, 0x8, 0x8, 0x46, 0x46, 0x0, 0x0, 0x0, 
	0x0, 0x44, 0x44, 0x39, 0x5B, 0x3A, 0x50, 0x50, 0x3A, 
	0x24, 0x4B, 0x4B, 0x4B, 0x1D, 0x1, 0x59, 0x5C, 0x7, 
	0x7, 0x30, 0x30, 0x36, 0x36, 0x6, 0x6, 0x46, 0x8, 
	0x46, 0x8, 0x0, 0x0, 0x1D, 0x5D, 0x44, 0x39, 0x21, 
	0x5B, 0x5E, 0x5E, 0x3A, 0x3A, 0x5F, 0x5F, 0x60, 0x60, 
	0xD, 0x55, 0xD, 0x55, 0x61, 0x61, 0x19, 0x61, 0x6, 
	0x6, 0x36, 0x46, 0x62, 0x62, 0x62, 0x62, 0x63, 0x36, 
	0x63, 0x36, 0x24, 0x24, 0x64, 0x64, 0x38, 0x38, 0x24, 
	0x24, 0x5F, 0x60, 0x4C, 0x4C, 0x65, 0x65, 0xD, 0x55, 
	0x66, 0x66, 0x61, 0x61, 0x36, 0x36, 0x6, 0x46, 0x4B, 
	0x4B, 0x4B, 0x4B, 0x11, 0x11, 0x11, 0x36, 0x23, 0x67, 
	0x67, 0x64, 0x24, 0x38, 0x24, 0x68, 0x4C, 0x4C, 0x4C, 
	0x4C, 0x65, 0xD, 0xD, 0xD, 0x2D, 0x2D, 0x61, 0x66, 
	0x46, 0x6, 0x46, 0x6, 0x69, 0x4B, 0x62, 0x4B, 0x63, 
	0x11, 0x3E, 0x63, 0x24, 0x24, 0x64, 0x67, 0x68, 0x2C, 
	0x38, 0x24, 0x0, 0x0, 0x0, 0x0, 0x6A, 0x6A, 0x65, 
	0x55, 0x19, 0x19, 0x66, 0x61, 0x6, 0x9, 0x9, 0x9, 
	0x62, 0x69, 0x6B, 0x4B, 0x11, 0x11, 0x3E, 0x63, 0x23, 
	0x67, 0x24, 0x23, 0x68, 0x68, 0x2C, 0x24, 
};

Gfx ground_z_midori_ci8_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 ground_z_midori_ci8_pal_rgba16[] = {
	0x34, 0x47, 0x24, 0x45, 0x3D, 0x41, 0x2C, 0x81, 0x2C, 
	0x1, 0x33, 0x85, 0x2C, 0x45, 0x2C, 0x5, 0x34, 0x45, 
	0x35, 0x43, 0x34, 0xC5, 0x3C, 0x85, 0x34, 0x5, 0x2C, 
	0x85, 0x33, 0xC1, 0x34, 0x3, 0x24, 0x83, 0x2C, 0x7, 
	0x44, 0x49, 0x23, 0x81, 0x34, 0x9, 0x3C, 0xB, 0x1C, 
	0x45, 0x2B, 0x45, 0x2D, 0x5, 0x2B, 0x85, 0x43, 0xC1, 
	0x1C, 0x43, 0x33, 0xC9, 0x34, 0x7, 0x24, 0xC3, 0x25, 
	0x3, 0x24, 0x43, 0x23, 0xC5, 0x2B, 0xC5, 0x34, 0x83, 
	0x2C, 0x3, 0x33, 0xCF, 0x24, 0x3, 0x2C, 0x9, 0x2B, 
	0x49, 0x2B, 0x47, 0x2B, 0x87, 0x2B, 0xC9, 0x2C, 0x41, 
	0x33, 0xC3, 0x33, 0xC7, 0x23, 0x7, 0x2B, 0xC3, 0x43, 
	0xC5, 0x14, 0x5, 0x1C, 0x5, 0x34, 0x4B, 0x3C, 0x49, 
	0x2B, 0xC7, 0x23, 0xC7, 0x33, 0xC5, 0x24, 0x5, 0x23, 
	0x83, 0x23, 0xC3, 0x44, 0x5, 0x54, 0x5, 0x3B, 0xC9, 
	0x3C, 0x87, 0x3C, 0x47, 0x5B, 0xC7, 0x43, 0xC7, 0x3B, 
	0xCB, 0x34, 0x85, 0x3C, 0x7, 0x2C, 0x83, 0x44, 0x3, 
	0x1C, 0x9, 0x24, 0x7, 0x1C, 0x47, 0x34, 0x43, 0x3C, 
	0x45, 0x3C, 0x5, 0x1C, 0x83, 0x23, 0x5, 0x23, 0x45, 
	0x44, 0x1, 0x24, 0x8B, 0x44, 0x89, 0x14, 0xC5, 0x2C, 
	0x47, 0x44, 0x8B, 0x44, 0x83, 0x2C, 0x43, 0xC, 0xC3, 
	0x44, 0x47, 0x1B, 0x87, 0x14, 0x43, 0x3B, 0xC7, 0x22, 
	0xC7, 0x3C, 0x83, 0x4C, 0xC3, 0x34, 0x1, 0x44, 0x45, 
	0x24, 0x47, 0x2B, 0x83, 0x34, 0xC3, 0x44, 0x81, 0x2B, 
	0x43, 0x2C, 0xC1, 0x1C, 0xC1, 0x3D, 0x43, 0x24, 0x81, 
	
};

Gfx ground_rock_ci4_aligner[] = {gsSPEndDisplayList()};
u8 ground_rock_ci4[] = {
	0x0, 0x12, 0x22, 0x21, 0x11, 0x34, 0x45, 0x66, 0x77, 
	0x77, 0x88, 0x11, 0x0, 0x0, 0x0, 0x12, 0x23, 0x22, 
	0x11, 0x11, 0x28, 0x44, 0x69, 0x99, 0x38, 0x88, 0x88, 
	0x55, 0x99, 0x20, 0x0, 0x0, 0x1, 0x12, 0x22, 0xA2, 
	0x13, 0x64, 0x44, 0x56, 0x77, 0x88, 0x88, 0xA1, 0x0, 
	0x0, 0x1, 0x22, 0x33, 0x72, 0x11, 0x1A, 0x88, 0x54, 
	0x55, 0x66, 0x88, 0x88, 0x88, 0x85, 0x59, 0x20, 0x0, 
	0x0, 0x1, 0x12, 0x22, 0xAA, 0x13, 0x64, 0xBB, 0x45, 
	0x88, 0x55, 0x88, 0x81, 0x0, 0x0, 0x2, 0x22, 0x77, 
	0x77, 0x33, 0xA3, 0x55, 0x44, 0x44, 0x46, 0x88, 0x58, 
	0x88, 0x85, 0x59, 0x22, 0x0, 0x0, 0x1, 0x11, 0x2A, 
	0xAA, 0x16, 0x44, 0xBB, 0xBB, 0xC5, 0x55, 0x88, 0x89, 
	0x10, 0x0, 0x12, 0x22, 0x77, 0x77, 0x88, 0x38, 0x44, 
	0x44, 0x44, 0x44, 0x55, 0x58, 0x88, 0x88, 0x55, 0x92, 
	0x10, 0x0, 0x1, 0x1D, 0xAA, 0xAA, 0x95, 0x44, 0x44, 
	0x44, 0x4C, 0x55, 0xEE, 0xE8, 0xA1, 0x11, 0x11, 0x33, 
	0x38, 0x88, 0x88, 0x8E, 0x55, 0x55, 0x44, 0x44, 0x44, 
	0x45, 0x55, 0x55, 0x55, 0x39, 0x11, 0x0, 0x1, 0x11, 
	0xAA, 0xAA, 0x65, 0x65, 0x44, 0x54, 0xCC, 0xC5, 0xEE, 
	0xE5, 0x9A, 0x1A, 0x11, 0x33, 0x38, 0x8E, 0xEE, 0xFF, 
	0x53, 0x38, 0x88, 0x88, 0x44, 0x44, 0xCC, 0xCC, 0x54, 
	0x59, 0x11, 0x0, 0x1, 0xD1, 0xAA, 0xA9, 0x55, 0x66, 
	0x58, 0x88, 0x5C, 0xC5, 0x5E, 0xEE, 0x89, 0x99, 0x33, 
	0x77, 0x88, 0xEE, 0xEF, 0xFF, 0x8A, 0xAA, 0x22, 0x33, 
	0x88, 0x54, 0x44, 0x44, 0x44, 0x59, 0x11, 0x10, 0x1, 
	0xDD, 0xAA, 0xA8, 0x45, 0x55, 0x55, 0x88, 0x85, 0x55, 
	0xEE, 0xEE, 0x89, 0x88, 0x77, 0x88, 0x88, 0xEE, 0xFF, 
	0xFF, 0x8A, 0xAA, 0x22, 0x22, 0x22, 0x28, 0x54, 0x44, 
	0x44, 0x53, 0x11, 0x11, 0x11, 0xDD, 0xDD, 0x95, 0x45, 
	0x55, 0x88, 0x88, 0x66, 0x5C, 0xEE, 0x44, 0x48, 0x8E, 
	0xCC, 0xCC, 0x55, 0xC4, 0x4B, 0xB5, 0x9A, 0xAA, 0x22, 
	0x22, 0xA1, 0x1A, 0x33, 0x64, 0x44, 0x55, 0xD1, 0x11, 
	0x11, 0xDA, 0xDD, 0x95, 0x55, 0x58, 0x88, 0x88, 0x66, 
	0x65, 0xEE, 0xEE, 0x4E, 0x44, 0xFF, 0xFF, 0x4B, 0xBB, 
	0xBB, 0x45, 0x33, 0x99, 0x22, 0x2A, 0xA1, 0x1D, 0x11, 
	0x33, 0x54, 0x44, 0x91, 0x11, 0x11, 0xDA, 0xDD, 0x65, 
	0x88, 0x88, 0x88, 0x88, 0x55, 0x66, 0x8E, 0x4E, 0xEE, 
	0x44, 0xBB, 0xBB, 0xBB, 0xBB, 0xB4, 0x53, 0x33, 0x98, 
	0x22, 0x12, 0x11, 0xDD, 0x11, 0x11, 0x25, 0x44, 0xCD, 
	0x11, 0x11, 0xDA, 0xD9, 0x55, 0x88, 0x88, 0x88, 0x88, 
	0x55, 0x55, 0x88, 0xE4, 0x4E, 0x44, 0xBB, 0xBB, 0xBB, 
	0xBB, 0xB4, 0x33, 0x33, 0x39, 0x22, 0x11, 0x11, 0xD, 
	0x11, 0x11, 0x28, 0x54, 0xC9, 0x11, 0xDD, 0xDA, 0x98, 
	0xC8, 0x88, 0x88, 0x88, 0x55, 0x88, 0x55, 0x88, 0x38, 
	0xC4, 0x44, 0xBB, 0xBB, 0x4F, 0xBB, 0x48, 0x32, 0x33, 
	0x33, 0x2A, 0x11, 0xA1, 0x0, 0xDA, 0x3A, 0xAA, 0x85, 
	0x46, 0x11, 0xDD, 0xDA, 0x8C, 0xC8, 0x85, 0x88, 0x88, 
	0x88, 0x88, 0x38, 0x83, 0x33, 0x33, 0x38, 0xEC, 0xCC, 
	0xFF, 0xBB, 0x43, 0x22, 0x32, 0x23, 0x2A, 0x11, 0xA1, 
	0xD0, 0xD3, 0x33, 0x33, 0x35, 0x44, 0x11, 0xAD, 0xD7, 
	0xCF, 0xC8, 0x55, 0x58, 0x83, 0x88, 0x88, 0x38, 0x88, 
	0x33, 0x33, 0x33, 0x77, 0xEE, 0xEF, 0xBB, 0x42, 0x22, 
	0x32, 0x23, 0x2A, 0xAA, 0xAA, 0xD0, 0xDA, 0x38, 0x38, 
	0x38, 0x44, 0x31, 0xAD, 0xD7, 0xCF, 0x88, 0x55, 0x83, 
	0x33, 0x33, 0x88, 0x85, 0x58, 0x88, 0x88, 0x83, 0x77, 
	0x7E, 0xEF, 0xBB, 0x82, 0x23, 0x32, 0x33, 0x22, 0xAA, 
	0xAA, 0x1D, 0xDA, 0x38, 0x88, 0x3A, 0x64, 0x61, 0x99, 
	0x98, 0x55, 0x88, 0x83, 0x33, 0x3A, 0xA3, 0x88, 0x85, 
	0xC8, 0xCC, 0xEE, 0xEE, 0x88, 0x88, 0x5C, 0x44, 0x88, 
	0x88, 0x33, 0x33, 0x32, 0x22, 0x99, 0xA1, 0x12, 0x22, 
	0x96, 0x93, 0x25, 0x59, 0x88, 0x8C, 0x58, 0x88, 0x3A, 
	0xAA, 0xA1, 0xA3, 0x88, 0x85, 0xC8, 0xCE, 0xFF, 0xFF, 
	0xE8, 0x88, 0x54, 0x4C, 0x55, 0x55, 0x88, 0x88, 0x83, 
	0x22, 0x99, 0xAA, 0xA2, 0x21, 0x39, 0x93, 0x26, 0x56, 
	0xCC, 0xCC, 0x58, 0x33, 0xAA, 0xAA, 0x11, 0xA8, 0x88, 
	0x85, 0xCC, 0xEC, 0xFF, 0xFF, 0xFC, 0xE8, 0xC4, 0x45, 
	0x55, 0x5C, 0xCC, 0x88, 0x88, 0x33, 0x99, 0x99, 0x22, 
	0xAA, 0x22, 0x39, 0x29, 0x55, 0xFF, 0xFC, 0x83, 0xAA, 
	0xDA, 0xAA, 0xA3, 0x38, 0x88, 0x85, 0x8C, 0xEC, 0xFF, 
	0xFF, 0xFF, 0xCC, 0x4B, 0x45, 0xCC, 0xCC, 0x44, 0xCC, 
	0x88, 0x88, 0x99, 0x99, 0x22, 0x11, 0x22, 0x23, 0x29, 
	0x55, 0x44, 0x48, 0x63, 0x22, 0x1A, 0xA9, 0x38, 0x88, 
	0x83, 0x88, 0x8E, 0xCC, 0xFF, 0xFF, 0xFF, 0xFC, 0x44, 
	0x44, 0xFF, 0xFF, 0xF4, 0x55, 0xEC, 0xE5, 0x83, 0x33, 
	0xA1, 0x11, 0x11, 0xA2, 0x22, 0x44, 0x44, 0xC8, 0x69, 
	0x32, 0xA1, 0x1A, 0x38, 0x89, 0x33, 0x88, 0x8E, 0xCC, 
	0xFF, 0xFF, 0xFF, 0xFF, 0x44, 0x44, 0xFF, 0xFF, 0xFF, 
	0x45, 0xCC, 0xFE, 0xE3, 0x33, 0xAA, 0x11, 0x21, 0x2A, 
	0x22, 0x44, 0x44, 0xC8, 0x66, 0x69, 0x91, 0xA9, 0x23, 
	0x93, 0xAA, 0x86, 0xEE, 0xCC, 0xFF, 0xFB, 0xFF, 0xCC, 
	0x44, 0x44, 0xBB, 0xBB, 0xBB, 0xBF, 0xFF, 0xFF, 0xCE, 
	0x83, 0x33, 0x3A, 0xA1, 0x12, 0x22, 0x44, 0x4C, 0x88, 
	0x69, 0x66, 0x99, 0x99, 0x22, 0x22, 0xAA, 0x86, 0xEC, 
	0xCC, 0xFF, 0xBB, 0xCC, 0x83, 0x88, 0x88, 0x88, 0xCF, 
	0xBF, 0xBB, 0xFC, 0x5C, 0xCC, 0xE8, 0x88, 0x88, 0x2A, 
	0x22, 0x22, 0x54, 0xCC, 0x88, 0x88, 0x88, 0x99, 0x99, 
	0x99, 0xA9, 0xA9, 0x86, 0x8E, 0xFF, 0xFF, 0xFC, 0x88, 
	0x33, 0x89, 0x89, 0x66, 0x66, 0xEE, 0xEC, 0xFF, 0xFC, 
	0xFF, 0xFE, 0x88, 0x88, 0x73, 0x22, 0x22, 0x85, 0xC8, 
	0x88, 0x88, 0x88, 0x9A, 0xA1, 0x19, 0x99, 0xA9, 0x88, 
	0x8F, 0xFF, 0xFF, 0xC8, 0x33, 0x23, 0x98, 0x88, 0x96, 
	0x99, 0x88, 0x8E, 0xFF, 0xFF, 0xFF, 0xFE, 0x83, 0x88, 
	0x77, 0x32, 0x22, 0x85, 0x87, 0x78, 0x83, 0x33, 0x9A, 
	0x11, 0x1A, 0x99, 0xAA, 0x99, 0x8F, 0xFF, 0xCC, 0x83, 
	0x23, 0x22, 0x98, 0x88, 0x39, 0x93, 0x33, 0x38, 0xCF, 
	0xFF, 0xFC, 0xCE, 0x83, 0x33, 0x77, 0x73, 0x22, 0x85, 
	0x87, 0xD7, 0x33, 0xAA, 0xA1, 0x11, 0x11, 0x99, 0x99, 
	0x99, 0x8F, 0xFF, 0xC8, 0x83, 0x22, 0x22, 0x98, 0x89, 
	0x33, 0x22, 0x33, 0x33, 0x8C, 0xFF, 0xFC, 0xEE, 0x83, 
	0x22, 0x77, 0x73, 0x22, 0x88, 0x8A, 0x1A, 0x2A, 0x22, 
	0x11, 0x1A, 0x11, 0xA9, 0x99, 0x99, 0xCF, 0xFF, 0x89, 
	0x32, 0x33, 0xAA, 0xA8, 0x83, 0xAA, 0xDD, 0xDA, 0x3A, 
	0x38, 0xCF, 0xFE, 0xE8, 0x89, 0xAA, 0xA7, 0x77, 0x33, 
	0x88, 0x3A, 0x11, 0xAA, 0xA2, 0xA1, 0x1A, 0x11, 0xA9, 
	0x66, 0x66, 0xFF, 0xFC, 0x83, 0x32, 0x33, 0xAA, 0x38, 
	0x88, 0x7A, 0xAD, 0xDA, 0x33, 0x88, 0xCF, 0xFE, 0xE8, 
	0x8A, 0xA1, 0xDA, 0x77, 0x37, 0x87, 0x3A, 0x11, 0x11, 
	0xA2, 0x2A, 0x1A, 0xA1, 0xA9, 0x66, 0x65, 0xFF, 0xC8, 
	0x92, 0x22, 0x33, 0x33, 0x38, 0x8A, 0xAA, 0xAD, 0xDD, 
	0x38, 0x88, 0xCF, 0xFF, 0xE8, 0x89, 0xA1, 0xDA, 0xA7, 
	0x37, 0x87, 0x3A, 0x11, 0x11, 0x1A, 0x2A, 0xA2, 0x99, 
	0x99, 0x96, 0x65, 0xFF, 0xC8, 0x32, 0x32, 0x33, 0x33, 
	0x38, 0x31, 0xDA, 0xAD, 0xDD, 0x88, 0xCC, 0xCC, 0xFF, 
	0xFE, 0x88, 0x9A, 0xDD, 0xAA, 0x38, 0x87, 0x9A, 0xAA, 
	0x11, 0x1D, 0xA1, 0x1A, 0x23, 0x33, 0x88, 0x84, 0xCC, 
	0x88, 0x72, 0x37, 0x93, 0xAA, 0x77, 0xAD, 0xD, 0xAA, 
	0x18, 0x8C, 0x55, 0x53, 0x88, 0x88, 0x99, 0x99, 0x99, 
	0xAA, 0x3C, 0xC8, 0x9A, 0xA1, 0x11, 0x1D, 0x11, 0x13, 
	0x33, 0x23, 0x88, 0x84, 0xCC, 0x88, 0x72, 0x33, 0x33, 
	0xAA, 0xA7, 0xAD, 0x0, 0xAA, 0x88, 0x8C, 0x53, 0xA3, 
	0x8A, 0xAA, 0x99, 0x99, 0x99, 0x66, 0x3C, 0xC8, 0x9A, 
	0xA1, 0x11, 0x1, 0x11, 0xA3, 0x33, 0x28, 0xEE, 0xE4, 
	0xCC, 0x88, 0x73, 0x77, 0x99, 0xAA, 0xA7, 0x7D, 0x0, 
	0xD8, 0x88, 0xC8, 0x8A, 0xAA, 0xAD, 0xDD, 0x11, 0xAA, 
	0x1A, 0x96, 0x44, 0xC8, 0x99, 0xA1, 0x1D, 0x0, 0xAA, 
	0xA3, 0x33, 0x84, 0x44, 0x44, 0xCC, 0x88, 0x77, 0x77, 
	0x89, 0x3A, 0xA7, 0x7A, 0x0, 0xD8, 0x8C, 0x88, 0x3A, 
	0xAA, 0xAA, 0x3A, 0xAA, 0x11, 0x11, 0xA9, 0xC4, 0xC8, 
	0x33, 0xAD, 0x2, 0x22, 0x22, 0x33, 0x55, 0x55, 0x44, 
	0x44, 0x44, 0x48, 0x88, 0x88, 0x88, 0x99, 0x33, 0x73, 
	0x11, 0x18, 0xCC, 0x88, 0xAA, 0x31, 0xDD, 0xAA, 0xAA, 
	0xDD, 0x0, 0xDA, 0x85, 0x58, 0x83, 0x3D, 0x2, 0x29, 
	0x83, 0x88, 0x55, 0x99, 0x22, 0x22, 0x98, 0x44, 0xE8, 
	0xE8, 0x68, 0x89, 0x33, 0x77, 0xAA, 0x38, 0xCC, 0x78, 
	0xA3, 0x3A, 0xDD, 0xDA, 0xAA, 0xDD, 0xDD, 0x11, 0x35, 
	0x58, 0x88, 0x8A, 0x29, 0x95, 0x88, 0x88, 0x92, 0x22, 
	0x11, 0x11, 0xAA, 0x94, 0x44, 0xEE, 0x66, 0x89, 0x37, 
	0x77, 0x33, 0x38, 0xC8, 0x77, 0xA3, 0x83, 0xDD, 0xDA, 
	0x77, 0xDD, 0x11, 0x11, 0x35, 0x58, 0x88, 0x88, 0x55, 
	0x55, 0x88, 0x32, 0x20, 0x0, 0x11, 0x11, 0xAA, 0xA9, 
	0xE4, 0x44, 0x66, 0x89, 0x77, 0x77, 0x88, 0x88, 0xC8, 
	0x77, 0xA8, 0x83, 0xAD, 0xDD, 0xA7, 0xAD, 0xA1, 0xAA, 
	0x38, 0x55, 0x85, 0x44, 0x66, 0x83, 0x83, 0x3A, 0xDD, 
	0x0, 0xDD, 0x1, 0xDD, 0xDA, 0x34, 0x44, 0x55, 0x69, 
	0x77, 0x78, 0x88, 0x88, 0xC8, 0x77, 0x78, 0x87, 0x7D, 
	0xDD, 0x37, 0x77, 0xD7, 0x77, 0x33, 0xCC, 0x84, 0x45, 
	0x8A, 0x3A, 0xAA, 0xAD, 0xD, 0xDD, 0x0, 0xD1, 0xDD, 
	0xDA, 0x16, 0x44, 0x45, 0x56, 0x77, 0x77, 0x88, 0x88, 
	0xC8, 0x78, 0x78, 0x88, 0x77, 0xD7, 0x77, 0x77, 0x77, 
	0x77, 0x33, 0xC4, 0x54, 0x42, 0xAA, 0xAA, 0xAA, 0xDD, 
	0xDD, 0xDD, 0xD, 0xD1, 0xDD, 0xDD, 0x13, 0x44, 0x44, 
	0x45, 0x58, 0x88, 0x85, 0x88, 0xC8, 0x88, 0x78, 0x88, 
	0x88, 0x77, 0x77, 0x77, 0x77, 0x77, 0x33, 0xC4, 0x44, 
	0x82, 0xAA, 0xAA, 0xAA, 0xDD, 0xDD, 0xDD, 0xDD, 0xD, 
	0xDA, 0xAD, 0x13, 0x64, 0x44, 0x44, 0xCC, 0x58, 0x88, 
	0x55, 0xCC, 0x88, 0x88, 0x88, 0x88, 0x88, 0x77, 0x77, 
	0x78, 0x88, 0x33, 0x44, 0xFF, 0x72, 0xD7, 0x7D, 0xAA, 
	0x11, 0x11, 0x11, 0x1D, 0xDD, 0xDA, 0xAA, 0x22, 0x85, 
	0xFF, 0xFF, 0xFF, 0xE8, 0x88, 0x88, 0xEE, 0x85, 0x88, 
	0x88, 0x88, 0x88, 0x88, 0x88, 0x85, 0x44, 0x44, 0x44, 
	0xFF, 0x72, 0xD7, 0x77, 0xAA, 0xAA, 0xAA, 0xAA, 0xA1, 
	0x1D, 0xDD, 0xAA, 0x22, 0x85, 0xFF, 0xFF, 0xFF, 0xFE, 
	0xE8, 0x88, 0xEE, 0xE8, 0x88, 0x88, 0x88, 0x88, 0x88, 
	0x8E, 0x44, 0x44, 0x44, 0x44, 0xFF, 0x72, 0xD7, 0x77, 
	0x33, 0x3A, 0x33, 0x3A, 0xAD, 0xDD, 0xDA, 0xAA, 0x22, 
	0x85, 0x8E, 0xFF, 0xFF, 0xFF, 0xFF, 0xE8, 0xEE, 0xE5, 
	0x88, 0x88, 0x88, 0x88, 0x8E, 0x44, 0x44, 0x55, 0x88, 
	0x88, 0xEF, 0xE2, 0xDD, 0x77, 0x33, 0x3A, 0x33, 0x31, 
	0xAD, 0x1D, 0xA3, 0x33, 0x22, 0x85, 0x88, 0x88, 0x88, 
	0xEF, 0xFF, 0xFE, 0xEE, 0xEE, 0x88, 0x88, 0x88, 0x88, 
	0x44, 0x4E, 0x88, 0x88, 0x99, 0x98, 0x95, 0x59, 0xAA, 
	0x3A, 0x33, 0x33, 0x77, 0x72, 0x32, 0x23, 0x77, 0x77, 
	0x7D, 0x8C, 0x55, 0x83, 0x11, 0x37, 0x88, 0x88, 0x55, 
	0x55, 0xE8, 0x88, 0x88, 0x84, 0x59, 0x99, 0x22, 0x32, 
	0x22, 0x22, 0x95, 0x56, 0xAA, 0xA8, 0x33, 0x33, 0x77, 
	0x77, 0x73, 0x77, 0x77, 0x77, 0xDD, 0x7C, 0x55, 0x58, 
	0x31, 0x11, 0x22, 0x38, 0x66, 0x55, 0x4E, 0x88, 0x38, 
	0x48, 0x92, 0x22, 0x22, 0x11, 0x11, 0x22, 0x26, 0x56, 
	0x8A, 0xA8, 0x83, 0x33, 0x77, 0x77, 0x77, 0x77, 0x77, 
	0x73, 0xDD, 0x7C, 0x55, 0x58, 0x87, 0x73, 0x22, 0x22, 
	0x29, 0x65, 0x44, 0x4E, 0x38, 0x43, 0x22, 0x22, 0x22, 
	0x11, 0x11, 0x12, 0x22, 0x95, 0x63, 0x3A, 0x83, 0xA3, 
	0x77, 0x77, 0x77, 0x77, 0x33, 0x73, 0xDD, 0x8C, 0x58, 
	0x88, 0x77, 0x88, 0x88, 0x82, 0x22, 0x96, 0x44, 0x44, 
	0x44, 0x82, 0x22, 0x22, 0x22, 0x21, 0x21, 0x11, 0x1A, 
	0x98, 0x55, 0x99, 0x88, 0x33, 0x77, 0x77, 0x77, 0x73, 
	0xAA, 0x3A, 0xAA, 0x85, 0x58, 0x88, 0x77, 0x78, 0xCE, 
	0xE8, 0x33, 0x33, 0x84, 0x44, 0x55, 0x8A, 0x22, 0x22, 
	0x33, 0x22, 0x22, 0x11, 0x11, 0xA9, 0x96, 0x56, 0x38, 
	0x83, 0x77, 0x73, 0x33, 0x32, 0xAA, 0xAA, 0x33, 0x55, 
	0x58, 0x88, 0x88, 0x77, 0xCC, 0xC8, 0x93, 0x22, 0x28, 
	0x44, 0x58, 0xAA, 0x11, 0x22, 0x99, 0x32, 0x22, 0x11, 
	0x11, 0xA9, 0x29, 0x65, 0x88, 0x88, 0x33, 0x22, 0x32, 
	0x22, 0xAA, 0x3A, 0x33, 0x55, 0x87, 0x78, 0x88, 0x78, 
	0xCC, 0xC8, 0x93, 0x22, 0x25, 0x44, 0x58, 0xAA, 0x11, 
	0x12, 0x66, 0x93, 0x22, 0x10, 0x11, 0x1A, 0x22, 0x96, 
	0xEE, 0x88, 0x72, 0x22, 0x32, 0x32, 0xAA, 0xA3, 0x33, 
	0x55, 0x87, 0x77, 0x77, 0x77, 0xCC, 0xE8, 0x39, 0x32, 
	0x25, 0x44, 0x53, 0xAA, 0x11, 0x12, 0x99, 0x99, 0x22, 
	0x10, 0x11, 0x12, 0x1A, 0x98, 0xCC, 0x88, 0x99, 0x92, 
	0x22, 0x22, 0x22, 0x23, 0x85, 0x55, 0x77, 0x77, 0x22, 
	0x22, 0x9C, 0xCC, 0x88, 0x99, 0x29, 0x55, 0x6A, 0x3A, 
	0x32, 0x23, 0x22, 0x22, 0x22, 0x21, 0x11, 0x21, 0x11, 
	0xA8, 0x8C, 0xC8, 0x99, 0x99, 0x33, 0x33, 0x88, 0x88, 
	0x55, 0x55, 0x77, 0x77, 0x22, 0x22, 0xD9, 0xCC, 0x8C, 
	0x89, 0x29, 0x55, 0x83, 0x33, 0x93, 0x32, 0x11, 0x22, 
	0x22, 0x22, 0x22, 0x22, 0x11, 0x19, 0xCC, 0x4C, 0x69, 
	0x96, 0x38, 0x88, 0x88, 0x88, 0x55, 0x58, 0x77, 0x33, 
	0x22, 0x11, 0x1D, 0x9C, 0xCC, 0x88, 0x65, 0x55, 0x83, 
	0x38, 0x69, 0x32, 0x10, 0x1, 0x22, 0x22, 0x22, 0x22, 
	0x11, 0x1A, 0x3C, 0x44, 0x56, 0x66, 0x88, 0x88, 0x88, 
	0x88, 0x88, 0x88, 0x77, 0x32, 0x21, 0x11, 0x11, 0xDC, 
	0xCC, 0x88, 0x65, 0x56, 0x83, 0x38, 0x69, 0x32, 0x0, 
	0x0, 0x1, 0x22, 0x22, 0x22, 0x11, 0x11, 0x36, 0x44, 
	0x44, 0x44, 0xCC, 0xCC, 0x89, 0x99, 0x22, 0x22, 0x99, 
	0x22, 0x11, 0x11, 0x11, 0xD9, 0x84, 0x88, 0x54, 0x43, 
	0x93, 0x98, 0x83, 0x22, 0x10, 0x0, 0x0, 0x1, 0x22, 
	0x22, 0x22, 0x11, 0x13, 0x44, 0x44, 0x48, 0x88, 0x88, 
	0x89, 0xAA, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x11, 
	0x1D, 0x94, 0x48, 0x54, 0x53, 0x83, 0x99, 0x88, 0x33, 
	0x21, 0x0, 0x0, 0x0, 0x2, 0x22, 0x22, 0x11, 0x11, 
	0x64, 0x44, 0x89, 0x77, 0x78, 0x9A, 0x1A, 0x10, 0x0, 
	0x2, 0x22, 0x22, 0x22, 0x11, 0x11, 0xA8, 0x44, 0x55, 
	0x33, 0x93, 0x99, 0x88, 0x88, 0x22, 0x10, 0x0, 0x0, 
	0x1, 0x22, 0x22, 0x11, 0x11, 0x34, 0x44, 0x89, 0x77, 
	0x77, 0x9A, 0x11, 0x0, 0x0, 0x0, 0x22, 0x22, 0x22, 
	0x11, 0x11, 0xA9, 0x44, 0x55, 0x99, 0x39, 0x89, 0x88, 
	0x88, 0x22, 0x10, 0x0, 0x0, 
};

Gfx ground_rock_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 ground_rock_ci4_pal_rgba16[] = {
	0xBC, 0xDF, 0xA4, 0x59, 0x93, 0x95, 0x8B, 0x11, 0x51, 
	0xCB, 0x62, 0x4D, 0x6A, 0xD1, 0x8B, 0x51, 0x72, 0xCF, 
	0x83, 0x53, 0x93, 0xD5, 0x41, 0x49, 0x62, 0xD, 0xA4, 
	0x57, 0x62, 0x4B, 0x51, 0xC9, 
};

Vtx ground_Circle_mesh_vtx_0[4] = {
	{{{62, 0, -62},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-63, 0, -62},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-63, 0, 62},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{62, 0, 62},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx ground_Circle_mesh_tri_0[] = {
	gsSPVertex(ground_Circle_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};Vtx ground_Circle_mesh_vtx_1[16] = {
	{{{-63, -250, -62},0, {4074, 996},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-63, -250, 63},0, {1014, 996},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-63, 0, 62},0, {1014, -5124},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-63, 0, -62},0, {4074, -5124},{0x81, 0x0, 0x0, 0xFF}}},
	{{{62, -250, -62},0, {1002, 7140},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-63, -250, -62},0, {-2058, 7140},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-63, 0, -62},0, {-2058, 1020},{0x0, 0x0, 0x81, 0xFF}}},
	{{{62, 0, -62},0, {1002, 1020},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-63, -250, 63},0, {1002, 996},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{62, -250, 63},0, {-2058, 996},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{62, 0, 62},0, {-2058, -5124},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-63, 0, 62},0, {1002, -5124},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{62, -250, 63},0, {4074, 7140},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{62, -250, -62},0, {1014, 7140},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{62, 0, -62},0, {1014, 1020},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{62, 0, 62},0, {4074, 1020},{0x7F, 0x0, 0x0, 0xFF}}},
};

Gfx ground_Circle_mesh_tri_1[] = {
	gsSPVertex(ground_Circle_mesh_vtx_1 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPEndDisplayList(),
};


Gfx mat_ground_grass[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ground_z_midori_ci8_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 107),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 32, ground_z_midori_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 124, 124),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(ground_grass_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_ground_grass[] = {
	gsDPPipeSync(),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};


Gfx mat_ground_rocks[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ground_rock_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 15),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 32, ground_rock_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 126, 252),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPSetLights1(ground_rocks_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_ground_rocks[] = {
	gsDPPipeSync(),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};


Gfx ground_Circle_mesh[] = {
	gsSPDisplayList(mat_ground_grass),
	gsSPDisplayList(ground_Circle_mesh_tri_0),
	gsSPDisplayList(mat_revert_ground_grass),
	gsSPDisplayList(mat_ground_rocks),
	gsSPDisplayList(ground_Circle_mesh_tri_1),
	gsSPDisplayList(mat_revert_ground_rocks),
	gsSPEndDisplayList(),
};



Gfx ground_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};