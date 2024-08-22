
#ifndef UTILS_H
#define UTILS_H
#define LOG_LEVEL 0

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef unsigned char byte; // Convenience typedef for unsigned char or uint8_t 

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void sleep_ms(int milliseconds);
void put_bin(byte b);
int min(int a, int b);
int max(int a, int b);
int abs(int a);

typedef struct StrVector {
    char **data;
    size_t size;
    size_t capacity;
} StrVector;

void str_vector_init(StrVector *vec);
void str_vector_append(StrVector *vec, const char *str);
void str_vector_free(StrVector *vec);
const char* str_vector_join_print(StrVector *vec, const char *delim);
#endif