#ifndef INSTRUCTION_TYPE_H
#define INSTRUCTION_TYPE_H
#include <stdlib.h>
#include "emulator.h"

typedef struct {
    byte opcode;
    byte argc;
    void (*operation)(Emulator *emu, byte *args);
    const char *mnemonic;
} Instruction;


#endif