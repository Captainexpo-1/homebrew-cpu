#include "emulator.h"
#include "emulatorMethods.h"

void panic(const char *message)
{
    printf("Panic: %s\n", message);
    exit(1);
}

void print_memory(Emulator *self, int lim)
{
    for (int i = 0; i < lim; i++)
    {
        printf("0x%x: %d, ", i, self->memory[i]);
    }
    printf("\n");
}

void destroy_emulator(Emulator *self)
{
    free(self);
}

DataLocation* dl(){
    DataLocation* dl = malloc(sizeof(DataLocation));
    if (!dl){
        printf("Error allocating datalocation!\n");
        return NULL;
    }
    dl->value = 0;
    dl->is_register = true;
    return dl;
}

byte get_value_in_memory(Emulator *self, byte address)
{
    return self->memory[address];
}

byte get_value_in_rom(Emulator *self, byte address)
{
    return self->program_rom[address];
}

void set_value_in_memory(Emulator *self, byte address, byte value)
{
    self->memory[address] = value;
}

Instruction instructions[] = {
    {0x00, 0, nop, "nop"},
    {0x01, 1, lda, "lda"},
    {0x02, 1, ldb, "ldb"},
    {0x03, 1, sta, "sta"},
    {0x04, 1, stb, "stb"},
    {0x05, 0, add, "add"},
    {0x06, 0, sub, "sub"},
    {0x07, 1, jmp, "jmp"},
    {0x08, 1, je, "je"},
    {0x09, 1, jl, "jl"},
    {0x0A, 1, jg, "jg"},
    {0x0B, 0, halt, "halt"},
    {0x0C, 1, sav, "sav"},
    {0x0D, 0, cmp, "cmp"},
    {0x0E, 1, lda_const, "lda_const"},
    {0x0F, 0, aout, "aout"},
};

Instruction* get_instruction(Emulator* self, byte opcode, bool ignore_halt){
    if (opcode >= sizeof(instructions)/sizeof(Instruction)){
        if (ignore_halt){
            return &instructions[0];
        }
        else{
            printf("Unknown opcode %x! Halting...", opcode);
            self->halted = true;

            return &instructions[0];
        }
    }
    return &instructions[opcode];
}

void run(Emulator *self)
{
    while (true){
        // Fetch
        byte opcode = get_value_in_rom(self, self->r_PC->value);

        Instruction *instruction = get_instruction(self, opcode, false);
        byte argc = instruction->argc;
        byte *args = malloc(sizeof(byte)*argc);
        if (!args){
            printf("Error allocating args for instruction %d!", opcode);
            return;
        }
        for (int i = 0; i < argc; i++){
            ic(self, self->r_PC);
            args[i] = get_value_in_rom(self, self->r_PC->value);
        }
        // Execute
        instruction->operation(self, args);

        sleep_ms(20); // Uncomment this line to add an execution delay for debugging
        free(args);  

        output_state(self);
        if (self->halted){
            printf("Halted!\n");
            break;
        }
    }
}

void output(Emulator *self)
{
    printf("A: %d\n", self->r_A->value);
    printf("B: %d\n", self->r_B->value);
    printf("Flags: %d\n", self->r_Flags->value);
    printf("PC: %d\n", self->r_PC->value);
    printf("TR: %d\n", self->r_TR->value);
    printf("ALUREG: %d\n", self->r_ALUREG->value);
    printf("ALUOUT: %d\n", self->r_ALUOUT->value);
}

Emulator* create_emulator(Emulator *self, byte *buffer, long file_size)
{

    printf("Allocating emulator...\n");
    self = malloc(sizeof(Emulator));
    if (!self)
    {
        printf("Error: Could not allocate memory\n");
        return NULL;
    }
    printf("Populating memory...\n");
    self->memory_size = 256;
    self->program_size = 4096;
    self->memory = malloc(sizeof(byte)*self->memory_size);
    self->program_rom = malloc(sizeof(byte)*self->program_size);
    for (int i = 0; i < file_size; i++)
    {
        if (i == 0xFF){ // Memory size
            printf("Warning: file exceeds memory size limits!\n");
            break;
        }
        self->program_rom[i] = buffer[i];

    }
    printf("Initializing emulator...\n");
    self->r_PC = dl();
    self->r_TR = dl();
    self->r_ALUREG = dl();
    self->r_ALUOUT = dl();
    self->r_Flags = dl(); // Flags msb -> lsb = gt, eq, lt
    self->r_A = dl();
    self->r_B = dl();
    self->halted = false;
    
    StrVector* output = malloc(sizeof(StrVector));
    if (!output){
        printf("Error allocating output vector!\n");
        return NULL;
    }
    str_vector_init(output);

    self->output = output;
    return self;
}

void mov_dl(Emulator *self, DataLocation *src, DataLocation *dest){
    dest->value = src->value;
}
void set_dl(Emulator *self, DataLocation *dl, byte val){
    dl->value = val;
}

void ic(Emulator *self, DataLocation *counter){
    counter->value++;
}