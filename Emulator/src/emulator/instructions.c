#include "instructions.h"
#include "instructionType.h"


void sav(Emulator *emu, byte *args){
    mov_dl(emu, emu->r_A, emu->r_B);
	ic(emu,emu->r_PC);
}
void lda(Emulator *emu, byte *args){
    byte v = get_value_in_memory(emu, args[0]);
    set_dl(emu, emu->r_A, v);
	ic(emu,emu->r_PC);
}
void ldb(Emulator *emu, byte *args){
    byte v = get_value_in_memory(emu, args[0]);
    set_dl(emu, emu->r_B, v);
	ic(emu,emu->r_PC);
}
void sta(Emulator *emu, byte *args){
    set_value_in_memory(emu, args[0], emu->r_A->value);
	ic(emu,emu->r_PC);
}
void stb(Emulator *emu, byte *args){
    set_value_in_memory(emu, args[0], emu->r_B->value);
	ic(emu,emu->r_PC);
}
void add(Emulator *emu, byte *args){
    mov_dl(emu, emu->r_A, emu->r_ALUREG);
    alu_do_operation(emu, 0b00000, emu->r_B->value);
    mov_dl(emu, emu->r_ALUOUT, emu->r_A);
	ic(emu,emu->r_PC);
}
void sub(Emulator *emu, byte *args){
    mov_dl(emu, emu->r_A, emu->r_ALUREG);
    alu_do_operation(emu, 0b00001, emu->r_B->value);
    mov_dl(emu, emu->r_ALUOUT, emu->r_A);
	ic(emu,emu->r_PC);
}
void jmp(Emulator *emu, byte *args){
    set_dl(emu, emu->r_PC, args[0]);
}
void je(Emulator *emu, byte *args){
    if (((emu->r_Flags->value >> 1) & 1) != 0){
        set_dl(emu, emu->r_PC, args[0]);
        return;
    }
	ic(emu,emu->r_PC);
}
void jl(Emulator *emu, byte *args){
    if (((emu->r_Flags->value >> 2) & 1) != 0){
        set_dl(emu, emu->r_PC, args[0]);
        return;
    }
	ic(emu,emu->r_PC);
}
void jg(Emulator *emu, byte *args){
    if ((emu->r_Flags->value & 1) != 0){
        set_dl(emu, emu->r_PC, args[0]);
        return;
    }
	ic(emu,emu->r_PC);
}

void nop(Emulator *emu, byte *args){
	ic(emu,emu->r_PC);
}
void halt(Emulator *emu, byte *args){
    printf("Halting\n");
    emu->halted = true;
	ic(emu,emu->r_PC);
}
void cmp(Emulator *emu, byte *args){
    byte a = emu->r_A->value;
    byte b = emu->r_B->value;

    mov_dl(emu, emu->r_A, emu->r_ALUREG);
    alu_do_operation(emu, 0b00100, emu->r_B->value);
    byte flags = 0b001;
    if (a == b) flags = 0b010;
    if (a < b) flags = 0b100;
    set_dl(emu, emu->r_Flags, flags);
    //printf("Comparing %d and %d, flags: %d\n", a, b, flags);
	ic(emu,emu->r_PC);
}
void lda_const(Emulator *emu, byte *args){
    set_dl(emu, emu->r_A, args[0]);
	ic(emu,emu->r_PC);
}
void aout(Emulator *emu, byte *args){
    if (emu == NULL || emu->r_A == NULL || emu->output == NULL) {
        fprintf(stderr, "Null pointer error in aout function\n");
        return;
    }
    char* buf = malloc(10);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed in aout function\n");
        return;
    }
    sprintf(buf, "%d", emu->r_A->value);
    str_vector_append(emu->output, buf);
    free(buf);
	ic(emu,emu->r_PC);
}