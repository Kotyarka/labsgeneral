#include "../include/functions.h"
#include "../include/errors_macro.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_memchr() {
    printf("Testing memchr...\n");
    
    char str[] = "Hello, World!";
    
    // Test finding existing character
    void* result = memchr(str, 'W', sizeof(str));
    assert(result != NULL);
    assert(*(char*)result == 'W');
    assert(result == str + 7);
    
    // Test finding character within limited range
    result = memchr(str, 'o', 5);
    assert(result != NULL);
    assert(*(char*)result == 'o');
    assert(result == str + 4);
    
    // Test not finding character
    result = memchr(str, 'x', sizeof(str));
    assert(result == NULL);
    
    // Test zero length
    result = memchr(str, 'H', 0);
    assert(result == NULL);
    
    printf("✓ memchr tests passed\n");
}

void test_memcmp() {
    printf("Testing memcmp...\n");
    
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "Hellp";
    char str4[] = "Hell";
    
    // Test equal strings
    assert(memcmp(str1, str2, 5) == 0);
    
    // Test str1 < str3
    assert(memcmp(str1, str3, 5) < 0);
    
    // Test str3 > str1
    assert(memcmp(str3, str1, 5) > 0);
    
    // Test partial comparison
    assert(memcmp(str1, str4, 4) == 0);
    
    // Test zero length
    assert(memcmp(str1, str3, 0) == 0);
    
    printf("✓ memcmp tests passed\n");
}

void test_memcpy() {
    printf("Testing memcpy...\n");
    
    char src[] = "Hello, World!";
    char dest[20];
    
    // Test normal copy
    void* result = memcpy(dest, src, strlen(src) + 1);
    assert(result == dest);
    assert(strcmp(dest, src) == 0);
    
    // Test partial copy
    char dest2[10];
    memcpy(dest2, src, 5);
    dest2[5] = '\0';
    assert(strcmp(dest2, "Hello") == 0);
    
    printf("✓ memcpy tests passed\n");
}

void test_memset() {
    printf("Testing memset...\n");
    
    char buffer[10];
    
    // Test setting entire buffer
    void* result = memset(buffer, 'A', sizeof(buffer));
    assert(result == buffer);
    for (int i = 0; i < 10; i++) {
        assert(buffer[i] == 'A');
    }
    
    // Test partial set
    char buffer2[10] = "Hello";
    memset(buffer2 + 5, '!', 3);
    assert(buffer2[5] == '!' && buffer2[6] == '!' && buffer2[7] == '!');
    
    printf("✓ memset tests passed\n");
}

void test_strncat() {
    printf("Testing strncat...\n");
    
    char dest[50] = "Hello";
    char src[] = ", World!";
    
    // Test normal concatenation
    char* result = strncat(dest, src, 8);
    assert(result == dest);
    assert(strcmp(dest, "Hello, World!") == 0);
    
    // Test partial concatenation
    char dest2[50] = "Hello";
    strncat(dest2, src, 3);
    assert(strcmp(dest2, "Hello, W") == 0);
    
    // Test n larger than source length
    char dest3[50] = "Hello";
    strncat(dest3, "!", 10);
    assert(strcmp(dest3, "Hello!") == 0);
    
    printf("✓ strncat tests passed\n");
}

void test_strchr() {
    printf("Testing strchr...\n");
    
    char str[] = "Hello, World!";
    
    // Test finding existing character
    char* result = strchr(str, 'W');
    assert(result != NULL);
    assert(*result == 'W');
    assert(result == str + 7);
    
    // Test finding first occurrence
    result = strchr(str, 'l');
    assert(result != NULL);
    assert(*result == 'l');
    assert(result == str + 2);
    
    // Test not finding character
    result = strchr(str, 'x');
    assert(result == NULL);
    
    // Test null terminator
    result = strchr(str, '\0');
    assert(result != NULL);
    assert(*result == '\0');
    
    printf("✓ strchr tests passed\n");
}

void test_strncmp() {
    printf("Testing strncmp...\n");
    
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "Hellp";
    char str4[] = "Hell";
    char str5[] = "HelloWorld";
    
    // Test equal strings
    assert(strncmp(str1, str2, 5) == 0);
    
    // Test str1 < str3
    assert(strncmp(str1, str3, 5) < 0);
    
    // Test str3 > str1
    assert(strncmp(str3, str1, 5) > 0);
    
    // Test partial comparison
    assert(strncmp(str1, str4, 4) == 0);
    
    // Test n larger than shorter string length
    assert(strncmp(str1, str4, 5) > 0);
    assert(strncmp(str4, str1, 5) < 0);
    
    // Test zero length
    assert(strncmp(str1, str3, 0) == 0);
    
    printf("✓ strncmp tests passed\n");
}

void test_strncpy() {
    printf("Testing strncpy...\n");
    
    char src[] = "Hello, World!";
    char dest[20];
    
    // Test normal copy
    char* result = strncpy(dest, src, strlen(src) + 1);
    assert(result == dest);
    assert(strcmp(dest, src) == 0);
    
    // Test partial copy
    char dest2[10];
    strncpy(dest2, src, 5);
    dest2[5] = '\0';
    assert(strcmp(dest2, "Hello") == 0);
    
    // Test n larger than source
    char dest3[20];
    strncpy(dest3, src, 15);
    // Check that first 13 bytes match source
    assert(memcmp(dest3, src, 13) == 0);
    // Check that remaining bytes are padded with zeros
    for (int i = 13; i < 15; i++) {
        assert(dest3[i] == '\0');
    }
    
    printf("✓ strncpy tests passed\n");
}

