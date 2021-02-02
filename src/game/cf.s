# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64

.include "macros.inc"

.section .text, "ax"

/* get_count_factor
Returns 0 if the ROM is being played on console.
Returns 1 if the ROM is being played on emulator with good settings.
Returns 2 or higher if the ROM is being played on emulator with bad settings.
*/

glabel get_count_factor

get_count_factor:
MFC0 $t0, $9
NOP
MFC0 $t1, $9
NOP
SUBU $at, $t1, $t0
JR $ra
SRL $v0, $at, 1