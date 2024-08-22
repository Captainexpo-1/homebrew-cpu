
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "emulator.h"
#include "emulatorMethods.h"
#include "alu.h"
#include <stdlib.h>

void lda( Emulator *emu, byte *args);
void ldb( Emulator *emu, byte *args);
void sta( Emulator *emu, byte *args);
void stb( Emulator *emu, byte *args);
void add( Emulator *emu, byte *args);
void sub( Emulator *emu, byte *args);
void jmp( Emulator *emu, byte *args);
void je( Emulator *emu, byte *args);
void jl( Emulator *emu, byte *args);
void jg( Emulator *emu, byte *args);
void nop( Emulator *emu, byte *args);
void halt( Emulator *emu, byte *args);
void sav( Emulator *emu, byte *args);
void cmp( Emulator *emu, byte *args);
void lda_const(Emulator *emu, byte *args);
void aout(Emulator *emu, byte *args);
#endif