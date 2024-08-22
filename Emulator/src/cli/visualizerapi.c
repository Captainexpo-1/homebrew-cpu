#include "visualizerapi.h"


/*typedef struct returnInstructionString {
    int after_address;
    const char *str;
} returnInstructionString;

returnInstructionString* get_instruction_representation(Emulator *emu, int init_address) {
    byte opcode = get_value_in_rom(emu, init_address);
    Instruction *instr = get_instruction(emu, opcode);
    if (!instr) {
        returnInstructionString *ris = malloc(sizeof(returnInstructionString));
        ris->str = strdup("Unknown");
        ris->after_address = init_address + 1;
        return ris;
    }
    
    char *str = malloc(100);
    if (!str) {
        printf("Error allocating memory for instruction representation\n");
        return NULL;
    }
    
    int arg_count = instr->argc;
    byte *args = malloc(sizeof(byte) * arg_count);
    if (!args) {
        printf("Error allocating memory for instruction arguments\n");
        free(str);
        return NULL;
    }
    
    for (int i = 0; i < arg_count; i++) {
        args[i] = get_value_in_rom(emu, init_address + 1 + i);
    }

    switch (arg_count) {
        case 0:
            sprintf(str, "%s", instr->mnemonic);
            break;
        case 1:
            sprintf(str, "%s 0x%02x", instr->mnemonic, args[0]);
            break;
        case 2:
            sprintf(str, "%s 0x%02x 0x%02x", instr->mnemonic, args[0], args[1]);
            break;
        default:
            sprintf(str, "%s", instr->mnemonic);
            break;
    }

    free(args);

    returnInstructionString *ris = malloc(sizeof(returnInstructionString));
    ris->str = str;
    ris->after_address = init_address + arg_count + 1;

    return ris;
}*/

const char* get_memory_value_str(Emulator *emu, byte address) {
    byte val = get_value_in_memory(emu, address);
    char *str = malloc(10);
    if (!str) {
        printf("Error allocating memory for memory value string\n");
        return NULL;
    }
    sprintf(str, "[%02x] 0x%02x", address, val);
    return str;
}

const char* get_rom_value_str(Emulator *emu, byte address) {
    byte val = get_value_in_rom(emu, address);
    char *str = malloc(10);
    if (!str) {
        printf("Error allocating memory for rom value string\n");
        return NULL;
    }
    sprintf(str, "[%02x] 0x%02x", address, val);
    return str;
}
void output_state(Emulator *emu) {
    clear();
    printf("-------------------------\n");
    printf("|  AReg |  BReg | Flags |\n");
    printf("|-------|-------|-------|\n");
    printf("| 0x%02x  | 0x%02x  | 0x%02x  |\n", emu->r_A->value, emu->r_B->value, emu->r_Flags->value);
    printf("-------------------------\n\n");

    // Display Memory
    printf("Memory:\n");
    int last_non_zero = 0;
    for (int i = 0; i < emu->memory_size - 1; i++) {
        byte val = get_value_in_memory(emu, i);
        if (val != 0) {
            last_non_zero = i;
        }
    }
    for (int i = 0; i <= last_non_zero; i++) {
        if (i % 5 == 0 && i != 0) {
            printf("\n");
        }
        const char* mem_str = get_memory_value_str(emu, i);
        printf("%s ", mem_str);
        free((void*)mem_str); // Free the memory allocated for the memory value string
    }
    printf("\n\n");

    // Display Program ROM
    printf("Program ROM:\n");

    int pc = emu->r_PC->value;
    for (int i = max(0, pc-2); i < min(emu->program_size, pc+3); i++) {
        // Get the rom value at the current address 
        byte rom_val = get_value_in_rom(emu, i);
        const char* instr_str = get_rom_value_str(emu, i);
        char *line = malloc(100);
        if (!line) {
            printf("Error allocating memory for program line\n");
            return;
        }
        if (i == pc) {
            sprintf(line, "%s <--\n", instr_str);
        } else {
            sprintf(line, "%s\n", instr_str);
        }

        printf("%s", line);

        free((void*)instr_str); // Free the memory allocated for the memory value string
    }
    printf("Halted: %d\n", emu->halted);
    // Display Output
    printf("Output: ");
    str_vector_join_print(emu->output, " ");

    printf("\n-------------------------\n");


}
