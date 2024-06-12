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