void test_strcspn() {
    printf("Testing strcspn...\n");
    
    char str[] = "Hello, World!";
    
    // Test no reject characters found
    size_t result = strcspn(str, "xyz");
    assert(result == strlen(str));
    
    // Test reject character at beginning
    result = strcspn(str, "H");
    assert(result == 0);
    
    // Test reject character in middle
    result = strcspn(str, ", ");
    assert(result == 5);

    
    // Test empty reject string
    result = strcspn(str, "");
    assert(result == strlen(str));
    
    printf("✓ strcspn tests passed\n");
}

void test_strerror() {
    printf("Testing strerror...\n");
    
    // Test valid error codes
    char* result = strerror(0);
    assert(result != NULL);
    
    result = strerror(1);
    assert(result != NULL);
    printf("✓ strerror tests passed\n");
}

void test_strlen() {
    printf("Testing strlen...\n");
    
    // Test normal string
    assert(strlen("Hello") == 5);
    
    // Test empty string
    assert(strlen("") == 0);
    
    // Test string with spaces
    assert(strlen("Hello World") == 11);
    
    printf("✓ strlen tests passed\n");
}

void test_strpbrk() {
    printf("Testing strpbrk...\n");
    
    char str[] = "Hello, World!";
    
    // Test finding first occurrence
    char* result = strpbrk(str, ",!");
    assert(result != NULL);
    assert(*result == ',');
    assert(result == str + 5);
    
    // Test finding from multiple characters
    result = strpbrk(str, "ol");
    assert(result != NULL);
    assert(*result == 'l');
    assert(result == str + 2);
    
    // Test not finding any
    result = strpbrk(str, "xyz");
    assert(result == NULL);
    
    // Test empty accept string
    result = strpbrk(str, "");
    assert(result == NULL);
    
    printf("✓ strpbrk tests passed\n");
}

void test_strrchr() {
    printf("Testing strrchr...\n");
    
    char str[] = "Hello, World!";
    
    // Test finding last occurrence
    char* result = strrchr(str, 'l');
    assert(result != NULL);
    assert(*result == 'l');
    assert(result == str + 10);
    
    // Test finding single occurrence
    result = strrchr(str, 'W');
    assert(result != NULL);
    assert(*result == 'W');
    assert(result == str + 7);
    
    // Test not finding character
    result = strrchr(str, 'x');
    assert(result == NULL);
    
    // Test null terminator
    result = strrchr(str, '\0');
    assert(result != NULL);
    assert(*result == '\0');
    
    printf("✓ strrchr tests passed\n");
}

void test_strstr() {
    printf("Testing strstr...\n");
    
    char haystack[] = "Hello, World!";
    
    // Test finding substring
    char* result = strstr(haystack, "World");
    assert(result != NULL);
    assert(strcmp(result, "World!") == 0);
    
    // Test finding at beginning
    result = strstr(haystack, "Hello");
    assert(result != NULL);
    assert(result == haystack);
    
    // Test not finding substring
    result = strstr(haystack, "XYZ");
    assert(result == NULL);
    
    // Test empty needle
    result = strstr(haystack, "");
    assert(result == haystack);
    
    // Test needle longer than haystack
    result = strstr("short", "very long string");
    assert(result == NULL);
    
    printf("✓ strstr tests passed\n");
}

void test_strtok() {
    printf("Testing strtok...\n");
    
    char str[] = "Hello,World,Test";
    
    // Test first token
    char* result = strtok(str, ",");
    assert(result != NULL);
    assert(strcmp(result, "Hello") == 0);
    
    // Test second token
    result = strtok(NULL, ",");
    assert(result != NULL);
    assert(strcmp(result, "World") == 0);
    
    // Test third token
    result = strtok(NULL, ",");
    assert(result != NULL);
    assert(strcmp(result, "Test") == 0);
    
    // Test no more tokens
    result = strtok(NULL, ",");
    assert(result == NULL);
    
    // Test multiple delimiters
    char str2[] = "Hello World\tTest";
    result = strtok(str2, " \t");
    assert(result != NULL);
    assert(strcmp(result, "Hello") == 0);
    
    result = strtok(NULL, " \t");
    assert(strcmp(result, "World") == 0);
    
    result = strtok(NULL, " \t");
    assert(strcmp(result, "Test") == 0);
    
    printf("✓ strtok tests passed\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    // Test edge cases that don't trigger nonnull warnings
    char empty[] = "";
    char single[] = "a";
    
    // Test with empty strings
    assert(strlen(empty) == 0);
    assert(strchr(empty, 'a') == NULL);
    assert(strcspn(empty, "abc") == 0);
    assert(strstr(empty, "") == empty);
    
    // Test with single character
    assert(strlen(single) == 1);
    assert(strchr(single, 'a') == single);
    assert(strchr(single, 'b') == NULL);
    
    // Test zero length operations
    char buffer[10] = "test";
    memset(buffer, 'X', 0); // This should not change buffer
    assert(strcmp(buffer, "test") == 0);
    
    char buffer2[10] = "test";
    strncpy(buffer2, "new", 0); // This should not change buffer
    assert(strcmp(buffer2, "test") == 0);
    
    printf("✓ Edge cases tests passed\n");
}

int main() {
    printf("Starting comprehensive tests for string library...\n\n");
    
    test_memchr();
    test_memcmp();
    test_memcpy();
    test_memset();
    test_strncat();
    test_strchr();
    test_strncmp();
    test_strncpy();
    test_strcspn();
    test_strerror();
    test_strlen();
    test_strpbrk();
    test_strrchr();
    test_strstr();
    test_strtok();
    test_edge_cases();
    
    printf("\nAll string library tests passed! ✓\n");
    return 0;
}