#include "../include/include.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

void test_add() {
    printf("Testing add function...\n");
    
    assert(add(0, 0) == 0);
    assert(add(5, 3) == 8);
    assert(add(10, 20) == 30);
    assert(add(100, 200) == 300);
    
    assert(add(-5, 10) == 5);
    assert(add(5, -3) == 2);
    assert(add(-5, -3) == -8);
    
    assert(add(INT_MAX, 0) == INT_MAX);
    assert(add(0, INT_MIN) == INT_MIN);
    
    printf("add tests passed!\n\n");
}

void test_strSize() {
    printf("Testing strSize function...\n");
    assert(strSize("") == 0);
    assert(strSize("a") == 1);
    assert(strSize("hello") == 5);
    assert(strSize("123456789") == 9);
    
    assert(strSize(NULL) == 0);
    
    printf("strSize tests passed!\n\n");
}

void test_reverse() {
    printf("Testing reverse function...\n");
    
    char empty[] = "";
    reverse(empty);
    assert(strcmp(empty, "") == 0);
    

    char single[] = "a";
    reverse(single);
    assert(strcmp(single, "a") == 0);
    

    char even[] = "abcd";
    reverse(even);
    assert(strcmp(even, "dcba") == 0);
    
    char odd[] = "abc";
    reverse(odd);
    assert(strcmp(odd, "cba") == 0);
    
    char pal[] = "radar";
    reverse(pal);
    assert(strcmp(pal, "radar") == 0);
    
    printf("reverse tests passed!\n\n");
}

void test_rightShift() {
    printf("Testing rightShift function...\n");
    
    char empty[10] = "";
    rightShift(empty);
    assert(strcmp(empty, "") == 0);
    
    char single[10] = "a";
    rightShift(single);
    assert(single[0] == 'a');
    
    char multi[10] = "abc";
    printf("Before shift: '%s'\n", multi);
    rightShift(multi);
    printf("After shift: '%s'\n", multi);
    assert(multi[0] == 'a');
    assert(multi[1] == 'a');
    assert(multi[2] == 'b');
    assert(multi[3] == 'c');
    assert(multi[4] == '\0');
    
    printf("rightShift tests passed!\n\n");
}


void test_convertToBase_binary() {
    printf("Testing convertToBase with base 2 (binary)...\n");
    
    char result[50];
    
    assert(convertToBase(0, result, 1) == OK);
    assert(strcmp(result, "0") == 0);
    
    assert(convertToBase(5, result, 1) == OK);
    assert(strcmp(result, "101") == 0);
    
    assert(convertToBase(10, result, 1) == OK);
    assert(strcmp(result, "1010") == 0);

    printf("Binary translation tests passed!\n\n");
}

void test_convertToBase_octal() {
    printf("Testing convertToBase with base 3 (octal-like)...\n");
    
    char result[50];
    
    assert(convertToBase(7, result, 3) == OK);
    
    assert(convertToBase(8, result, 3) == OK);
    
    assert(convertToBase(-7, result, 3) == OK);
    assert(result[0] == '-');
    
    printf("Octal translation tests passed!\n\n");
}

void test_convertToBase_hexadecimal() {
    printf("Testing convertToBase with base 4 (hexadecimal-like)...\n");
    
    char result[50];
    
    assert(convertToBase(10, result, 4) == OK);
    
    assert(convertToBase(15, result, 4) == OK);
    
    assert(convertToBase(255, result, 4) == OK);
    
    printf("Hexadecimal translation tests passed!\n\n");
}

void test_convertToBase_edge_cases() {
    printf("Testing convertToBase edge cases...\n");
    
    char result[50];
    
    assert(convertToBase(10, NULL, 2) == POINTER_ERROR);
    
    assert(convertToBase(INT_MAX, result, 1) == OK);
    assert(convertToBase(INT_MIN, result, 1) == OK);
    assert(result[0] == '-');
    
    assert(convertToBase(255, result, 1) == OK); // binary
    assert(convertToBase(255, result, 3) == OK); // base 8
    assert(convertToBase(255, result, 4) == OK); // base 16
    assert(convertToBase(255, result, 5) == OK); // base 32
    
    printf("Edge cases tests passed!\n\n");
}

void test_convertToBase_base_32() {
    printf("Testing convertToBase with base 5 (base 32-like)...\n");
    
    char result[50];
    
    assert(convertToBase(31, result, 5) == OK);
    
    assert(convertToBase(35, result, 5) == OK);
    
    printf("Base 32 translation tests passed!\n\n");
}

void test_integration() {
    printf("Testing integration of functions...\n");
    
    char result[50];
    
    assert(convertToBase(42, result, 1) == OK);
    int len = strSize(result);
    assert(len > 0);

    char reversed[50];
    strcpy(reversed, result);
    reverse(reversed);
    if (strcmp(result, reversed) != 0) {
        reverse(reversed); 
        assert(strcmp(result, reversed) == 0);
    }
    
    printf("Integration tests passed!\n\n");
}

void run_all_tests() {
    printf("=== Starting All Tests for Bitwise Number Conversion ===\n\n");
    
    test_add();
    test_strSize();
    test_reverse();
    test_rightShift();
    test_convertToBase_binary();
    test_convertToBase_octal();
    test_convertToBase_hexadecimal();
    test_convertToBase_base_32();
    test_convertToBase_edge_cases();
    test_integration();
    
    printf("=== All Tests Passed! ===\n");
}

int main() {
    run_all_tests();
    return 0;
}