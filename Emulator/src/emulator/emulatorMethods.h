#ifndef EMULATOR_METHODS_H
#define EMULATOR_METHODS_H

// Forward declarations
typedef struct Emulator Emulator;

#include "emulator.h"
#include "instructionType.h"
#include "instructions.h"


Emulator* create_emulator(Emulator *self, byte *buffer, long file_size);
void destroy_emulator(Emulator* self);
void run(Emulator* self);
Instruction* get_instruction(Emulator* self, byte opcode, bool ignore_halt);
void output(Emulator* self);
byte get_value_in_memory(Emulator* self, byte address);
void set_value_in_memory(Emulator* self, byte address, byte value);
void mov_dl(Emulator *self, DataLocation *src, DataLocation *dest);
void set_dl(Emulator *self, DataLocation *dl, byte val);
void ic(Emulator *self, DataLocation *counter);
byte get_value_in_rom(Emulator *self, byte address);

extern Instruction instructions[];

#endif