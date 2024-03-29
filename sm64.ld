OUTPUT_ARCH (mips)

#define LINKER /* Removes externs from preprocessed script */
#include "segments.h"
#undef LINKER

#define BEGIN_SEG(name, addr) \
    _##name##SegmentStart = ADDR(.name); \
    _##name##SegmentRomStart = __romPos; \
    .name addr : AT(__romPos)

#define END_SEG(name) \
    _##name##SegmentEnd = ADDR(.name) + SIZEOF(.name); \
    _##name##SegmentRomEnd = __romPos + SIZEOF(.name); \
    __romPos += SIZEOF(.name);

#define BEGIN_NOLOAD(name) \
    _##name##SegmentNoloadStart = ADDR(.name.noload); \
    .name.noload (NOLOAD) :

#define END_NOLOAD(name) \
    _##name##SegmentNoloadEnd = ADDR(.name.noload) + SIZEOF(.name.noload);

#define YAY0_SEG(name, segAddr) \
   BEGIN_SEG(name##_yay0, segAddr) \
   { \
      BUILD_DIR/bin/name.szp.o(.data); \
      . = ALIGN(0x10); \
   } \
   END_SEG(name##_yay0)

#define YAY0_EU_SEG(name, segAddr) \
   BEGIN_SEG(name##_yay0, segAddr) \
   { \
      BUILD_DIR/bin/eu/name.szp.o(.data); \
      . = ALIGN(0x10); \
   } \
   END_SEG(name##_yay0)

#define STANDARD_LEVEL(name) \
   BEGIN_SEG(name##_segment_7, 0x07000000) \
   { \
      BUILD_DIR/levels/name/leveldata.szp.o(.data); \
      . = ALIGN(0x10); \
   } \
   END_SEG(name##_segment_7) \
   BEGIN_SEG(name, 0x0E000000) \
   { \
      BUILD_DIR/levels/name/script.o(.data); \
      BUILD_DIR/levels/name/geo.o(.data); \
   } \
   END_SEG(name)

#define STANDARD_OBJECTS(name, segAddr, geoAddr) \
   BEGIN_SEG(name##_yay0, segAddr) \
   { \
      BUILD_DIR/actors/name.szp.o(.data); \
      . = ALIGN(0x10); \
   } \
   END_SEG(name##_yay0) \
   BEGIN_SEG(name##_geo, geoAddr) \
   { \
      BUILD_DIR/actors/name##_geo.o(.data); \
   } \
   END_SEG(name##_geo)

SECTIONS
{
   __romPos = 0;

   BEGIN_SEG(boot, 0x04000000)
   {
      BUILD_DIR/asm/rom_header.o(.text);
      BUILD_DIR/asm/boot.o(.text);
   }
   END_SEG(boot)

   . = 0x80000400;
   BEGIN_NOLOAD(zbuffer) {
      BUILD_DIR/src/buffers/zbuffer.o(.bss*);
   }
   END_NOLOAD(zbuffer)

   . = _zbufferSegmentNoloadEnd;
   BEGIN_NOLOAD(buffers)
   {
      BUILD_DIR/src/buffers/buffers.o(.bss*);
      BUILD_DIR/src/audio/globals_start.o(.bss*);
      BUILD_DIR/src/audio/synthesis.o(.bss*);
      BUILD_DIR/src/audio/heap.o(.bss*);
      BUILD_DIR/src/audio/load.o(.bss*);
      BUILD_DIR/src/audio/data.o(.bss*);
      BUILD_DIR/src/audio*.o(.bss*);

#ifdef VERSION_EU
      . = ALIGN(0x200);
#else
      . = ALIGN(0x1000);
#endif
      BUILD_DIR/src/buffers/gfx_output_buffer.o(.bss*);
   }
   END_NOLOAD(buffers)

   /*ASSERT((. <= SEG_MAIN), "Error: buffers segment extended into main")*/

   . = _buffersSegmentNoloadEnd;
   /* lib/src/__osDevMgrMain.c and lib/src/osCreateViManager.c contain infinite
    * loops compiled without -g, which cause the return statements and the .o
    * files themselves to be aligned to 32-byte boundaries. But the linker
    * Nintendo used did not respect .o file alignment, and aligned the files
    * only to 16 bytes, in some cases misaligning them. We force the same to
    * happen using the SUBALIGN directive. This is harmless; the alignment is
    * just an optimization. */
   BEGIN_SEG(main, .) SUBALIGN(16)
   {
      BUILD_DIR/asm/entry.o(.text);

      BUILD_DIR/src/game*.o(.text);
      BUILD_DIR/src/s2d_engine*.o(.text);
#ifdef UNF
      BUILD_DIR/src/usb*.o(.text);
#endif
      BUILD_DIR/src/audio*.o(.text);
      BUILD_DIR/asm/llmuldiv_gcc.o(.text);
      BUILD_DIR/asm/slidec.o(.text);

      */libultra_rom.a:*.o(.text);
      */libhvqm2.a:*.o(.text);

      BUILD_DIR/lib/rsp.o(.text);   
      lib/PR/hvqm/hvqm2sp1.o(.text);

      /* data */
      BUILD_DIR/src/game*.o(.data*);
      BUILD_DIR/src/game*.o(.sdata*);
      BUILD_DIR/src/s2d_engine*.o(.data*);
      BUILD_DIR/src/s2d_engine*.o(.sdata*);
#ifdef UNF
      BUILD_DIR/src/usb*.o(.data*);
      BUILD_DIR/src/usb*.o(.sdata*);
#endif
      BUILD_DIR/src/audio*.o(.data*);
      BUILD_DIR/src/audio*.o(.sdata*);

      */libultra_rom.a:*.o(.data*);
      */libultra_rom.a:*.o(.sdata*);
      */libhvqm2.a:*.o(.data*);

      BUILD_DIR/lib/rsp.o(.data*);
      lib/PR/hvqm/hvqm2sp1.o(.data*);

      /* rodata */
      BUILD_DIR/src/game*.o(.rodata*);
      BUILD_DIR/src/s2d_engine*.o(.rodata*);
#ifdef UNF
      BUILD_DIR/src/usb*.o(.rodata*);
#endif
      BUILD_DIR/src/audio*.o(.rodata*);

      */libultra_rom.a:*.o(.rodata*);
      */libhvqm2.a:*.o(.rodata*);

      BUILD_DIR/lib/rsp.o(.rodata*);
      lib/PR/hvqm/hvqm2sp1.o(.rodata*);
   }
   END_SEG(main)
   BEGIN_NOLOAD(main)
   {
      BUILD_DIR/src/game*.o(.bss*);
      BUILD_DIR/src/game*.o(.sbss*);
      BUILD_DIR/src/s2d_engine*.o(.bss*);
      BUILD_DIR/src/s2d_engine*.o(.sbss*);
      BUILD_DIR/src/usb*.o(.bss*);
      BUILD_DIR/src/usb*.o(.sbss*);
      BUILD_DIR/src/audio*.o(.bss*);
      BUILD_DIR/src/audio*.o(.sbss*);
      
      */libultra_rom.a:*.o(.bss*);
      */libultra_rom.a:*.o(.sbss*);
      */libhvqm2.a:*.o(.bss*);

      . = ALIGN(0x8);
   }
   END_NOLOAD(main)
   _mainSegmentNoloadSizeLo = SIZEOF (.main.noload) & 0xffff;
   _mainSegmentNoloadSizeHi = SIZEOF (.main.noload) >> 16;

   /*ASSERT((. <= SEG_ENGINE), "Error: main segment extended into engine.")*/

   . = _mainSegmentNoloadEnd;

   BEGIN_SEG(engine, .)
   {
      BUILD_DIR/src/engine*.o(.text);
      /* data */
      BUILD_DIR/src/engine*.o(.data*);
      BUILD_DIR/src/engine*.o(.sdata*);
      /* rodata */
      BUILD_DIR/src/engine*.o(.rodata*);
   }
   END_SEG(engine)
   BEGIN_NOLOAD(engine)
   {
      BUILD_DIR/src/engine*.o(.bss*);
      . = ALIGN(0x100);
   }
   END_NOLOAD(engine)

   /*ASSERT((. <= SEG_FRAMEBUFFERS), "Error: engine segment extended into framebuffers.")*/

   . = _engineSegmentNoloadEnd;
   BEGIN_NOLOAD(framebuffers)
   {
      BUILD_DIR/src/buffers/framebuffers.o(.bss*);
   }
   END_NOLOAD(framebuffers)

   __mainPoolStart = .;
   __mainPoolSize = RAM_END - .;

   __expansionRamStart = 0x80400000;
   ASSERT((. <= __expansionRamStart), "Error: RDRAM expanded into Expansion RAM, despite Expansion RAM not being defined.")


   BEGIN_SEG(entry, 0x10000000)
   {
      BUILD_DIR/levels/entry.o(.data);
   }
   END_SEG(entry)

   /* load YAY0 and level data */
   YAY0_SEG(segment2, 0x02000000)
#ifdef VERSION_EU
   YAY0_EU_SEG(translation_en, 0x19000000)
   YAY0_EU_SEG(translation_fr, 0x19000000)
   YAY0_EU_SEG(translation_de, 0x19000000)
#endif

   /* mario actor group */
   STANDARD_OBJECTS(group0,  0x04000000, 0x17000000)

   /* load the other actor groups */
   STANDARD_OBJECTS(group1,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group2,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group3,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group4,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group5,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group6,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group7,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group8,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group9,  0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group10, 0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group11, 0x05000000, 0x0C000000)
   STANDARD_OBJECTS(group12, 0x06000000, 0x0D000000)
   STANDARD_OBJECTS(group13, 0x06000000, 0x0D000000)
   STANDARD_OBJECTS(group14, 0x06000000, 0x0D000000)
   STANDARD_OBJECTS(group15, 0x06000000, 0x0D000000)
   STANDARD_OBJECTS(group16, 0x06000000, 0x0D000000)
   STANDARD_OBJECTS(group17, 0x06000000, 0x0D000000)

   /* load the common actor groups */
   STANDARD_OBJECTS(common0, 0x08000000, 0x0F000000)
   STANDARD_OBJECTS(common1, 0x03000000, 0x16000000)

   /* use segmented addressing for behaviors */
   BEGIN_SEG(behavior, 0x13000000)
   {
      BUILD_DIR/data/behavior_data.o(.data);
   }
   END_SEG(behavior)

   /* 0x8016F000 21D7D0-255EC0 [386F0] */
   BEGIN_SEG(goddard, SEG_GODDARD)
   {
      BUILD_DIR/src/menu*.o(.text);
      BUILD_DIR/src/menu*.o(.data*);
      BUILD_DIR/src/menu*.o(.rodata*);
   }
   END_SEG(goddard)
   BEGIN_NOLOAD(goddard)
   {
      BUILD_DIR/src/menu*.o(.bss*);
   }
   END_NOLOAD(goddard)

   ASSERT((. <= (SEG_POOL_START + POOL_SIZE)), "Error: extended past pool end.")


   /* 0x268020 0x268020-0 [0] */
   BEGIN_SEG(intro, 0x14000000)
   {
      BUILD_DIR/levels/intro/script.o(.data);
      BUILD_DIR/levels/intro/geo.o(.data);
   }
   END_SEG(intro)
   BEGIN_SEG(intro_segment_7, 0x07000000)
   {
      BUILD_DIR/levels/intro/leveldata.szp.o(.data);
      . = ALIGN(0x10);
   }
   END_SEG(intro_segment_7)

   YAY0_SEG(debug_level_select, 0x07000000)
   YAY0_SEG(title_screen_bg, 0x0A000000)

   gMainLevels = __romPos;

   BEGIN_SEG(menu, 0x14000000)
   {
      BUILD_DIR/levels/menu/script.o(.data);
      BUILD_DIR/levels/menu/geo.o(.data);
   }
   END_SEG(menu)
   BEGIN_SEG(menu_segment_7, 0x07000000)
   {
      BUILD_DIR/levels/menu/leveldata.szp.o(.data);
      . = ALIGN(0x10);
   }
   END_SEG(menu_segment_7)

   BEGIN_SEG(scripts, 0x15000000)
   {
      BUILD_DIR/levels/scripts.o(.data);
   }
   END_SEG(scripts)

   YAY0_SEG(water_skybox, 0x0A000000)
   YAY0_SEG(ccm_skybox, 0x0A000000)
   YAY0_SEG(clouds_skybox, 0x0A000000)
   YAY0_SEG(bitfs_skybox, 0x0A000000)
   YAY0_SEG(wdw_skybox, 0x0A000000)
   YAY0_SEG(cloud_floor_skybox, 0x0A000000)
   YAY0_SEG(ssl_skybox, 0x0A000000)
   YAY0_SEG(bbh_skybox, 0x0A000000)
   YAY0_SEG(bidw_skybox, 0x0A000000)
   YAY0_SEG(bits_skybox, 0x0A000000)

   // Texture bins
   YAY0_SEG(fire, 0x09000000)
   YAY0_SEG(spooky, 0x09000000)
   YAY0_SEG(generic, 0x09000000)
   YAY0_SEG(water, 0x09000000)
   YAY0_SEG(sky, 0x09000000)
   YAY0_SEG(snow, 0x09000000)
   YAY0_SEG(cave, 0x09000000)
   YAY0_SEG(machine, 0x09000000)
   YAY0_SEG(mountain, 0x09000000)
   YAY0_SEG(grass, 0x09000000)
   YAY0_SEG(outside, 0x09000000)
   YAY0_SEG(inside, 0x09000000)
   YAY0_SEG(effect, 0x0B000000)

#define STUB_LEVEL(_0, _1, _2, _3, _4, _5, _6, _7, _8)
#define DEFINE_LEVEL(_0, _1, _2, folder, _4, _5, _6, _7, _8, _9, _10) STANDARD_LEVEL(folder)

   #include "levels/level_defines.h"

#undef STUB_LEVEL
#undef DEFINE_LEVEL

   /* 4E9FA0-? [?] */
   BEGIN_SEG(assets, __romPos)
   {
      BUILD_DIR/assets/mario_anim_data.o(.data);
      BUILD_DIR/assets/mario_anim_data.o(.rodata);
      BUILD_DIR/assets/demo_data.o(.data);
      BUILD_DIR/sound/sound_data.o(.data);
   }
   END_SEG(assets)
  
   BEGIN_SEG(capcom, __romPos) SUBALIGN(2)
   {
      BUILD_DIR/data/capcom.o(.data);
   }
	END_SEG(capcom)
#if 0
   BEGIN_SEG(sein, __romPos) SUBALIGN(2)
   {
      BUILD_DIR/data/sein.o(.data);
   }
	END_SEG(sein)
#endif
   /* Discard everything not specifically mentioned above. */
   /DISCARD/ :
   {
      *(*);
   }
}
