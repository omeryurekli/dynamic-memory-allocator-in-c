# Dynamic Memory Allocator

This project implements a dynamic memory allocator using a doubly-linked list as a free list. It includes functions for memory allocation, deallocation, and managing the free list.

## Overview

The dynamic memory allocator uses a doubly-linked list to manage free and allocated memory blocks. The allocator is designed to efficiently handle memory requests and deallocations, using a first-fit strategy to find suitable free blocks.

## Files

- **makefile**: The makefile for compiling the project.
- **mem_alloc.c**: The main implementation file for the dynamic memory allocator.
- **mem_alloc.h**: The header file containing type definitions and function declarations.

## makefile

The `makefile` is used to compile the project. It defines the compiler, flags, and targets for building the project.

### Targets

- **test**: Compiles the main allocator code and a test main file.
- **clean**: Removes the compiled test executable.

### Sample Commands

```makefile
CC = gcc
CFLAGS = -std=gnu99 -Wall
APP = mem_alloc
FLAGS = $(CFLAGS)
TEST_TARGET = test

test: $(APP).c test_main.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f $(TEST_TARGET)
mem_alloc.c
The mem_alloc.c file contains the implementation of the dynamic memory allocator. It includes functions for memory allocation, deallocation, and managing the free list.

Key Functions
mem_alloc: Allocates memory of a requested size.
mem_free: Frees the allocated memory.
mem_init: Initializes the memory allocator.
mem_extend: Extends the free list by allocating more memory pages.
print_list: Prints the current free list.
print_header: Prints the details of a given memory block header.
mem_alloc.h
The mem_alloc.h file contains the preprocessor directives and type definitions required by the allocator.

Type Definitions
Header: A struct representing a memory block header.
Function Declarations
mem_alloc: Allocates memory of a requested size.
mem_free: Frees the allocated memory.
mem_init: Initializes the memory allocator.
mem_extend: Extends the free list by allocating more memory pages.
print_list: Prints the current free list.
print_header: Prints the details of a given memory block header.
Usage
Compile the project:


make test
Run the compiled test executable:

./test
Clean up the build:

make clean
Author
