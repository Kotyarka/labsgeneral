CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fsanitize=address -std=c99
LDFLAGS = -fsanitize=address -lm

MAIN_PROGRAM = text_formatter
TEST_PROGRAM = internal_tests

MAIN_SOURCES = main.c source/formatting.c
TEST_SOURCES = tests/internal_tests.c source/formatting.c

MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

all: $(MAIN_PROGRAM) $(TEST_PROGRAM)

$(MAIN_PROGRAM): $(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) -o $(MAIN_PROGRAM) $(MAIN_OBJECTS)

$(TEST_PROGRAM): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $(TEST_PROGRAM) $(TEST_OBJECTS)

main.o: main.c include/include.h
	$(CC) $(CFLAGS) -Iinclude -c main.c -o main.o

source/formatting.o: source/formatting.c include/include.h
	$(CC) $(CFLAGS) -Iinclude -c source/formatting.c -o source/formatting.o

tests/internal_tests.o: tests/internal_tests.c include/include.h
	$(CC) $(CFLAGS) -Iinclude -c tests/internal_tests.c -o tests/internal_tests.o

test: $(MAIN_PROGRAM) $(TEST_PROGRAM)
	@echo "=== Running internal tests ==="
	./$(TEST_PROGRAM)
	@echo ""
	@echo "=== Running external tests ==="
	@echo ""
	
	@echo "Test 1: Invalid input file path"
	@echo "nonexistent.txt" > test_runner1.txt
	@echo "output.txt" >> test_runner1.txt
	@./$(MAIN_PROGRAM) < test_runner1.txt 2>&1 | grep -q "Cannot open input file" && echo "✓ PASS" || (echo "✗ FAIL"; ./$(MAIN_PROGRAM) < test_runner1.txt 2>&1)
	@echo ""
	
	@echo "Test 2: Invalid output file path"
	@echo "valid_input.txt" > test_runner2.txt
	@echo "/invalid/path/output.txt" >> test_runner2.txt
	@echo "This is test content" > valid_input.txt
	@./$(MAIN_PROGRAM) < test_runner2.txt 2>&1 | grep -q "Cannot open output file" && echo "✓ PASS" || (echo "✗ FAIL"; ./$(MAIN_PROGRAM) < test_runner2.txt 2>&1)
	@echo ""
	
	@echo "Test 3: Basic text formatting"
	@echo "This is a short line that should not be modified." > test_input3.txt
	@echo "This is a much longer line that definitely exceeds the eighty character limit and should be formatted across multiple lines properly." >> test_input3.txt
	@echo "Short line." >> test_input3.txt
	@echo "test_input3.txt" > test_runner3.txt
	@echo "test_output3.txt" >> test_runner3.txt
	@./$(MAIN_PROGRAM) < test_runner3.txt 2>&1 | grep -q "Formatting completed successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking output file content:"
	@cat test_output3.txt | grep -q "This is a short line that should not be modified." && echo "✓ PASS (short line preserved)" || echo "✗ FAIL"
	@cat test_output3.txt | wc -l | grep -q "4" && echo "✓ PASS (correct number of lines)" || echo "✗ FAIL"
	@echo "Checking line length constraints:"
	@while IFS= read -r line; do length=$$(echo "$$line" | tr -d '\n' | wc -c); if [ $$length -gt 80 ]; then echo "✗ FAIL: Line too long: $$length chars"; exit 1; fi; done < test_output3.txt && echo "✓ PASS (all lines <= 80 chars)" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 4: Very long word handling"
	@echo "ThisIsAnExtremelyLongWordThatExceedsEightyCharactersAndShouldBeSplitIntoMultipleLinesWhenFormatted" > test_input4.txt
	@echo "test_input4.txt" > test_runner4.txt
	@echo "test_output4.txt" >> test_runner4.txt
	@./$(MAIN_PROGRAM) < test_runner4.txt 2>&1 | grep -q "Formatting completed successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@cat test_output4.txt | wc -l | grep -q "2" && echo "✓ PASS (long word split)" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 5: Multiple spaces and formatting"
	@echo "   Multiple    spaces    between    words    should    be    handled    properly    " > test_input5.txt
	@echo "Another line with normal spacing." >> test_input5.txt
	@echo "test_input5.txt" > test_runner5.txt
	@echo "test_output5.txt" >> test_runner5.txt
	@./$(MAIN_PROGRAM) < test_runner5.txt 2>&1 | grep -q "Formatting completed successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking extra spaces removal:"
	@cat test_output5.txt | grep -q "Multiple spaces between words should be handled properly" && echo "✓ PASS (extra spaces removed)" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 6: Empty input file"
	@echo "" > test_input6.txt
	@echo "test_input6.txt" > test_runner6.txt
	@echo "test_output6.txt" >> test_runner6.txt
	@./$(MAIN_PROGRAM) < test_runner6.txt 2>&1 | grep -q "Formatting completed successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@test -f test_output6.txt && echo "✓ PASS (output file created)" || echo "✗ FAIL"
	@test ! -s test_output6.txt && echo "✓ PASS (empty output for empty input)" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 7: Mixed content formatting"
	@echo "Short" > test_input7.txt
	@echo "" >> test_input7.txt
	@echo "This line contains a mix of short words and oneverylongwordthatexceedsthelimit followed by normal text." >> test_input7.txt
	@echo "    Leading and trailing spaces    " >> test_input7.txt
	@echo "test_input7.txt" > test_runner7.txt
	@echo "test_output7.txt" >> test_runner7.txt
	@./$(MAIN_PROGRAM) < test_runner7.txt 2>&1 | grep -q "Formatting completed successfully" && echo "✓ PASS" || echo "✗ FAIL"
	@echo "Checking complex formatting:"
	@while IFS= read -r line; do length=$$(echo "$$line" | tr -d '\n' | wc -c); if [ $$length -gt 80 ]; then echo "✗ FAIL: Line too long: $$length chars"; exit 1; fi; done < test_output7.txt && echo "✓ PASS (all lines formatted correctly)" || echo "✗ FAIL"
	@echo ""
	
	@echo "Test 8: Empty input file path"
	@echo "" > test_runner8.txt
	@echo "test_output3.txt" >> test_runner8.txt
	@./$(MAIN_PROGRAM) < test_runner8.txt 2>&1 | grep -q "Input file path is empty" && echo "✓ PASS" || (echo "✗ FAIL"; ./$(MAIN_PROGRAM) < test_runner8.txt 2>&1)
	@echo ""
	
	@echo "Test 9: Empty output file path"
	@echo "test_input3.txt" > test_runner9.txt
	@echo "" >> test_runner9.txt
	@./$(MAIN_PROGRAM) < test_runner9.txt 2>&1 | grep -q "Output file path is empty" && echo "✓ PASS" || (echo "✗ FAIL"; ./$(MAIN_PROGRAM) < test_runner9.txt 2>&1)
	@echo ""
	
	@echo "Cleaning up test files..."
	@rm -f test_input*.txt test_output*.txt test_runner*.txt valid_input.txt
	
	@echo "All tests completed!"

clean:
	rm -f $(MAIN_PROGRAM) $(TEST_PROGRAM) source/*.o tests/*.o *.o test_input*.txt test_output*.txt test_runner*.txt valid_input.txt

.PHONY: all test clean