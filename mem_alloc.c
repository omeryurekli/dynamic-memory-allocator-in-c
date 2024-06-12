  /*
  * mem_alloc.c
  * A dynamic memory allocator that uses a double linked-list list as a free list that has all the blocks we allocated for dynamic memory allocation.
  * Author: Omer Yurekli - yureklio@bc.edu
  */

#include "mem_alloc.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>





Header *free_list = NULL;

int is_allocated(Header *header) {
    return header->size & 1;
}

int is_free(Header *header) {
    if (header == NULL || ((size_t)header & (WORD_SIZE - 1)) != 0) {
        return 0;
    }
    return !(header->size & 1);
}

void set_allocated(Header *header) {
    header->size |= 1;
}

void set_free(Header *header) {
    header->size &= ~1;
}
    
Header *get_header(void *mem) {
    return (Header *)((char *)mem - sizeof(Header));
}

int same_page(Header *h1, Header *h2) {
    return ((size_t)h1 & ~(PAGE_SIZE - 1)) == ((size_t)h2 & ~(PAGE_SIZE - 1));
}

    
size_t get_size(Header *header) {
    return header->size & ~((size_t)1);
}


int mem_init() {
    void* pointer = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (pointer == MAP_FAILED) {
        return FAILURE;
    }
    Header* header = (Header*)pointer;
    header->size = PAGE_SIZE - sizeof(Header);
    header->next = NULL;
    header->previous = NULL;
    free_list = header;
    return SUCCESS;
}

int mem_extend(Header *last) {
    void* pointer = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (pointer == MAP_FAILED) {
    return FAILURE;
    }
    Header* header = (Header*)pointer;
    header->size = PAGE_SIZE - sizeof(Header);
    header->next = NULL;
    header->previous = last;
    if (last == NULL) {
        free_list = header;
    } else {
        last->next = header;
    }
    return SUCCESS;
}

void * mem_alloc(size_t requested_size) {
    if (requested_size == 0 || requested_size > PAGE_SIZE - sizeof(Header)) {
        return NULL;
    }

    if (free_list == NULL) {
        if (mem_init() == FAILURE) {
            return NULL;
        }
    }

    size_t aligned_size = (requested_size + WORD_SIZE - 1) & ~(WORD_SIZE - 1);
    Header *current = free_list;

    while (current->next != NULL && (is_allocated(current) || current->size < aligned_size)) {
        current = current->next;
    }
    if ((is_allocated(current) || current->size < aligned_size) && mem_extend(current) == FAILURE) {
        return NULL;
    }
    current = (current->next == NULL) ? current : current->next;
    if (current->size > aligned_size + sizeof(Header)) {
        Header *new_header = (Header *)((char *)current + sizeof(Header) + aligned_size);
        new_header->size = current->size - aligned_size - sizeof(Header);
        new_header->next = current->next;
        new_header->previous = current;
        if (current->next != NULL) {
            current->next->previous = new_header;
        }
        current->next = new_header;
        current->size = aligned_size;
    }
    set_allocated(current);
    char * payload_start = (char *)current + sizeof(Header);
    return payload_start;
}


void mem_free(void *ptr) {
    Header * header = get_header(ptr);
    set_free(header);
    if (header->next && is_free(header->next) && same_page(header, header->next)) {
        header->size += header->next->size + sizeof(Header);
        header->next = header->next->next;
        if (header->next) {
            header->next->previous = header;
        }
    }
    if (header->previous && is_free(header->previous) && same_page(header, header->previous)) {
        header->previous->size += header->size + sizeof(Header);
        header->previous->next = header->next;
        if (header->next) {
            header->next->previous = header->previous;
        }
        header = header->previous;
    }
    if (header->size == PAGE_SIZE - sizeof(Header)) {
        if (header->previous) {
            header->previous->next = header->next;
            if (header->next) {
                header->next->previous = header->previous;
            }
        } else if (header->next) {
            free_list = header->next;
            free_list->previous = NULL;
        } else {
            free_list = NULL;
        }
        munmap(header, PAGE_SIZE);
    }
}

void print_list() {
    if (!free_list) {
        printf("(Empty list.)\n");
        return;
    }
    while (free_list != NULL) {
        printf("%p", (void *)free_list);
        if (free_list->next != NULL) {
            printf("->");
        }
        free_list = free_list->next;
    }
    printf("\n");
}

void print_header(Header *header) {
    printf(" Addr: %p\n Size: %zu\n ", (void *)header, get_size(header));
    if (header->previous) {
        printf("Previous: %p\n ", (void *)header->previous);
    } else {
        printf("Previous: %s\n ", "0x0");
    }
    if (header->next) {
        printf("Next: %p\n", (void *)header->next);
    } else {
        printf("Next: %s\n", "0x0");
    }
}

