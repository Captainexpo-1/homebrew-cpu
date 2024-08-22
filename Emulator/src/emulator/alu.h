#ifndef ALU_H
#define ALU_H
#include "emulator.h"
#include "emulatorMethods.h"

void alu_do_operation(Emulator *emu, byte fn_sel, byte data);

#endif