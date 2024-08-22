#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif



#include <stdio.h>
#include "emulator.h"
#include "emulatorMethods.h"
#include <stdlib.h>



int main(int argc, char const *argv[])
{
    int log_level = 0;
    bool mem_file = false;
    char* mem_file_name;
    if (log_level > 0) printf("Starting...\n");
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    if (argc > 2){
        mem_file = true;
        mem_file_name = argv[2];
    }
    if (log_level > 0) printf("Opening file...\n");
    FILE *file = fopen(argv[1], "rb");
    if (!file)
    {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    byte *buffer = malloc(file_size);
    if (!buffer)
    {
        printf("Error: Could not allocate memory\n");
        return 1;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    if (mem_file){
        FILE *mem_file = fopen(mem_file_name, "rb");
        if (!mem_file)
        {
            printf("Error: Could not open file %s\n", mem_file_name);
            return 1;
        }
        fseek(mem_file, 0, SEEK_END);
        long mem_file_size = ftell(mem_file);
        fseek(mem_file, 0, SEEK_SET);
        byte *mem_buffer = malloc(mem_file_size);
        if (!mem_buffer)
        {
            printf("Error: Could not allocate memory\n");
            return 1;
        }
        fread(mem_buffer, 1, mem_file_size, mem_file);
        fclose(mem_file);
        for (int i = 0; i < mem_file_size; i++)
        {
            if (i == 0xFF){ // Memory size
                printf("Warning: file exceeds memory size limits!\n");
                break;
            }
            buffer[i] = mem_buffer[i];
        }
        free(mem_buffer);
    }

    if (log_level > 0) printf("Creating emulator...\n");
    Emulator *emulator = NULL;
    emulator = create_emulator(emulator, buffer, file_size);
    if (!emulator)
    {
        printf("Error: Could not create emulator\n");
        return 1;
    }
    if (log_level > 0) printf("Starting emulator...\n");
    run(emulator);
    //output(emulator);
    if (log_level > 0) printf("Stopping...\n");
    destroy_emulator(emulator);
    free(buffer);
}
