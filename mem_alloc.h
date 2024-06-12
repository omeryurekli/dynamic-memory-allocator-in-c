  /*
  * mem_alloc.h
  * The header file for mem_alloc.c which contains preprocessor directives and type definitions
  * Author: Omer Yurekli - yureklio@bc.edu
  */

#define MEM_ALLOC_H

#include <stddef.h>

#define PAGE_SIZE   4096
#define WORD_SIZE   8
#define SUCCESS     0
#define FAILURE     -1

typedef struct Header {
    size_t size;
    struct Header *next;
    struct Header *previous;
} Header;

void *mem_alloc(size_t requested_size);
void mem_free(void *ptr);

