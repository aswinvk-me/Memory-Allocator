

#include <stdio.h>
#include <stdlib.h> //memset function in this
#include <unistd.h> //sbrk function in this
#include <string.h>

#define ALIGN 16

typedef union Header
{
    struct
    {
        size_t size;
        int is_free;
        union Header *next;
    };
    char padding[32]; // force header to be 32 bytes (multiple of 16)
} Header;



void *my_malloc(int);
void my_free(void *);
void *my_realloc(void *, size_t);
void *my_calloc(size_t, size_t);
size_t align(size_t);
void print_heap();