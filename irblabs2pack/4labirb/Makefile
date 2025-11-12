CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99
LDFLAGS = -fsanitize=address

MAIN_PROGRAM = main_program
TEST_PROGRAM = tests_program

MAIN_SOURCES = main.c source/functions.c
TEST_SOURCES = tests/tests.c source/functions.c

MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

$(MAIN_PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $(MAIN_PROGRAM) $(MAIN_OBJECTS)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJECTS)

main.o: main.c include/functions.h
	$(CC) $(CFLAGS) -Iinclude -c main.c -o main.o

source/functions.o: source/functions.c include/functions.h
	$(CC) $(CFLAGS) -Iinclude -c source/functions.c -o source/functions.o

tests/tests.o: tests/tests.c include/functions.h
	$(CC) $(CFLAGS) -Iinclude -c tests/tests.c -o tests/tests.o

test: $(TEST_PROGRAM)
	@echo "=== Running custom printf/scanf tests ==="
	./$(TEST_PROGRAM)

clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) $(MAIN_OBJECTS) $(TEST_OBJECTS)

.PHONY: all test clean