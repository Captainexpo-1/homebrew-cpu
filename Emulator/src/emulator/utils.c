
#include "utils.h"

void sleep_ms(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void put_bin(byte b){
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (b >> i) & 1);
    }
}

int min(int a, int b){
    return a < b ? a : b;
}
int max(int a, int b){
    return a > b ? a : b;
}
int abs(int a){
    return a < 0 ? -a : a;
}


void str_vector_init(StrVector *vec){
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

void str_vector_append(StrVector *vec, const char *str){
    if (vec->size >= vec->capacity){
        vec->capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(char*));
    }
    vec->data[vec->size] = malloc(strlen(str) + 1);
    strcpy(vec->data[vec->size], str);
    vec->size++;
}

void str_vector_free(StrVector *vec){
    for (int i = 0; i < vec->size; i++){
        free(vec->data[i]);
    }
    free(vec->data);
}

const char* str_vector_join_print(StrVector *vec, const char *delim){
    for (int i = 0; i < vec->size; i++){
        printf("%s", vec->data[i]);
        if (i < vec->size - 1){
            printf("%s", delim);
        }
    }
    return NULL;
}