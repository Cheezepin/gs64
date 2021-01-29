Lights1 frost_spire_ice_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx frost_spire_transice_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 frost_spire_transice_rgba32[] = {
	0x76, 0x9e, 0xb8, 0xaf, 0x58, 0x80, 0xa0, 0xaf, 
	0x62, 0x8a, 0xaa, 0xaf, 0x6c, 0x94, 0xb4, 0xaf, 
	0x86, 0xae, 0xca, 0xaf, 0x86, 0xae, 0xca, 0xaf, 
	0xaa, 0xca, 0xe2, 0xaf, 0xa4, 0xc4, 0xe0, 0xaf, 
	0xd2, 0xe4, 0xf0, 0xaf, 0xda, 0xec, 0xf4, 0xaf, 
	0xd0, 0xe8, 0xf8, 0xaf, 0xbe, 0xd6, 0xec, 0xaf, 
	0x9a, 0xba, 0xd6, 0xaf, 0xac, 0xcc, 0xe4, 0xaf, 
	0x9a, 0xb8, 0xce, 0xaf, 0xb0, 0xc8, 0xdc, 0xaf, 
	0xb0, 0xd0, 0xe8, 0xaf, 0xa2, 0xc6, 0xe2, 0xaf, 
	0xc4, 0xe4, 0xf0, 0xaf, 0xc4, 0xe4, 0xf0, 0xaf, 
	0xc2, 0xda, 0xea, 0xaf, 0xc8, 0xe0, 0xf0, 0xaf, 
	0xb6, 0xd0, 0xe2, 0xaf, 0x7c, 0xa0, 0xbc, 0xaf, 
	0x78, 0x9c, 0xbc, 0xaf, 0x84, 0xa6, 0xc6, 0xaf, 
	0x88, 0xae, 0xca, 0xaf, 0xac, 0xc8, 0xd8, 0xaf, 
	0xb4, 0xcc, 0xe0, 0xaf, 0xb8, 0xd0, 0xe0, 0xaf, 
	0x8e, 0xb4, 0xcc, 0xaf, 0x96, 0xba, 0xd2, 0xaf, 
	0x90, 0xb8, 0xd0, 0xaf, 0x68, 0x90, 0xae, 0xaf, 
	0x60, 0x88, 0xa8, 0xaf, 0x6a, 0x92, 0xb2, 0xaf, 
	0x84, 0xac, 0xca, 0xaf, 0x8c, 0xb4, 0xcc, 0xaf, 
	0xb4, 0xd4, 0xea, 0xaf, 0xb8, 0xd8, 0xec, 0xaf, 
	0xbc, 0xd4, 0xe4, 0xaf, 0xc4, 0xd8, 0xe8, 0xaf, 
	0xa8, 0xc0, 0xda, 0xaf, 0x9c, 0xb4, 0xd2, 0xaf, 
	0x92, 0xb2, 0xd2, 0xaf, 0x9a, 0xba, 0xd6, 0xaf, 
	0x94, 0xb2, 0xca, 0xaf, 0xa8, 0xc8, 0xd8, 0xaf, 
	0x9c, 0xc2, 0xe0, 0xaf, 0x94, 0xbc, 0xdc, 0xaf, 
	0xa4, 0xc4, 0xde, 0xaf, 0xc6, 0xe6, 0xf2, 0xaf, 
	0xcc, 0xe4, 0xf2, 0xaf, 0xd4, 0xec, 0xf6, 0xaf, 
	0xc0, 0xd8, 0xe8, 0xaf, 0x7c, 0xa0, 0xbc, 0xaf, 
	0x7c, 0x9e, 0xbe, 0xaf, 0x94, 0xb0, 0xd0, 0xaf, 
	0x90, 0xb4, 0xcc, 0xaf, 0xac, 0xc8, 0xd8, 0xaf, 
	0xba, 0xd2, 0xe0, 0xaf, 0xb8, 0xd0, 0xe0, 0xaf, 
	0x98, 0xb8, 0xd0, 0xaf, 0x9a, 0xbc, 0xd4, 0xaf, 
	0xa0, 0xc2, 0xdc, 0xaf, 0x70, 0xa2, 0xc0, 0xaf, 
	0x6a, 0x96, 0xb6, 0xaf, 0x68, 0x94, 0xb4, 0xaf, 
	0x80, 0xa4, 0xc4, 0xaf, 0x96, 0xbc, 0xd4, 0xaf, 
	0xbc, 0xdc, 0xec, 0xaf, 0xa2, 0xc2, 0xd8, 0xaf, 
	0x94, 0xb2, 0xca, 0xaf, 0x9a, 0xb6, 0xce, 0xaf, 
	0x84, 0xa4, 0xc4, 0xaf, 0x88, 0xaa, 0xc8, 0xaf, 
	0x92, 0xb2, 0xca, 0xaf, 0x96, 0xb8, 0xce, 0xaf, 
	0x9c, 0xb6, 0xd2, 0xaf, 0x9a, 0xb4, 0xd0, 0xaf, 
	0xac, 0xcc, 0xe4, 0xaf, 0x92, 0xb8, 0xd0, 0xaf, 
	0x84, 0xac, 0xcc, 0xaf, 0x84, 0xac, 0xcc, 0xaf, 
	0xce, 0xe6, 0xf2, 0xaf, 0xd8, 0xf0, 0xf8, 0xaf, 
	0xb4, 0xd8, 0xec, 0xaf, 0x78, 0x9e, 0xbe, 0xaf, 
	0x82, 0xa2, 0xc2, 0xaf, 0x96, 0xb6, 0xd2, 0xaf, 
	0x9c, 0xc0, 0xd8, 0xaf, 0x8e, 0xb4, 0xce, 0xaf, 
	0xc8, 0xd8, 0xe8, 0xaf, 0xc0, 0xd0, 0xe4, 0xaf, 
	0x70, 0x98, 0xb8, 0xaf, 0xb8, 0xd2, 0xe2, 0xaf, 
	0xa8, 0xc8, 0xe0, 0xaf, 0x76, 0xa6, 0xc2, 0xaf, 
	0x84, 0xa8, 0xc8, 0xaf, 0x78, 0xa0, 0xc0, 0xaf, 
	0x80, 0xa4, 0xc4, 0xaf, 0xa2, 0xc4, 0xdc, 0xaf, 
	0xa4, 0xc4, 0xda, 0xaf, 0x9c, 0xbc, 0xd4, 0xaf, 
	0x94, 0xb2, 0xca, 0xaf, 0x88, 0xa8, 0xc0, 0xaf, 
	0x82, 0xa2, 0xc2, 0xaf, 0x90, 0xb6, 0xd0, 0xaf, 
	0xa4, 0xcc, 0xdc, 0xaf, 0x9a, 0xbe, 0xd2, 0xaf, 
	0x96, 0xb4, 0xce, 0xaf, 0x8c, 0xa6, 0xc6, 0xaf, 
	0xb0, 0xd0, 0xe8, 0xaf, 0x96, 0xba, 0xd2, 0xaf, 
	0x7c, 0xa4, 0xc4, 0xaf, 0x60, 0x88, 0xa8, 0xaf, 
	0x90, 0xb4, 0xce, 0xaf, 0xd8, 0xf0, 0xf8, 0xaf, 
	0xb0, 0xd2, 0xe8, 0xaf, 0x70, 0x98, 0xb8, 0xaf, 
	0x86, 0xa6, 0xc6, 0xaf, 0x90, 0xb0, 0xcc, 0xaf, 
	0x84, 0xaa, 0xc6, 0xaf, 0x6e, 0x96, 0xb4, 0xaf, 
	0xb0, 0xc6, 0xda, 0xaf, 0xba, 0xcc, 0xe0, 0xaf, 
	0x70, 0x98, 0xb8, 0xaf, 0xb8, 0xd2, 0xe2, 0xaf, 
	0xa6, 0xc6, 0xdc, 0xaf, 0x78, 0xa4, 0xc0, 0xaf, 
	0x9c, 0xbe, 0xde, 0xaf, 0x8a, 0xb2, 0xd2, 0xaf, 
	0x86, 0xaa, 0xc6, 0xaf, 0x98, 0xb8, 0xd0, 0xaf, 
	0xa0, 0xc8, 0xe0, 0xaf, 0x96, 0xb8, 0xd6, 0xaf, 
	0x9e, 0xbe, 0xd6, 0xaf, 0x98, 0xb8, 0xd0, 0xaf, 
	0x84, 0xa4, 0xc4, 0xaf, 0x9c, 0xbc, 0xd4, 0xaf, 
	0xb4, 0xdc, 0xec, 0xaf, 0xb0, 0xd4, 0xe4, 0xaf, 
	0x8c, 0xac, 0xcc, 0xaf, 0x8a, 0xa8, 0xc8, 0xaf, 
	0xb0, 0xd8, 0xf0, 0xaf, 0x8a, 0xac, 0xca, 0xaf, 
	0x76, 0x9e, 0xbe, 0xaf, 0x6a, 0x92, 0xb6, 0xaf, 
	0x68, 0x90, 0xb0, 0xaf, 0xb6, 0xd6, 0xee, 0xaf, 
	0xac, 0xcc, 0xe0, 0xaf, 0x70, 0x98, 0xb4, 0xaf, 
	0x9c, 0xbc, 0xd4, 0xaf, 0x8a, 0xaa, 0xc6, 0xaf, 
	0x74, 0x98, 0xb8, 0xaf, 0x68, 0x90, 0xb0, 0xaf, 
	0x6e, 0x8c, 0xaa, 0xaf, 0x98, 0xb2, 0xc6, 0xaf, 
	0x68, 0x90, 0xb0, 0xaf, 0xc0, 0xd4, 0xe8, 0xaf, 
	0x7e, 0xa8, 0xc4, 0xaf, 0x7e, 0xa8, 0xc4, 0xaf, 
	0xa0, 0xc0, 0xe0, 0xaf, 0x8c, 0xb4, 0xd4, 0xaf, 
	0x7c, 0xa4, 0xc4, 0xaf, 0x86, 0xaa, 0xc6, 0xaf, 
	0xa8, 0xd0, 0xe8, 0xaf, 0xa8, 0xd0, 0xe8, 0xaf, 
	0xb8, 0xd8, 0xf0, 0xaf, 0xb4, 0xd4, 0xec, 0xaf, 
	0x9c, 0xbc, 0xd4, 0xaf, 0xa0, 0xc0, 0xd8, 0xaf, 
	0xb4, 0xdc, 0xec, 0xaf, 0xb4, 0xdc, 0xec, 0xaf, 
	0xa2, 0xbc, 0xdc, 0xaf, 0x8c, 0xac, 0xcc, 0xaf, 
	0xb0, 0xd8, 0xf0, 0xaf, 0x8c, 0xb0, 0xcc, 0xaf, 
	0x74, 0x9c, 0xbc, 0xaf, 0x88, 0xb0, 0xca, 0xaf, 
	0x80, 0xa4, 0xc0, 0xaf, 0x80, 0xa6, 0xc4, 0xaf, 
	0x90, 0xb6, 0xcc, 0xaf, 0x70, 0x98, 0xb4, 0xaf, 
	0xa0, 0xc0, 0xd8, 0xaf, 0x92, 0xb2, 0xcc, 0xaf, 
	0x98, 0xb8, 0xd8, 0xaf, 0x7c, 0xa0, 0xc0, 0xaf, 
	0x78, 0x94, 0xb0, 0xaf, 0x78, 0x94, 0xb0, 0xaf, 
	0x7c, 0xa0, 0xbc, 0xaf, 0xc0, 0xd4, 0xe8, 0xaf, 
	0x6c, 0x94, 0xb4, 0xaf, 0x7a, 0x9c, 0xbc, 0xaf, 
	0x9c, 0xbc, 0xce, 0xaf, 0x9c, 0xbc, 0xce, 0xaf, 
	0x96, 0xb2, 0xd0, 0xaf, 0x7a, 0x9e, 0xc4, 0xaf, 
	0x98, 0xba, 0xda, 0xaf, 0xb8, 0xd8, 0xf0, 0xaf, 
	0xb8, 0xd6, 0xea, 0xaf, 0xb6, 0xd4, 0xe8, 0xaf, 
	0xa2, 0xc2, 0xda, 0xaf, 0xac, 0xd0, 0xe4, 0xaf, 
	0xc2, 0xe2, 0xf0, 0xaf, 0xc4, 0xe4, 0xf0, 0xaf, 
	0xa8, 0xce, 0xe2, 0xaf, 0xa0, 0xc4, 0xdc, 0xaf, 
	0xc0, 0xe0, 0xf8, 0xaf, 0x8c, 0xac, 0xc8, 0xaf, 
	0x8e, 0xae, 0xcc, 0xaf, 0xa8, 0xc8, 0xdc, 0xaf, 
	0xb6, 0xd6, 0xea, 0xaf, 0xae, 0xce, 0xe6, 0xaf, 
	0x8e, 0xaa, 0xc8, 0xaf, 0x74, 0x98, 0xbc, 0xaf, 
	0xa8, 0xc8, 0xdc, 0xaf, 0xb4, 0xd0, 0xe0, 0xaf, 
	0xb2, 0xd4, 0xec, 0xaf, 0xb0, 0xd4, 0xec, 0xaf, 
	0x92, 0xba, 0xd2, 0xaf, 0x70, 0x98, 0xb0, 0xaf, 
	0x78, 0x90, 0xa8, 0xaf, 0xc4, 0xd4, 0xe4, 0xaf, 
	0x6c, 0x94, 0xb4, 0xaf, 0x64, 0x8a, 0xaa, 0xaf, 
	0x8c, 0xac, 0xc4, 0xaf, 0xc0, 0xd8, 0xe8, 0xaf, 
	0xaa, 0xc2, 0xdc, 0xaf, 0x82, 0xa4, 0xc6, 0xaf, 
	0x90, 0xb6, 0xd2, 0xaf, 0xb8, 0xd8, 0xf0, 0xaf, 
	0xc4, 0xde, 0xee, 0xaf, 0xbc, 0xd8, 0xea, 0xaf, 
	0xa8, 0xcc, 0xe0, 0xaf, 0xb8, 0xe0, 0xf0, 0xaf, 
	0xc4, 0xe4, 0xf0, 0xaf, 0xbc, 0xdc, 0xf0, 0xaf, 
	0xb0, 0xd8, 0xe8, 0xaf, 0xb6, 0xdc, 0xec, 0xaf, 
	0xc0, 0xe0, 0xf8, 0xaf, 0xa0, 0xc0, 0xd8, 0xaf, 
	0xa8, 0xc8, 0xdc, 0xaf, 0xb8, 0xd6, 0xe6, 0xaf, 
	0xc4, 0xe4, 0xf4, 0xaf, 0xc4, 0xe4, 0xf4, 0xaf, 
	0xa2, 0xba, 0xd4, 0xaf, 0x86, 0xa2, 0xc4, 0xaf, 
	0xa8, 0xc8, 0xdc, 0xaf, 0xc0, 0xd8, 0xe8, 0xaf, 
	0xb4, 0xd4, 0xec, 0xaf, 0xba, 0xd8, 0xf0, 0xaf, 
	0x94, 0xbc, 0xd4, 0xaf, 0x7a, 0xa2, 0xba, 0xaf, 
	0x70, 0x88, 0xa0, 0xaf, 0xa0, 0xb4, 0xc8, 0xaf, 
	0x70, 0x90, 0xb0, 0xaf, 0x5a, 0x7a, 0x9e, 0xaf, 
	0x78, 0x9c, 0xbc, 0xaf, 0xc8, 0xe0, 0xf0, 0xaf, 
	0xc0, 0xd4, 0xe0, 0xaf, 0x74, 0x90, 0xb4, 0xaf, 
	0x7c, 0xa4, 0xc0, 0xaf, 0x9c, 0xc4, 0xdc, 0xaf, 
	0xb4, 0xda, 0xf0, 0xaf, 0xda, 0xe6, 0xf0, 0xaf, 
	0xc0, 0xdc, 0xe8, 0xaf, 0xc8, 0xe8, 0xf0, 0xaf, 
	0xcc, 0xe4, 0xf0, 0xaf, 0xc4, 0xe2, 0xf0, 0xaf, 
	0xce, 0xea, 0xf4, 0xaf, 0xd0, 0xea, 0xf2, 0xaf, 
	0xc6, 0xe6, 0xf2, 0xaf, 0xb4, 0xd4, 0xe8, 0xaf, 
	0xac, 0xcc, 0xe4, 0xaf, 0xcc, 0xec, 0xf4, 0xaf, 
	0xd8, 0xf0, 0xf8, 0xaf, 0xd0, 0xe8, 0xf4, 0xaf, 
	0x9c, 0xb8, 0xcc, 0xaf, 0x6c, 0x8a, 0xac, 0xaf, 
	0xb2, 0xd0, 0xe2, 0xaf, 0xc8, 0xe2, 0xec, 0xaf, 
	0xd0, 0xe8, 0xf8, 0xaf, 0xb4, 0xd0, 0xe4, 0xaf, 
	0x88, 0xb0, 0xd0, 0xaf, 0x7c, 0xa0, 0xc0, 0xaf, 
	0x76, 0x96, 0xb6, 0xaf, 0x7a, 0x9a, 0xba, 0xaf, 
	0x68, 0x88, 0xa8, 0xaf, 0x64, 0x84, 0xa4, 0xaf, 
	0x78, 0x9c, 0xbc, 0xaf, 0xb4, 0xd0, 0xe4, 0xaf, 
	0xc0, 0xd4, 0xe0, 0xaf, 0x6a, 0x88, 0xae, 0xaf, 
	0x6e, 0x96, 0xb4, 0xaf, 0x92, 0xba, 0xd2, 0xaf, 
	0xb8, 0xdc, 0xf0, 0xaf, 0xe0, 0xe8, 0xf0, 0xaf, 
	0xc4, 0xe4, 0xec, 0xaf, 0xc8, 0xe8, 0xf0, 0xaf, 
	0xcc, 0xe4, 0xf0, 0xaf, 0xce, 0xe6, 0xf0, 0xaf, 
	0xd4, 0xec, 0xf0, 0xaf, 0xd4, 0xec, 0xf0, 0xaf, 
	0xcc, 0xec, 0xf6, 0xaf, 0xbe, 0xde, 0xee, 0xaf, 
	0xbc, 0xdc, 0xec, 0xaf, 0xd0, 0xf0, 0xf8, 0xaf, 
	0xd8, 0xf0, 0xf8, 0xaf, 0xca, 0xe6, 0xf4, 0xaf, 
	0x78, 0x96, 0xb4, 0xaf, 0x58, 0x78, 0xa0, 0xaf, 
	0xa4, 0xc6, 0xdc, 0xaf, 0xd0, 0xe8, 0xf0, 0xaf, 
	0xd0, 0xe8, 0xf8, 0xaf, 0x9a, 0xbc, 0xd6, 0xaf, 
	0x88, 0xb0, 0xd0, 0xaf, 0x78, 0xa0, 0xc0, 0xaf, 
	0x8c, 0xac, 0xcc, 0xaf, 0x7c, 0x9c, 0xbc, 0xaf, 
	0x7a, 0x9a, 0xba, 0xaf, 0x68, 0x88, 0xa8, 0xaf, 
	0x68, 0x88, 0xa8, 0xaf, 0x84, 0xa4, 0xbc, 0xaf, 
	0xbe, 0xd6, 0xe0, 0xaf, 0x78, 0x96, 0xb0, 0xaf, 
	0x6c, 0x94, 0xb4, 0xaf, 0x80, 0xa8, 0xc8, 0xaf, 
	0xa4, 0xc4, 0xd4, 0xaf, 0xd8, 0xe8, 0xf0, 0xaf, 
	0xd8, 0xe8, 0xf0, 0xaf, 0xd8, 0xe8, 0xf0, 0xaf, 
	0xba, 0xd0, 0xd8, 0xaf, 0xd8, 0xe8, 0xf0, 0xaf, 
	0xe0, 0xf0, 0xf0, 0xaf, 0xd8, 0xe8, 0xec, 0xaf, 
	0xd6, 0xee, 0xf8, 0xaf, 0xd0, 0xe8, 0xf8, 0xaf, 
	0xc8, 0xe0, 0xf0, 0xaf, 0xc8, 0xe0, 0xf0, 0xaf, 
	0xd8, 0xf0, 0xf8, 0xaf, 0xc8, 0xe2, 0xf0, 0xaf, 
	0x64, 0x8c, 0xac, 0xaf, 0x50, 0x78, 0x98, 0xaf, 
	0xa8, 0xc8, 0xde, 0xaf, 0xd2, 0xe4, 0xf4, 0xaf, 
	0xb6, 0xce, 0xe2, 0xaf, 0x80, 0xa0, 0xc0, 0xaf, 
	0x70, 0x94, 0xb0, 0xaf, 0x74, 0x98, 0xb4, 0xaf, 
	0x8c, 0xac, 0xcc, 0xaf, 0x80, 0xa0, 0xc0, 0xaf, 
	0x68, 0x88, 0xa8, 0xaf, 0x74, 0x94, 0xb4, 0xaf, 
	0x6e, 0x8e, 0xac, 0xaf, 0x6e, 0x8e, 0xac, 0xaf, 
	0x80, 0x9e, 0xb6, 0xaf, 0x9a, 0xb6, 0xc8, 0xaf, 
	0x6c, 0x94, 0xb4, 0xaf, 0x76, 0x9e, 0xbe, 0xaf, 
	0x88, 0xae, 0xca, 0xaf, 0xd8, 0xe8, 0xf0, 0xaf, 
	0xd8, 0xe8, 0xf0, 0xaf, 0xce, 0xe0, 0xea, 0xaf, 
	0xac, 0xc4, 0xcc, 0xaf, 0xd8, 0xe8, 0xf0, 0xaf, 
	0xe0, 0xf0, 0xf0, 0xaf, 0xc2, 0xd8, 0xe2, 0xaf, 
	0xd0, 0xe8, 0xf8, 0xaf, 0xd4, 0xec, 0xf8, 0xaf, 
	0xc8, 0xe0, 0xf0, 0xaf, 0x9c, 0xb6, 0xd0, 0xaf, 
	0xd2, 0xea, 0xf4, 0xaf, 0xc0, 0xdc, 0xee, 0xaf, 
	0x66, 0x8e, 0xae, 0xaf, 0x52, 0x7a, 0x9a, 0xaf, 
	0x98, 0xc0, 0xd8, 0xaf, 0xc6, 0xdc, 0xec, 0xaf, 
	0x8e, 0xaa, 0xc8, 0xaf, 0x80, 0xa0, 0xc0, 0xaf, 
	0x6c, 0x8c, 0xac, 0xaf, 0x6e, 0x90, 0xae, 0xaf, 
	0x84, 0xa4, 0xc4, 0xaf, 0x80, 0xa0, 0xc0, 0xaf, 
	0x5e, 0x76, 0x96, 0xaf, 0x78, 0x98, 0xb0, 0xaf, 
	0x80, 0xa0, 0xbc, 0xaf, 0x78, 0x98, 0xb6, 0xaf, 
	0x5e, 0x7e, 0x9c, 0xaf, 0x7a, 0x98, 0xae, 0xaf, 
	0x80, 0xa2, 0xbc, 0xaf, 0x80, 0xa0, 0xb8, 0xaf, 
	0x78, 0x98, 0xb8, 0xaf, 0xcc, 0xdc, 0xe4, 0xaf, 
	0xd0, 0xe0, 0xf0, 0xaf, 0x98, 0xb4, 0xc8, 0xaf, 
	0xa8, 0xc8, 0xd8, 0xaf, 0xc8, 0xe0, 0xe8, 0xaf, 
	0xd2, 0xe6, 0xf0, 0xaf, 0xa8, 0xc8, 0xda, 0xaf, 
	0xc4, 0xd4, 0xe2, 0xaf, 0xde, 0xe8, 0xf2, 0xaf, 
	0x96, 0xac, 0xc2, 0xaf, 0x78, 0x94, 0xb0, 0xaf, 
	0xb0, 0xca, 0xe0, 0xaf, 0xa8, 0xc4, 0xda, 0xaf, 
	0x52, 0x78, 0x9e, 0xaf, 0x58, 0x7c, 0xa0, 0xaf, 
	0x94, 0xb0, 0xc8, 0xaf, 0xb2, 0xcc, 0xde, 0xaf, 
	0x64, 0x84, 0xa4, 0xaf, 0x80, 0xa8, 0xc0, 0xaf, 
	0x60, 0x80, 0xa0, 0xaf, 0x80, 0x98, 0xb8, 0xaf, 
	0x88, 0xa8, 0xc8, 0xaf, 0x8a, 0xaa, 0xca, 0xaf, 
	0x60, 0x7a, 0x98, 0xaf, 0x78, 0x98, 0xb0, 0xaf, 
	0x9a, 0xba, 0xd2, 0xaf, 0x8e, 0xae, 0xc6, 0xaf, 
	0x80, 0xa0, 0xb0, 0xaf, 0x72, 0x92, 0xa8, 0xaf, 
	0x78, 0x9c, 0xb8, 0xaf, 0x78, 0x9c, 0xb8, 0xaf, 
	0x78, 0x98, 0xb8, 0xaf, 0xaa, 0xc2, 0xd2, 0xaf, 
	0xa2, 0xbc, 0xce, 0xaf, 0x70, 0x96, 0xae, 0xaf, 
	0x84, 0xac, 0xc4, 0xaf, 0xc8, 0xe0, 0xe8, 0xaf, 
	0xa2, 0xc4, 0xd8, 0xaf, 0x90, 0xb8, 0xd0, 0xaf, 
	0xa4, 0xbc, 0xd0, 0xaf, 0xd4, 0xe0, 0xec, 0xaf, 
	0x72, 0x90, 0xae, 0xaf, 0x6e, 0x8c, 0xaa, 0xaf, 
	0x84, 0xa2, 0xc0, 0xaf, 0x84, 0xa2, 0xc0, 0xaf, 
	0x52, 0x78, 0x9e, 0xaf, 0x6c, 0x8c, 0xac, 0xaf, 
	0x96, 0xb4, 0xca, 0xaf, 0x7c, 0x9c, 0xb8, 0xaf, 
	0x70, 0x94, 0xb0, 0xaf, 0x78, 0xa0, 0xb8, 0xaf, 
	0x7c, 0x94, 0xb4, 0xaf, 0xa0, 0xb8, 0xd8, 0xaf, 
	0x90, 0xb4, 0xd0, 0xaf, 0x9a, 0xbe, 0xda, 0xaf, 
	0x68, 0x88, 0xa8, 0xaf, 0x7c, 0x9c, 0xbc, 0xaf, 
	0xa8, 0xc8, 0xe0, 0xaf, 0xaa, 0xca, 0xe2, 0xaf, 
	0x8e, 0xae, 0xcc, 0xaf, 0x80, 0xa0, 0xc0, 0xaf, 
	0x72, 0x9a, 0xba, 0xaf, 0x6e, 0x96, 0xb6, 0xaf, 
	0x6c, 0x92, 0xb2, 0xaf, 0x88, 0xa6, 0xbe, 0xaf, 
	0x74, 0x9c, 0xbc, 0xaf, 0x82, 0xa4, 0xc4, 0xaf, 
	0x8c, 0xb2, 0xca, 0xaf, 0xb6, 0xd0, 0xe2, 0xaf, 
	0x94, 0xbc, 0xd4, 0xaf, 0x98, 0xbe, 0xd6, 0xaf, 
	0xa4, 0xbc, 0xd0, 0xaf, 0xcc, 0xdc, 0xe8, 0xaf, 
	0x5e, 0x80, 0xa0, 0xaf, 0x70, 0x94, 0xb4, 0xaf, 
	0x86, 0xa0, 0xbe, 0xaf, 0x68, 0x88, 0xa8, 0xaf, 
	0x6c, 0x8c, 0xac, 0xaf, 0x84, 0xa4, 0xc4, 0xaf, 
	0x70, 0x98, 0xb8, 0xaf, 0x70, 0x98, 0xb8, 0xaf, 
	0x8c, 0xb2, 0xcc, 0xaf, 0x7a, 0x9a, 0xba, 0xaf, 
	0x90, 0xae, 0xc4, 0xaf, 0xb0, 0xcc, 0xd8, 0xaf, 
	0xa0, 0xc0, 0xde, 0xaf, 0x9c, 0xbc, 0xdc, 0xaf, 
	0x7e, 0x9e, 0xbe, 0xaf, 0x8c, 0xac, 0xcc, 0xaf, 
	0xb4, 0xd4, 0xec, 0xaf, 0xb0, 0xd0, 0xe8, 0xaf, 
	0xa0, 0xc0, 0xd8, 0xaf, 0x94, 0xb4, 0xd0, 0xaf, 
	0x76, 0x9e, 0xbe, 0xaf, 0x6e, 0x96, 0xb6, 0xaf, 
	0x70, 0x94, 0xb4, 0xaf, 0x74, 0x98, 0xb4, 0xaf, 
	0x80, 0xa2, 0xc2, 0xaf, 0x84, 0xa4, 0xc4, 0xaf, 
	0xa0, 0xc0, 0xd4, 0xaf, 0x98, 0xba, 0xd0, 0xaf, 
	0xa8, 0xc8, 0xe0, 0xaf, 0xa8, 0xc8, 0xe0, 0xaf, 
	0xb6, 0xcc, 0xda, 0xaf, 0xb6, 0xca, 0xd8, 0xaf, 
	0x6c, 0x8e, 0xae, 0xaf, 0x70, 0x94, 0xb4, 0xaf, 
	0xaa, 0xc0, 0xd6, 0xaf, 0x94, 0xac, 0xc8, 0xaf, 
	0x80, 0xa0, 0xc0, 0xaf, 0x90, 0xb0, 0xd0, 0xaf, 
	0x58, 0x78, 0xa0, 0xaf, 0x76, 0xa0, 0xbe, 0xaf, 
	0x8c, 0xb4, 0xcc, 0xaf, 0x7c, 0x9c, 0xbc, 0xaf, 
	0xa4, 0xc0, 0xd0, 0xaf, 0xc8, 0xe2, 0xe8, 0xaf, 
	0xb4, 0xd4, 0xf0, 0xaf, 0xac, 0xcc, 0xe8, 0xaf, 
	0xa0, 0xc0, 0xd8, 0xaf, 0xb8, 0xd8, 0xf0, 0xaf, 
	0xb8, 0xe0, 0xf8, 0xaf, 0xb4, 0xd8, 0xf0, 0xaf, 
	0xa6, 0xc6, 0xe4, 0xaf, 0xae, 0xce, 0xec, 0xaf, 
	0x96, 0xb2, 0xce, 0xaf, 0x92, 0xb0, 0xcc, 0xaf, 
	0x86, 0xa6, 0xc4, 0xaf, 0xa4, 0xc4, 0xd6, 0xaf, 
	0xb4, 0xd4, 0xe4, 0xaf, 0x9c, 0xbc, 0xd4, 0xaf, 
	0xa4, 0xcc, 0xe0, 0xaf, 0xac, 0xd4, 0xe6, 0xaf, 
	0xa2, 0xca, 0xe8, 0xaf, 0xa8, 0xd0, 0xe8, 0xaf, 
	0xbc, 0xdc, 0xe8, 0xaf, 0xbc, 0xdc, 0xe8, 0xaf, 
	0x62, 0x90, 0xb6, 0xaf, 0x78, 0xa0, 0xc4, 0xaf, 
	0xc8, 0xe0, 0xf0, 0xaf, 0x98, 0xb8, 0xd0, 0xaf, 
	0x8e, 0xac, 0xca, 0xaf, 0xa4, 0xbc, 0xd4, 0xaf, 
	0x68, 0x92, 0xaa, 0xaf, 0x7c, 0xaa, 0xc2, 0xaf, 
	0x72, 0x96, 0xb6, 0xaf, 0x70, 0x98, 0xb8, 0xaf, 
	0xa4, 0xc4, 0xd4, 0xaf, 0xd0, 0xec, 0xf0, 0xaf, 
	0xb8, 0xe0, 0xf0, 0xaf, 0xb8, 0xe0, 0xf0, 0xaf, 
	0x7a, 0x9a, 0xba, 0xaf, 0x9a, 0xba, 0xd4, 0xaf, 
	0xb2, 0xd6, 0xee, 0xaf, 0xac, 0xca, 0xe2, 0xaf, 
	0x9c, 0xbc, 0xd6, 0xaf, 0xc0, 0xe0, 0xf8, 0xaf, 
	0x9e, 0xbc, 0xd0, 0xaf, 0xac, 0xc8, 0xd8, 0xaf, 
	0xa8, 0xc8, 0xd8, 0xaf, 0xb8, 0xd4, 0xe4, 0xaf, 
	0xc8, 0xe4, 0xf0, 0xaf, 0xb8, 0xd8, 0xe8, 0xaf, 
	0xb0, 0xd8, 0xea, 0xaf, 0xbc, 0xe4, 0xf4, 0xaf, 
	0xae, 0xd6, 0xee, 0xaf, 0xae, 0xd6, 0xee, 0xaf, 
	0xb6, 0xd6, 0xe4, 0xaf, 0xa2, 0xc2, 0xd8, 0xaf, 
	0x62, 0x90, 0xb6, 0xaf, 0x8e, 0xb2, 0xd0, 0xaf, 
	0xbc, 0xd6, 0xe8, 0xaf, 0x96, 0xb6, 0xce, 0xaf, 
	0x88, 0xa8, 0xc8, 0xaf, 0xb6, 0xce, 0xe4, 0xaf, 
	0x64, 0x90, 0xa8, 0xaf, 0x78, 0xa4, 0xbc, 0xaf, 
	0x74, 0x9c, 0xbc, 0xaf, 0x78, 0xa0, 0xc0, 0xaf, 
	0xa4, 0xc4, 0xd4, 0xaf, 0xd0, 0xec, 0xf0, 0xaf, 
	0xb8, 0xe0, 0xf0, 0xaf, 0x92, 0xb2, 0xca, 0xaf, 
	0x68, 0x88, 0xa6, 0xaf, 0x72, 0x92, 0xae, 0xaf, 
	0x80, 0x98, 0xb0, 0xaf, 0x8a, 0xa2, 0xba, 0xaf, 
	0xa0, 0xb8, 0xd2, 0xaf, 0xb2, 0xca, 0xde, 0xaf, 
	0x98, 0xb8, 0xd2, 0xaf, 0x68, 0x88, 0xac, 0xaf, 
	0xa2, 0xc0, 0xd2, 0xaf, 0xd8, 0xf0, 0xf8, 0xaf, 
	0xd4, 0xea, 0xf4, 0xaf, 0xca, 0xe4, 0xf0, 0xaf, 
	0xc4, 0xe2, 0xf4, 0xaf, 0xb8, 0xdc, 0xf0, 0xaf, 
	0xb0, 0xd4, 0xf0, 0xaf, 0xa4, 0xc6, 0xe4, 0xaf, 
	0xaa, 0xca, 0xda, 0xaf, 0x90, 0xb0, 0xc6, 0xaf, 
	0x84, 0xa0, 0xc0, 0xaf, 0xa8, 0xc2, 0xd8, 0xaf, 
	0x80, 0x98, 0xb4, 0xaf, 0x7a, 0x92, 0xb0, 0xaf, 
	0xae, 0xc6, 0xda, 0xaf, 0xc2, 0xda, 0xe8, 0xaf, 
	0x64, 0x8c, 0xac, 0xaf, 0x6a, 0x92, 0xb2, 0xaf, 
	0x78, 0xa0, 0xc0, 0xaf, 0x84, 0xa4, 0xc4, 0xaf, 
	0x8c, 0xac, 0xc8, 0xaf, 0xd0, 0xf0, 0xf8, 0xaf, 
	0xb0, 0xd0, 0xe8, 0xaf, 0x6e, 0x8e, 0xae, 0xaf, 
	0x70, 0x90, 0xa8, 0xaf, 0x66, 0x86, 0xa4, 0xaf, 
	0x56, 0x6e, 0x8c, 0xaf, 0x7a, 0x92, 0xaa, 0xaf, 
	0xac, 0xc4, 0xda, 0xaf, 0x90, 0xa8, 0xc8, 0xaf, 
	0x74, 0x94, 0xb8, 0xaf, 0x50, 0x70, 0x98, 0xaf, 
	0x72, 0x90, 0xae, 0xaf, 0xae, 0xca, 0xda, 0xaf, 
	0xd6, 0xea, 0xf4, 0xaf, 0xd8, 0xec, 0xf4, 0xaf, 
	0xcc, 0xe6, 0xf6, 0xaf, 0xc6, 0xe2, 0xf4, 0xaf, 
	0xb0, 0xd4, 0xf0, 0xaf, 0x96, 0xbc, 0xd6, 0xaf, 
	0x98, 0xb8, 0xc8, 0xaf, 0x94, 0xb4, 0xc6, 0xaf, 
	0x98, 0xb8, 0xd0, 0xaf, 0xa8, 0xc2, 0xd8, 0xaf, 
	0x76, 0x8e, 0xae, 0xaf, 0x84, 0x9c, 0xb8, 0xaf, 
	0xa6, 0xbe, 0xd4, 0xaf, 0xae, 0xc6, 0xda, 0xaf, 
	0x66, 0x8e, 0xae, 0xaf, 0x74, 0x9c, 0xbc, 0xaf, 
	0x84, 0xa6, 0xc6, 0xaf, 0x88, 0xa8, 0xc8, 0xaf, 
	0x80, 0xa0, 0xc0, 0xaf, 0xaa, 0xca, 0xdc, 0xaf, 
	0x74, 0x94, 0xb2, 0xaf, 0x68, 0x88, 0xa8, 0xaf, 
	0x74, 0x9a, 0xb2, 0xaf, 0x80, 0xa4, 0xbc, 0xaf, 
	0x58, 0x70, 0x8a, 0xaf, 0x68, 0x80, 0x9c, 0xaf, 
	0xbc, 0xce, 0xe6, 0xaf, 0x88, 0xa0, 0xbc, 0xaf, 
	0x60, 0x80, 0xa0, 0xaf, 0x44, 0x64, 0x84, 0xaf, 
	0x64, 0x84, 0x9c, 0xaf, 0x86, 0xa6, 0xb4, 0xaf, 
	0xa0, 0xbc, 0xc8, 0xaf, 0xce, 0xe0, 0xe8, 0xaf, 
	0xd8, 0xe8, 0xf8, 0xaf, 0xd8, 0xe8, 0xf8, 0xaf, 
	0xc6, 0xde, 0xec, 0xaf, 0x98, 0xb8, 0xd8, 0xaf, 
	0x8a, 0xb2, 0xd2, 0xaf, 0x8e, 0xb6, 0xd6, 0xaf, 
	0xa4, 0xc4, 0xdc, 0xaf, 0x8a, 0xaa, 0xc6, 0xaf, 
	0x84, 0xa4, 0xc2, 0xaf, 0x88, 0xa8, 0xc8, 0xaf, 
	0x9c, 0xbc, 0xd0, 0xaf, 0x90, 0xb0, 0xc8, 0xaf, 
	0x6e, 0x90, 0xb0, 0xaf, 0x80, 0xa8, 0xc8, 0xaf, 
	0x84, 0xac, 0xc4, 0xaf, 0x86, 0xac, 0xc6, 0xaf, 
	0x6c, 0x8c, 0xaa, 0xaf, 0x86, 0xa6, 0xc4, 0xaf, 
	0x72, 0x98, 0xb8, 0xaf, 0x6c, 0x94, 0xb4, 0xaf, 
	0x8e, 0xac, 0xc4, 0xaf, 0xa8, 0xc0, 0xd8, 0xaf, 
	0x6e, 0x8a, 0xa6, 0xaf, 0x68, 0x80, 0x9c, 0xaf, 
	0xc8, 0xd8, 0xf0, 0xaf, 0x68, 0x88, 0xa6, 0xaf, 
	0x4e, 0x6e, 0x8e, 0xaf, 0x50, 0x70, 0x90, 0xaf, 
	0x58, 0x78, 0x98, 0xaf, 0x78, 0x98, 0xa8, 0xaf, 
	0x80, 0xa4, 0xb4, 0xaf, 0x78, 0x9e, 0xae, 0xaf, 
	0xa0, 0xbc, 0xd4, 0xaf, 0xbc, 0xd4, 0xe8, 0xaf, 
	0xac, 0xc8, 0xe0, 0xaf, 0x98, 0xb8, 0xd8, 0xaf, 
	0x84, 0xac, 0xcc, 0xaf, 0x8e, 0xb6, 0xd6, 0xaf, 
	0x90, 0xb0, 0xc8, 0xaf, 0x82, 0xa2, 0xbc, 0xaf, 
	0x8c, 0xac, 0xcc, 0xaf, 0x90, 0xb0, 0xd0, 0xaf, 
	0x8c, 0xb0, 0xc4, 0xaf, 0x88, 0xaa, 0xc2, 0xaf, 
	0x76, 0x9c, 0xbc, 0xaf, 0x80, 0xa8, 0xc8, 0xaf, 
	0x84, 0xac, 0xc4, 0xaf, 0x82, 0xa6, 0xc2, 0xaf, 
	0x6c, 0x8c, 0xaa, 0xaf, 0x7e, 0x9e, 0xbc, 0xaf, 
	0x88, 0xa8, 0xc8, 0xaf, 0x7c, 0x9e, 0xbe, 0xaf, 
	0x9a, 0xbc, 0xd6, 0xaf, 0xa8, 0xc8, 0xe0, 0xaf, 
	0x7c, 0x9c, 0xb6, 0xaf, 0x68, 0x88, 0xa4, 0xaf, 
	0x9a, 0xb2, 0xc8, 0xaf, 0x60, 0x78, 0x98, 0xaf, 
	0x62, 0x82, 0xa2, 0xaf, 0x6a, 0x8a, 0xaa, 0xaf, 
	0x70, 0x90, 0xaa, 0xaf, 0x74, 0x94, 0xac, 0xaf, 
	0x76, 0x92, 0xac, 0xaf, 0x74, 0x92, 0xaa, 0xaf, 
	0x76, 0x96, 0xbe, 0xaf, 0x8c, 0xb4, 0xcc, 0xaf, 
	0x80, 0xa4, 0xc4, 0xaf, 0x74, 0x9a, 0xba, 0xaf, 
	0x74, 0x98, 0xb8, 0xaf, 0x88, 0xa8, 0xc8, 0xaf, 
	0x88, 0xa8, 0xc2, 0xaf, 0x90, 0xb0, 0xc8, 0xaf, 
	0x8c, 0xaa, 0xca, 0xaf, 0x90, 0xac, 0xcc, 0xaf, 
	0x88, 0xa8, 0xc8, 0xaf, 0x76, 0x9a, 0xba, 0xaf, 
	0x7c, 0xa4, 0xbc, 0xaf, 0x88, 0xac, 0xc4, 0xaf, 
	0x78, 0x98, 0xb6, 0xaf, 0x7a, 0x9a, 0xb4, 0xaf, 
	0x7c, 0xa4, 0xc2, 0xaf, 0x92, 0xb6, 0xce, 0xaf, 
	0x8e, 0xae, 0xca, 0xaf, 0x7e, 0x9e, 0xbe, 0xaf, 
	0xa8, 0xc8, 0xe0, 0xaf, 0xba, 0xda, 0xec, 0xaf, 
	0x84, 0xa4, 0xc0, 0xaf, 0x74, 0x94, 0xb0, 0xaf, 
	0x84, 0x9c, 0xb8, 0xaf, 0x60, 0x78, 0x98, 0xaf, 
	0x6c, 0x8c, 0xac, 0xaf, 0x6e, 0x8e, 0xae, 0xaf, 
	0x6c, 0x8c, 0xa8, 0xaf, 0x72, 0x92, 0xac, 0xaf, 
	0x7c, 0x96, 0xae, 0xaf, 0x72, 0x90, 0xaa, 0xaf, 
	0x84, 0xac, 0xc4, 0xaf, 0x90, 0xb8, 0xd0, 0xaf, 
	0x84, 0xa6, 0xc6, 0xaf, 0x80, 0xa4, 0xc4, 0xaf, 
	0x8a, 0xaa, 0xca, 0xaf, 0xa0, 0xbc, 0xdc, 0xaf, 
	0x9e, 0xbe, 0xd4, 0xaf, 0x9e, 0xbe, 0xd4, 0xaf, 
	0xa6, 0xbc, 0xd4, 0xaf, 0x90, 0xac, 0xcc, 0xaf, 
	0x88, 0xa8, 0xc8, 0xaf, 0x70, 0x98, 0xb8, 0xaf, 
	0x88, 0xac, 0xc4, 0xaf, 0x8e, 0xb0, 0xc8, 0xaf, 
	0x72, 0x92, 0xb0, 0xaf, 0x82, 0xa2, 0xbc, 0xaf, 
	0xa0, 0xc2, 0xd6, 0xaf, 0xaa, 0xca, 0xdc, 0xaf, 
	0x7a, 0x9a, 0xba, 0xaf, 0x8a, 0xaa, 0xc6, 0xaf, 
	0xc4, 0xdc, 0xec, 0xaf, 0xc0, 0xd8, 0xea, 0xaf, 
	0x86, 0x9e, 0xbe, 0xaf, 0x7c, 0x94, 0xb4, 0xaf, 
	0x6e, 0x92, 0xb2, 0xaf, 0x6a, 0x90, 0xb0, 0xaf, 
	0x70, 0x8c, 0xa8, 0xaf, 0x66, 0x84, 0xa2, 0xaf, 
	0x6e, 0x88, 0xa8, 0xaf, 0x7e, 0x9c, 0xbc, 0xaf, 
	0x7c, 0xa2, 0xc2, 0xaf, 0x7c, 0xa4, 0xc4, 0xaf, 
	0x88, 0xac, 0xcc, 0xaf, 0x90, 0xb2, 0xd0, 0xaf, 
	0x94, 0xb2, 0xca, 0xaf, 0x9c, 0xb8, 0xd0, 0xaf, 
	0xa2, 0xbc, 0xd6, 0xaf, 0xd8, 0xf0, 0xf8, 0xaf, 
	0xa4, 0xcc, 0xe0, 0xaf, 0x84, 0xac, 0xc6, 0xaf, 
	0xb6, 0xce, 0xe4, 0xaf, 0x88, 0xa8, 0xc8, 0xaf, 
	0x94, 0xb4, 0xd0, 0xaf, 0x82, 0xa8, 0xc0, 0xaf, 
	0xa8, 0xca, 0xda, 0xaf, 0x78, 0xa4, 0xbc, 0xaf, 
	0x84, 0xa4, 0xc2, 0xaf, 0xc6, 0xe0, 0xf2, 0xaf, 
	0xc0, 0xe0, 0xf0, 0xaf, 0x8c, 0xae, 0xcc, 0xaf, 
	0x78, 0x98, 0xb8, 0xaf, 0xa2, 0xc2, 0xd6, 0xaf, 
	0xc4, 0xdc, 0xec, 0xaf, 0xb6, 0xce, 0xe4, 0xaf, 
	0x6a, 0x82, 0xa8, 0xaf, 0x78, 0x90, 0xb0, 0xaf, 
	0x74, 0x9a, 0xba, 0xaf, 0x7c, 0x9e, 0xbe, 0xaf, 
	0x74, 0x8e, 0xa8, 0xaf, 0x74, 0x90, 0xac, 0xaf, 
	0x8c, 0xac, 0xcc, 0xaf, 0x84, 0xa2, 0xc2, 0xaf, 
	0x92, 0xb4, 0xd4, 0xaf, 0x82, 0xa8, 0xc8, 0xaf, 
	0x8c, 0xb0, 0xce, 0xaf, 0xa8, 0xc4, 0xde, 0xaf, 
	0x9c, 0xb6, 0xce, 0xaf, 0xbc, 0xd0, 0xe8, 0xaf, 
	0xd8, 0xf0, 0xf8, 0xaf, 0xc4, 0xdc, 0xec, 0xaf, 
	0x8a, 0xb2, 0xcc, 0xaf, 0x78, 0xa0, 0xc0, 0xaf, 
	0xbc, 0xd4, 0xe8, 0xaf, 0x98, 0xb4, 0xd0, 0xaf, 
	0x78, 0x9c, 0xbc, 0xaf, 0x90, 0xb2, 0xcc, 0xaf, 
	0xa8, 0xca, 0xda, 0xaf, 0x6c, 0x9c, 0xb8, 0xaf, 
	0xa2, 0xbe, 0xd8, 0xaf, 0xd0, 0xe8, 0xf8, 0xaf, 
	0xac, 0xd0, 0xe4, 0xaf, 0x70, 0x96, 0xb6, 0xaf, 
	0x7e, 0x9e, 0xbc, 0xaf, 0xb2, 0xd2, 0xe2, 0xaf, 
	0xb6, 0xce, 0xe0, 0xaf, 0xa0, 0xbc, 0xd0, 0xaf, 
	0x50, 0x70, 0x90, 0xaf, 0x84, 0xaa, 0xc4, 0xaf, 
	0x80, 0xa8, 0xc8, 0xaf, 0x80, 0xa8, 0xc8, 0xaf, 
	0x8e, 0xa6, 0xc4, 0xaf, 0xb2, 0xca, 0xdc, 0xaf, 
	0xa4, 0xbe, 0xd8, 0xaf, 0xa2, 0xbc, 0xd6, 0xaf, 
	0xa0, 0xba, 0xd2, 0xaf, 0x98, 0xb6, 0xce, 0xaf, 
	0xac, 0xc4, 0xdc, 0xaf, 0xb2, 0xca, 0xe0, 0xaf, 
	0xaa, 0xca, 0xd6, 0xaf, 0xd8, 0xec, 0xf0, 0xaf, 
	0xc8, 0xe0, 0xf0, 0xaf, 0xa8, 0xc6, 0xda, 0xaf, 
	0x6e, 0x96, 0xb6, 0xaf, 0x70, 0x98, 0xb4, 0xaf, 
	0xa6, 0xc6, 0xd8, 0xaf, 0xac, 0xcc, 0xdc, 0xaf, 
	0x78, 0xa0, 0xc0, 0xaf, 0xa0, 0xc0, 0xda, 0xaf, 
	0x84, 0xa4, 0xc4, 0xaf, 0x88, 0xa8, 0xc8, 0xaf, 
	0xb0, 0xc8, 0xe4, 0xaf, 0xb8, 0xd0, 0xea, 0xaf, 
	0x7e, 0x9c, 0xbc, 0xaf, 0x60, 0x80, 0xa0, 0xaf, 
	0x8a, 0xa8, 0xc0, 0xaf, 0x98, 0xb2, 0xca, 0xaf, 
	0xc0, 0xd8, 0xe8, 0xaf, 0x86, 0xa2, 0xbc, 0xaf, 
	0x5c, 0x7c, 0x9c, 0xaf, 0x80, 0xa4, 0xc0, 0xaf, 
	0x88, 0xb0, 0xd0, 0xaf, 0x72, 0x96, 0xba, 0xaf, 
	0xba, 0xd2, 0xe2, 0xaf, 0xc2, 0xda, 0xe8, 0xaf, 
	0xa0, 0xba, 0xd4, 0xaf, 0xb0, 0xc8, 0xe0, 0xaf, 
	0xbc, 0xd0, 0xe8, 0xaf, 0xbc, 0xd0, 0xe8, 0xaf, 
	0xb2, 0xca, 0xe0, 0xaf, 0xbe, 0xd6, 0xe8, 0xaf, 
	0xbc, 0xd8, 0xe0, 0xaf, 0xe0, 0xf2, 0xf4, 0xaf, 
	0xc8, 0xe0, 0xf0, 0xaf, 0x94, 0xb8, 0xcc, 0xaf, 
	0x84, 0xac, 0xc4, 0xaf, 0x78, 0xa0, 0xbc, 0xaf, 
	0x8a, 0xb0, 0xc4, 0xaf, 0x9e, 0xc0, 0xd2, 0xaf, 
	0x7c, 0xa2, 0xc2, 0xaf, 0x7e, 0xa6, 0xc4, 0xaf, 
	0x7c, 0x9c, 0xbe, 0xaf, 0xa4, 0xc4, 0xe0, 0xaf, 
	0xc0, 0xd8, 0xf0, 0xaf, 0x7c, 0x9a, 0xba, 0xaf, 
	0x6c, 0x8c, 0xac, 0xaf, 0x60, 0x80, 0xa0, 0xaf, 
	0x5c, 0x84, 0xa0, 0xaf, 0x7a, 0x9c, 0xb4, 0xaf, 
	0xc8, 0xe0, 0xf0, 0xaf, 0x68, 0x90, 0xa8, 0xaf, 
	0x62, 0x8a, 0xaa, 0xaf, 0x74, 0x98, 0xb8, 0xaf, 
	0x74, 0xa0, 0xbc, 0xaf, 0x7c, 0xa4, 0xc0, 0xaf, 
	0xdc, 0xec, 0xf4, 0xaf, 0xb8, 0xd2, 0xea, 0xaf, 
	0xb2, 0xca, 0xda, 0xaf, 0xb6, 0xce, 0xde, 0xaf, 
	0xcc, 0xde, 0xee, 0xaf, 0xd0, 0xe0, 0xf0, 0xaf, 
	0xc4, 0xdc, 0xec, 0xaf, 0xc8, 0xe0, 0xf0, 0xaf, 
	0xc2, 0xda, 0xec, 0xaf, 0xc2, 0xda, 0xec, 0xaf, 
	0xc0, 0xe0, 0xf0, 0xaf, 0x7e, 0xa6, 0xbc, 0xaf, 
	0x94, 0xbc, 0xce, 0xaf, 0x94, 0xbc, 0xce, 0xaf, 
	0x7c, 0xa0, 0xb8, 0xaf, 0x82, 0xa6, 0xbe, 0xaf, 
	0x82, 0xaa, 0xc2, 0xaf, 0x7c, 0xa4, 0xc0, 0xaf, 
	0x7c, 0x9c, 0xbc, 0xaf, 0xa8, 0xd0, 0xe8, 0xaf, 
	0xb4, 0xd6, 0xe6, 0xaf, 0x5a, 0x80, 0xa0, 0xaf, 
	0x70, 0xa0, 0xc0, 0xaf, 0x66, 0x8e, 0xae, 0xaf, 
	0x60, 0x80, 0xa8, 0xaf, 0x7c, 0x9c, 0xba, 0xaf, 
	0x9e, 0xbc, 0xd0, 0xaf, 0x7e, 0xa2, 0xb8, 0xaf, 
	0x6a, 0x90, 0xb0, 0xaf, 0x68, 0x8e, 0xae, 0xaf, 
	0x6e, 0x9c, 0xba, 0xaf, 0x8c, 0xb0, 0xc8, 0xaf, 
	0xbe, 0xd6, 0xea, 0xaf, 0xbe, 0xd6, 0xea, 0xaf, 
	0xac, 0xc8, 0xdc, 0xaf, 0xc2, 0xd6, 0xe2, 0xaf, 
	0xd0, 0xe0, 0xf0, 0xaf, 0xb8, 0xd4, 0xe8, 0xaf, 
	0xb0, 0xc8, 0xde, 0xaf, 0xcc, 0xe4, 0xf4, 0xaf, 
	0x9c, 0xba, 0xd6, 0xaf, 0xb0, 0xc8, 0xe0, 0xaf, 
	0xb8, 0xda, 0xea, 0xaf, 0x8e, 0xb6, 0xc8, 0xaf, 
	0xb4, 0xdc, 0xe8, 0xaf, 0xa8, 0xd0, 0xe0, 0xaf, 
	0x84, 0xa8, 0xc0, 0xaf, 0x7c, 0xa0, 0xb8, 0xaf, 
	0x82, 0xaa, 0xc2, 0xaf, 0x80, 0xa8, 0xc0, 0xaf, 
	0x7c, 0x9c, 0xbc, 0xaf, 0xa4, 0xca, 0xe4, 0xaf, 
	0x96, 0xba, 0xce, 0xaf, 0x78, 0x98, 0xb8, 0xaf, 
	0x70, 0xa0, 0xc0, 0xaf, 0x6e, 0x9c, 0xbc, 0xaf, 
	0x70, 0x90, 0xb2, 0xaf, 0x78, 0x98, 0xb8, 0xaf, 
	0x78, 0x98, 0xb8, 0xaf, 0x6c, 0x90, 0xb0, 0xaf, 
	0x74, 0x9c, 0xbc, 0xaf, 0x6c, 0x92, 0xb2, 0xaf, 
	0x70, 0x98, 0xb8, 0xaf, 0x86, 0xaa, 0xc2, 0xaf, 
	0x9c, 0xc0, 0xde, 0xaf, 0xc0, 0xe0, 0xf8, 0xaf, 
	0xac, 0xc8, 0xdc, 0xaf, 0xc4, 0xd8, 0xe8, 0xaf, 
	0xc8, 0xe0, 0xf0, 0xaf, 0xaa, 0xca, 0xe2, 0xaf, 
	0xb4, 0xce, 0xe6, 0xaf, 0xa6, 0xc2, 0xda, 0xaf, 
	0x94, 0xb4, 0xd2, 0xaf, 0xb4, 0xd4, 0xec, 0xaf, 
	0xa8, 0xce, 0xe6, 0xaf, 0xa4, 0xc8, 0xe0, 0xaf, 
	0xc8, 0xe8, 0xf4, 0xaf, 0xb6, 0xd6, 0xea, 0xaf, 
	0xa6, 0xc4, 0xd6, 0xaf, 0x80, 0xa8, 0xc0, 0xaf, 
	0x84, 0xaa, 0xc2, 0xaf, 0x84, 0xaa, 0xc2, 0xaf, 
	0x74, 0x9c, 0xba, 0xaf, 0x8e, 0xb6, 0xcc, 0xaf, 
	0x90, 0xb0, 0xd0, 0xaf, 0x88, 0xa8, 0xc8, 0xaf, 
	0x90, 0xb2, 0xce, 0xaf, 0x88, 0xac, 0xcc, 0xaf, 
	0x84, 0xa4, 0xc0, 0xaf, 0x6a, 0x8a, 0xae, 0xaf, 
	0x66, 0x8a, 0xaa, 0xaf, 0x58, 0x80, 0xa0, 0xaf, 
	0x62, 0x82, 0xa2, 0xaf, 0x6e, 0x94, 0xb4, 0xaf, 
	0x7a, 0xa0, 0xbc, 0xaf, 0x82, 0xa4, 0xc0, 0xaf, 
	0xa4, 0xc6, 0xe4, 0xaf, 0xb4, 0xd4, 0xf0, 0xaf, 
	0xbe, 0xd4, 0xe4, 0xaf, 0xd0, 0xe0, 0xf0, 0xaf, 
	0xcc, 0xe4, 0xf4, 0xaf, 0xc4, 0xdc, 0xec, 0xaf, 
	0xac, 0xc8, 0xe0, 0xaf, 0x96, 0xb6, 0xce, 0xaf, 
	0xb4, 0xd4, 0xec, 0xaf, 0xb4, 0xd4, 0xec, 0xaf, 
	0xa2, 0xc4, 0xdc, 0xaf, 0xaa, 0xd0, 0xe8, 0xaf, 
	0xcc, 0xec, 0xf6, 0xaf, 0xc0, 0xe0, 0xf0, 0xaf, 
	0xba, 0xd2, 0xe4, 0xaf, 0x9e, 0xba, 0xd2, 0xaf, 
	0x94, 0xb8, 0xcc, 0xaf, 0x70, 0x98, 0xb8, 0xaf, 
	0x74, 0x9c, 0xba, 0xaf, 0x80, 0xa8, 0xc2, 0xaf, 
	0x74, 0x94, 0xb8, 0xaf, 0x86, 0xa6, 0xc8, 0xaf, 
	0x98, 0xb8, 0xd0, 0xaf, 0xaa, 0xc4, 0xdc, 0xaf, 
	0x90, 0xb0, 0xc8, 0xaf, 0x7c, 0x9c, 0xba, 0xaf, 
	
};

