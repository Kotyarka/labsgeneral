CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99
LDFLAGS = -fsanitize=address

MAIN_PROGRAM = string_lib_test
TEST_PROGRAM = string_tests

MAIN_SOURCES = main.c
TEST_SOURCES = tests/string_tests.c

MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

$(MAIN_PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $(MAIN_PROGRAM) $(MAIN_OBJECTS)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJECTS)

main.o: main.c include/functions.h
	$(CC) $(CFLAGS) -Iinclude -c main.c -o main.o

tests/string_tests.o: tests/string_tests.c include/functions.h include/errors_macro.h
	$(CC) $(CFLAGS) -Iinclude -Wno-memset-transposed-args -Wno-stringop-truncation -Wno-nonnull -Wno-unused-variable -Wno-stringop-overread -c tests/string_tests.c -o tests/string_tests.o

test: $(TEST_PROGRAM)
	@echo "=== Running string library tests ==="
	./$(TEST_PROGRAM)

clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) *.o tests/*.o

.PHONY: all test clean