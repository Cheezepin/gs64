/**
 * Behavior for bhvActivatedBackAndForthPlatform.
 * There are only 2 of these in the game; the BitFS gray elevator
 * and the BitS arrow platform.
 * Note: The filename is abbreviated to avoid compiler seg fault on long paths
 */

/**
 * Table of activated back-and-forth platform collision models.
 * The second entry is unused. It corresponds to the mesh platform
 * at the beginning of BitFS. In the game, it's a bhvPlatformOnTrack,
 * which allows for more complex movement; its path is mostly a straight line
 * except for where it dips into the lava. It seems the programmers
 * had it as a bhvActivatedBackAndForthPlatform initially, which moves
 * in a straight line, and wanted it to dip into the lava to make Mario have to
 * move off of it. To do this, they changed it to a bhvPlatformOnTrack, but
 * forgot to remove its entry in this table.
 */
static void const *sActivatedBackAndForthPlatformCollisionModels[] = {
    /* ACTIVATED_BF_PLAT_TYPE_BITS_ARROW_PLAT */ bits_seg7_collision_0701AD54,
    /* ACTIVATED_BF_PLAT_TYPE_BITFS_MESH_PLAT */ bitfs_seg7_collision_070157E0,
    /* ACTIVATED_BF_PLAT_TYPE_BITFS_ELEVATOR  */ bitfs_seg7_collision_07015124
};

/**
 * Activated back-and-forth platform initialization function.
 */
void bhv_activated_back_and_forth_platform_init(void) {

}

/**
 * Activated back-and-forth platform update function.
 */
void bhv_activated_back_and_forth_platform_update(void) {
    
}
