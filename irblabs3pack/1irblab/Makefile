CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99 
LDFLAGS = -fsanitize=address -lm

MAIN_PROGRAM = program
TEST_PROGRAM = test_program

SRC_DIR = source
INC_DIR = include
TST_DIR = tests

MAIN_SOURCES = main.c $(SRC_DIR)/function.c
TEST_SOURCES = $(TST_DIR)/test.c $(SRC_DIR)/function.c

MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

$(MAIN_PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $(MAIN_PROGRAM) $(MAIN_OBJECTS)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJECTS)

main.o: main.c $(INC_DIR)/include.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(SRC_DIR)/function.o: $(SRC_DIR)/function.c $(INC_DIR)/include.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(TST_DIR)/test.o: $(TST_DIR)/test.c $(INC_DIR)/include.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

test: $(TEST_PROGRAM)
	@echo "internal tests:"
	./$(TEST_PROGRAM)

clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) *.o $(SRC_DIR)/*.o $(TST_DIR)/*.o

.PHONY: all test clean