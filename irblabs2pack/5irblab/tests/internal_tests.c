#include "../include/include.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_word_counter_basic() {
    printf("Testing basic word counting...\n");
    char line[] = "Hello world this is a test";
    char* words[10];
    
    int count = wordCounter(line, words);
    assert(count == 6);
    assert(strcmp(words[0], "Hello") == 0);
    assert(strcmp(words[1], "world") == 0);
    assert(strcmp(words[5], "test") == 0);
    printf("✓ Basic word counting passed\n");
}

void test_word_counter_empty() {
    printf("Testing empty line...\n");
    char line[] = "";
    char* words[10];
    
    int count = wordCounter(line, words);
    assert(count == 0);
    printf("✓ Empty line test passed\n");
}

void test_word_counter_whitespace() {
    printf("Testing whitespace handling...\n");
    char line[] = "   Multiple   spaces   between   words   ";
    char* words[10];
    
    int count = wordCounter(line, words);
    assert(count == 4);
    assert(strcmp(words[0], "Multiple") == 0);
    assert(strcmp(words[1], "spaces") == 0);
    assert(strcmp(words[2], "between") == 0);
    assert(strcmp(words[3], "words") == 0);
    printf("✓ Whitespace handling passed\n");
}

void test_is_readable() {
    printf("Testing is_readable function...\n");
    assert(is_readable('a') == 1);
    assert(is_readable('Z') == 1);
    assert(is_readable('5') == 1);
    assert(is_readable('!') == 1);
    assert(is_readable(' ') == 0);
    assert(is_readable('\t') == 0);
    assert(is_readable('\n') == 0);
    printf("✓ is_readable test passed\n");
}

void test_format_line_short() {
    printf("Testing short line formatting...\n");
    char line[] = "Short line that fits";
    char buffer[1024];
    FILE* output = fopen("test_short.txt", "w+");
    
    assert(output != NULL);
    errorCodes result = formatLine(line, output);
    assert(result == OK);
    
    fseek(output, 0, SEEK_SET);
    fgets(buffer, sizeof(buffer), output);
    assert(strcmp(buffer, "Short line that fits\n") == 0);
    
    fclose(output);
    remove("test_short.txt");
    printf("✓ Short line formatting passed\n");
}

void test_format_line_long_word() {
    printf("Testing long word splitting...\n");
    char line[] = "ThisIsAVeryLongWordThatExceedsEightyCharactersAndShouldBeSplitIntoMultipleLinesWhenFormattedProperly";
    char buffer[1024];
    FILE* output = fopen("test_long_word.txt", "w+");
    
    assert(output != NULL);
    errorCodes result = formatLine(line, output);
    assert(result == OK);
    
    fseek(output, 0, SEEK_SET);
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), output)) {
        line_count++;
        assert(strlen(buffer) <= 81);
    }
    assert(line_count > 1);
    
    fclose(output);
    remove("test_long_word.txt");
    printf("✓ Long word splitting passed\n");
}

void test_format_line_multiple_long_words() {
    printf("Testing multiple long words formatting...\n");
    char line[] = "FirstWord SecondVeryLongWordThatNeedsToBeSplit ThirdWord AnotherLongWordThatAlsoRequiresSplitting";
    FILE* output = fopen("test_multi_long.txt", "w+");
    
    assert(output != NULL);
    errorCodes result = formatLine(line, output);
    assert(result == OK);
    
    fseek(output, 0, SEEK_SET);
    char buffer[1024];
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), output)) {
        line_count++;
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') len--;
        assert(len <= 80);
    }
    assert(line_count > 1);
    
    fclose(output);
    remove("test_multi_long.txt");
    printf("✓ Multiple long words formatting passed\n");
}

void test_formatting_process() {
    printf("Testing formatting process...\n");
    
    FILE* input = fopen("test_input.txt", "w");
    assert(input != NULL);
    fprintf(input, "First line\n");
    fprintf(input, "Second line with some text\n");
    fprintf(input, "A very long line that definitely exceeds eighty characters and needs to be formatted properly across multiple lines\n");
    fprintf(input, "Short\n");
    fclose(input);

    input = fopen("test_input.txt", "r");
    FILE* output = fopen("test_output.txt", "w");
    assert(input != NULL && output != NULL);
    
    errorCodes result = formattingProcess(input, output);
    assert(result == OK);
    
    fclose(input);
    fclose(output);
    
    output = fopen("test_output.txt", "r");
    assert(output != NULL);
    
    char buffer[1024];
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), output)) {
        line_count++;
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') len--;
        assert(len <= 80);
    }
    assert(line_count >= 4);
    
    fclose(output);
    
    remove("test_input.txt");
    remove("test_output.txt");
    printf("✓ Formatting process test passed\n");
}

void test_error_handling() {
    printf("Testing error handling...\n");
    
    errorCodes result = formatLine(NULL, stdout);
    assert(result == INVALID_PARAMETER);
    
    result = formatLine("test", NULL);
    assert(result == INVALID_PARAMETER);
    
    char* words[10];
    int count = wordCounter(NULL, words);
    assert(count == 0);
    
    count = wordCounter("test", NULL);
    assert(count == 0);
    
    result = formattingProcess(NULL, stdout);
    assert(result == INVALID_PARAMETER);
    
    result = formattingProcess(stdin, NULL);
    assert(result == INVALID_PARAMETER);
    
    printf("✓ Error handling test passed\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    char line1[] = "     ";
    char* words[10];
    int count = wordCounter(line1, words);
    assert(count == 0);
    
    char line2[] = "  Word1\tWord2\nWord3  ";
    count = wordCounter(line2, words);
    assert(count == 3);
    
    char longLine[2000];
    strcpy(longLine, "Start");
    for (int i = 0; i < 100; i++) {
        strcat(longLine, " word");
    }
    strcat(longLine, " end");
    
    FILE* output = fopen("test_edge.txt", "w+");
    assert(output != NULL);
    errorCodes result = formatLine(longLine, output);
    assert(result == OK);
    
    fseek(output, 0, SEEK_SET);
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') len--;
        assert(len <= 80);
    }
    
    fclose(output);
    remove("test_edge.txt");
    printf("✓ Edge cases test passed\n");
}

int main() {
    printf("Starting comprehensive tests for text formatter...\n\n");
    
    test_is_readable();
    test_word_counter_basic();
    test_word_counter_empty();
    test_word_counter_whitespace();
    test_format_line_short();
    test_format_line_long_word();
    test_format_line_multiple_long_words();
    test_formatting_process();
    test_error_handling();
    test_edge_cases();
    
    printf("\nAll formatter tests passed! ✓\n");
    return 0;
}