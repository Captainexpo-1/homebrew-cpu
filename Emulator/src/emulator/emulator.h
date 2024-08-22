#ifndef EMULATOR_H
#define EMULATOR_H
#include <stdbool.h>
#include "utils.h"
void panic(const char *message);
// Forward declaration
typedef struct Emulator Emulator;

typedef struct {
    byte value;
    bool is_register; 
} DataLocation;
typedef struct Emulator{
    byte *memory;
    byte *program_rom;
    uint32_t memory_size;
    uint32_t program_size;
    DataLocation* r_A;
    DataLocation* r_B;
    DataLocation* r_Flags;
    DataLocation* r_PC;
    DataLocation* r_TR;
    DataLocation* r_ALUREG;
    DataLocation* r_ALUOUT;
    StrVector* output;
    bool halted;
} Emulator;

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../cli/visualizerapi.h"
#endif