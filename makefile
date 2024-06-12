CC = gcc
CFLAGS = -std=gnu99 -Wall
APP = mem_alloc
FLAGS = $(CFLAGS)
TEST_TARGET = test

test: $(APP).c test_main.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f $(TEST_TARGET)


