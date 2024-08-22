#ifndef VISUALIZERAPI_H
#define VISUALIZERAPI_H

#include <stdio.h>
#include "printer.h"
#include "../emulator/emulator.h"
#include "../emulator/instructions.h"
#include "../emulator/instructionType.h"
#include "../emulator/emulatorMethods.h"
#include "../emulator/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Output should look like this

--------------------------
|  sAReg |  BReg |  Flags |
|-------|-------|--------|
|  0xFF |  0xFF |  0x00  |
--------------------------

Memory: [00] 0xFA [01] 0x01
        [02] 0xAA [03] 0x44
        //... up to the last non-zero memory address)
Program ROM:
0x00: lda_const 0xFA // Backwards 2
0x01: sav
0x02: lda_const 0x01 <-- // arrow pointing to the current instruction
0x03: sav
0x04: lda_const 0xAA // Forward 2

--------------------------
*/

typedef struct returnInstructionString returnInstructionString;
extern const char* get_rom_value_str(Emulator *emu, byte address);
extern const char* get_memory_value_str(Emulator *emu, byte address);
extern void output_state(Emulator *emu);


#endif