Vtx frost_spire_ice_mesh_vtx_0[78] = {
	{{{162, -1000, -94},0, {671, 1894},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{162, -750, -94},0, {892, 1169},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{162, -750, 94},0, {646, 1042},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{162, -1000, 94},0, {344, 1725},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, -1000, 188},0, {-21, 2032},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{0, -750, 188},0, {27, 1273},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{-162, -750, 94},0, {-492, 1169},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{-162, -1000, 94},0, {-712, 1894},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{-162, -1000, -94},0, {1727, 2000},{0xC0, 0x0, 0x92, 0xFF}}},
	{{{-162, -750, -94},0, {1684, 1249},{0xC0, 0x0, 0x92, 0xFF}}},
	{{{0, -750, -187},0, {1411, 1273},{0xC0, 0x0, 0x92, 0xFF}}},
	{{{0, -1000, -187},0, {1363, 2032},{0xC0, 0x0, 0x92, 0xFF}}},
	{{{0, -1000, -187},0, {1363, 2032},{0x3F, 0x0, 0x92, 0xFF}}},
	{{{0, -750, -187},0, {1411, 1273},{0x3F, 0x0, 0x92, 0xFF}}},
	{{{162, -750, -94},0, {892, 1169},{0x3F, 0x0, 0x92, 0xFF}}},
	{{{162, -1000, -94},0, {671, 1894},{0x3F, 0x0, 0x92, 0xFF}}},
	{{{162, -1000, 94},0, {344, 2000},{0x40, 0x0, 0x6E, 0xFF}}},
	{{{162, -750, 94},0, {300, 1249},{0x40, 0x0, 0x6E, 0xFF}}},
	{{{0, -750, 188},0, {27, 1273},{0x40, 0x0, 0x6E, 0xFF}}},
	{{{0, -1000, 188},0, {-21, 2032},{0x40, 0x0, 0x6E, 0xFF}}},
	{{{-162, -1000, 94},0, {-712, 1894},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-162, -750, 94},0, {-492, 1169},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-162, -750, -94},0, {-737, 1042},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-162, -1000, -94},0, {-1040, 1725},{0x81, 0x0, 0x0, 0xFF}}},
	{{{108, -500, -62},0, {1113, 444},{0x7E, 0xD, 0x0, 0xFF}}},
	{{{54, 0, -31},0, {1463, -998},{0x7E, 0xD, 0x0, 0xFF}}},
	{{{54, 0, 31},0, {1381, -1040},{0x7E, 0xD, 0x0, 0xFF}}},
	{{{108, -500, 63},0, {949, 360},{0x7E, 0xD, 0x0, 0xFF}}},
	{{{0, -500, 125},0, {75, 513},{0xC1, 0xD, 0x6E, 0xFF}}},
	{{{0, 0, 63},0, {253, -963},{0xC1, 0xD, 0x6E, 0xFF}}},
	{{{-54, 0, 31},0, {80, -998},{0xC1, 0xD, 0x6E, 0xFF}}},
	{{{-108, -500, 63},0, {-271, 444},{0xC1, 0xD, 0x6E, 0xFF}}},
	{{{-108, -500, -62},0, {1641, 497},{0xC1, 0xD, 0x92, 0xFF}}},
	{{{-54, 0, -31},0, {1727, -971},{0xC1, 0xD, 0x92, 0xFF}}},
	{{{0, 0, -62},0, {1636, -963},{0xC1, 0xD, 0x92, 0xFF}}},
	{{{0, -500, -125},0, {1459, 513},{0xC1, 0xD, 0x92, 0xFF}}},
	{{{0, -500, -125},0, {1459, 513},{0x3F, 0xD, 0x92, 0xFF}}},
	{{{0, 0, -62},0, {1636, -963},{0x3F, 0xD, 0x92, 0xFF}}},
	{{{54, 0, -31},0, {1463, -998},{0x3F, 0xD, 0x92, 0xFF}}},
	{{{108, -500, -62},0, {1113, 444},{0x3F, 0xD, 0x92, 0xFF}}},
	{{{108, -500, 63},0, {257, 497},{0x3F, 0xD, 0x6E, 0xFF}}},
	{{{54, 0, 31},0, {344, -971},{0x3F, 0xD, 0x6E, 0xFF}}},
	{{{0, 0, 63},0, {253, -963},{0x3F, 0xD, 0x6E, 0xFF}}},
	{{{0, -500, 125},0, {75, 513},{0x3F, 0xD, 0x6E, 0xFF}}},
	{{{-108, -500, 63},0, {-271, 444},{0x82, 0xD, 0x0, 0xFF}}},
	{{{-54, 0, 31},0, {80, -998},{0x82, 0xD, 0x0, 0xFF}}},
	{{{-54, 0, -31},0, {-2, -1040},{0x82, 0xD, 0x0, 0xFF}}},
	{{{-108, -500, -62},0, {-435, 360},{0x82, 0xD, 0x0, 0xFF}}},
	{{{0, 0, -62},0, {1727, 1940},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-54, 0, -31},0, {1880, 2032},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-54, 0, 31},0, {2032, 1940},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{54, 0, 31},0, {1880, 1662},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, 0, 63},0, {2032, 1755},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{54, 0, -31},0, {1727, 1755},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{162, -750, -94},0, {892, 1169},{0x3E, 0x1B, 0x94, 0xFF}}},
	{{{0, -750, -187},0, {1411, 1273},{0x3E, 0x1B, 0x94, 0xFF}}},
	{{{0, -500, -125},0, {1459, 513},{0x3E, 0x1B, 0x94, 0xFF}}},
	{{{108, -500, -62},0, {1113, 444},{0x3E, 0x1B, 0x94, 0xFF}}},
	{{{162, -750, 94},0, {646, 1042},{0x7C, 0x1B, 0x0, 0xFF}}},
	{{{162, -750, -94},0, {892, 1169},{0x7C, 0x1B, 0x0, 0xFF}}},
	{{{108, -500, -62},0, {1113, 444},{0x7C, 0x1B, 0x0, 0xFF}}},
	{{{108, -500, 63},0, {949, 360},{0x7C, 0x1B, 0x0, 0xFF}}},
	{{{0, -750, 188},0, {27, 1273},{0x3E, 0x1B, 0x6C, 0xFF}}},
	{{{162, -750, 94},0, {300, 1249},{0x3E, 0x1B, 0x6C, 0xFF}}},
	{{{108, -500, 63},0, {257, 497},{0x3E, 0x1B, 0x6C, 0xFF}}},
	{{{0, -500, 125},0, {75, 513},{0x3E, 0x1B, 0x6C, 0xFF}}},
	{{{-162, -750, 94},0, {-492, 1169},{0xC2, 0x1B, 0x6C, 0xFF}}},
	{{{0, -750, 188},0, {27, 1273},{0xC2, 0x1B, 0x6C, 0xFF}}},
	{{{0, -500, 125},0, {75, 513},{0xC2, 0x1B, 0x6C, 0xFF}}},
	{{{-108, -500, 63},0, {-271, 444},{0xC2, 0x1B, 0x6C, 0xFF}}},
	{{{-162, -750, -94},0, {-737, 1042},{0x84, 0x1B, 0x0, 0xFF}}},
	{{{-162, -750, 94},0, {-492, 1169},{0x84, 0x1B, 0x0, 0xFF}}},
	{{{-108, -500, 63},0, {-271, 444},{0x84, 0x1B, 0x0, 0xFF}}},
	{{{-108, -500, -62},0, {-435, 360},{0x84, 0x1B, 0x0, 0xFF}}},
	{{{0, -750, -187},0, {1411, 1273},{0xC2, 0x1B, 0x94, 0xFF}}},
	{{{-162, -750, -94},0, {1684, 1249},{0xC2, 0x1B, 0x94, 0xFF}}},
	{{{-108, -500, -62},0, {1641, 497},{0xC2, 0x1B, 0x94, 0xFF}}},
	{{{0, -500, -125},0, {1459, 513},{0xC2, 0x1B, 0x94, 0xFF}}},
};

Gfx frost_spire_ice_mesh_tri_0[] = {
	gsSPVertex(frost_spire_ice_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(frost_spire_ice_mesh_vtx_0 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(frost_spire_ice_mesh_vtx_0 + 32, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(frost_spire_ice_mesh_vtx_0 + 48, 14, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(2, 3, 0, 0),
	gsSP1Triangle(2, 4, 3, 0),
	gsSP1Triangle(3, 5, 0, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(10, 12, 13, 0),
	gsSPVertex(frost_spire_ice_mesh_vtx_0 + 62, 16, 0),
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


Gfx mat_frost_spire_ice[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, frost_spire_transice_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 124, 124),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(frost_spire_ice_lights),
	gsSPEndDisplayList(),
};

Gfx frost_spire_ice_mesh[] = {
	gsSPDisplayList(mat_frost_spire_ice),
	gsSPDisplayList(frost_spire_ice_mesh_tri_0),
	gsSPEndDisplayList(),
};

Gfx frost_spire_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};
