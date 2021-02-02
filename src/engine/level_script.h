#ifndef LEVEL_SCRIPT_H
#define LEVEL_SCRIPT_H

#include <PR/ultratypes.h>

struct LevelCommand;

extern u8 level_script_entry[];
extern u8 level_script_entry_error_screen[];

struct LevelCommand *level_script_execute(struct LevelCommand *cmd);

extern s32 determine_starting_level(void);

#endif // LEVEL_SCRIPT_H
