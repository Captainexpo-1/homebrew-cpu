#include "printer.h"

void error(const char *message){
    fprintf(stderr, "Error: %s\n", message);
}

void help(int argc, char** argv){
    printf("Usage: %s <program> [memfile]\n", argv[0]);
    printf("filename: The file to load into program ROM\n");
    printf("memfile: The file to load into RAM (max 256 bytes)\n");
}

void clear(){
    system("clear");
}

void print(const char *message){
    printf("%s\n", message);
}