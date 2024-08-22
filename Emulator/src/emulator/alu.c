#include "alu.h"

void alu_do_operation(Emulator *emu, byte fn_sel, byte data){
    // TODO: Use acual values from ALU function table
    byte alu_r_val = emu->r_ALUREG->value;
    byte o_val = 0;
    switch (fn_sel)
    {
    case 0b00000: // Addition
        o_val = alu_r_val + data;
        break;
    case 0b00001: // Subtraction
        o_val = alu_r_val - data;
        break;
    case 0b00010: // OR
        o_val = alu_r_val | data;
        break;
    case 0b00011: // AND
        o_val = alu_r_val & data;
        break;
    case 0b00100: // Zero
        break;
    case 0b00101: // One
        o_val = 1;
        break;
    case 0b00110: // Invert
        o_val = ~alu_r_val;
        break;
    case 0b00111: // A 
        o_val = emu->r_A->value;
        break;
    default:    
        printf("Error: Unknown alu function: %d\n", fn_sel);
        break;
    }
    set_dl(emu, emu->r_ALUOUT, o_val);
}