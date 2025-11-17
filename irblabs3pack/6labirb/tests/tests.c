#include "../include/functions.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_stackInit() {
    printf("Testing stackInit...\n");
    
    Stack stack;
    
    assert(stackInit(&stack, 1000) == OK);
    assert(stack.capacity == 1000);
    assert(stack.size == -1);
    assert(stack.data != NULL);
    deleteStack(&stack);
    
    assert(stackInit(&stack, 1) == OK);
    deleteStack(&stack);
    
    printf("✓ stackInit tests passed\n");
}

void test_isStackEmpty() {
    printf("Testing isStackEmpty...\n");
    
    Stack stack;
    stackInit(&stack, 10);
    
    assert(isStackEmpty(&stack) == 1);
    
    pushStack(&stack, 'A');
    assert(isStackEmpty(&stack) == 0);
    
    popStack(&stack);
    assert(isStackEmpty(&stack) == 1);
    
    deleteStack(&stack);
    
    printf("✓ isStackEmpty tests passed\n");
}

void test_pushStack() {
    printf("Testing pushStack...\n");
    
    Stack stack;
    stackInit(&stack, 2);
    
    assert(pushStack(&stack, 'A') == OK);
    assert(stack.size == 0);
    assert(stack.data[0] == 'A');
    
    assert(pushStack(&stack, 'B') == OK);
    assert(pushStack(&stack, 'C') == OK);
    assert(stack.capacity > 2);
    
    assert(pushStack(&stack, 'D') == OK);
    assert(stack.size == 3);
    
    deleteStack(&stack);
    
    printf("✓ pushStack tests passed\n");
}

void test_topStack() {
    printf("Testing topStack...\n");
    
    Stack stack;
    stackInit(&stack, 10);
    
    assert(topStack(&stack) == ' ');
    
    pushStack(&stack, 'A');
    char result = topStack(&stack);
    assert(result == 'A');
    assert(stack.size == 0);
    
    pushStack(&stack, 'B');
    result = topStack(&stack);
    assert(result == 'B');
    assert(stack.size == 1);
    
    deleteStack(&stack);
    
    printf("✓ topStack tests passed\n");
}

void test_popStack() {
    printf("Testing popStack...\n");
    
    Stack stack;
    stackInit(&stack, 10);
    
    pushStack(&stack, 'A');
    pushStack(&stack, 'B');
    
    assert(popStack(&stack) == OK);
    assert(stack.size == 0);
    assert(topStack(&stack) == 'A');
    
    assert(popStack(&stack) == OK);
    assert(stack.size == -1);
    
    
    deleteStack(&stack);
    
    printf("✓ popStack tests passed\n");
}

void test_deleteStack() {
    printf("Testing deleteStack...\n");
    
    Stack stack;
    stackInit(&stack, 10);
    
    assert(deleteStack(&stack) == OK);
    
    printf("✓ deleteStack tests passed\n");
}

void test_getSize() {
    printf("Testing getSize...\n");
    
    Stack stack;
    stackInit(&stack, 10);
    
    assert(getSize(&stack) == 0);
    
    pushStack(&stack, 'A');
    assert(getSize(&stack) == 1);
    
    pushStack(&stack, 'B');
    pushStack(&stack, 'C');
    assert(getSize(&stack) == 3);
    
    popStack(&stack);
    assert(getSize(&stack) == 2);
    
    deleteStack(&stack);
    
    printf("✓ getSize tests passed\n");
}

void test_check_brackets_basic() {
    printf("Testing checkerBrackets basic cases...\n");
    
    assert(checkerBrackets("()") == 1);
    assert(checkerBrackets("[]") == 1);
    assert(checkerBrackets("{}") == 1);
    assert(checkerBrackets("<>") == 1);
    assert(checkerBrackets("()[]{}<>") == 1);
    assert(checkerBrackets("([{<>}])") == 1);
    assert(checkerBrackets("") == 1);
    assert(checkerBrackets(NULL) == 0);
    
    assert(checkerBrackets("(") == 0);
    assert(checkerBrackets(")") == 0);
    assert(checkerBrackets("([)]") == 0);
    assert(checkerBrackets("({)}") == 0);
    assert(checkerBrackets("<[>]") == 0);
    
    printf("✓ checkerBrackets basic tests passed\n");
}

void test_check_brackets_with_text() {
    printf("Testing checkerBrackets with text...\n");
    
    assert(checkerBrackets("(hello world)") == 1);
    assert(checkerBrackets("array[123] + object{key: value}") == 1);
    assert(checkerBrackets("function<int(int)> f;") == 1);
    assert(checkerBrackets("a = (b + c) * [d - e] / {f % g} <h>") == 1);
    
    assert(checkerBrackets("(hello world") == 0);
    assert(checkerBrackets("array[123] + object{key: value") == 0);
    assert(checkerBrackets("if (x > 0) { y = x * 2; ") == 0);
    assert(checkerBrackets("function<int(int))> f;") == 0);
    
    printf("✓ checkerBrackets with text tests passed\n");
}

void test_check_brackets_complex() {
    printf("Testing checkerBrackets complex cases...\n");
    
    assert(checkerBrackets("((([{<>}])))") == 1);
    assert(checkerBrackets("<({[]})>") == 1);
    assert(checkerBrackets("([{<((()))>}])") == 1);
    assert(checkerBrackets("({[<>]})") == 1);
    assert(checkerBrackets("<{[()]}>") == 1);
    
    assert(checkerBrackets("((([{<>}))))") == 0);
    assert(checkerBrackets("<({[})>") == 0);
    assert(checkerBrackets("([{<((())>}])") == 0);
    
    printf("✓ checkerBrackets complex tests passed\n");
}

void test_check_brackets_edge_cases() {
    printf("Testing checkerBrackets edge cases...\n");
    
    assert(checkerBrackets("(((([[[{{{<<<") == 0);
    assert(checkerBrackets("))))]}}>>))") == 0);
    assert(checkerBrackets("a") == 1);
    assert(checkerBrackets("1") == 1);
    assert(checkerBrackets(" ") == 1);
    assert(checkerBrackets("@") == 1);
    
    char long_balanced[1000];
    int pos = 0;
    for (int i = 0; i < 100; i++) {
        long_balanced[pos++] = '(';
        long_balanced[pos++] = '[';
        long_balanced[pos++] = '{';
        long_balanced[pos++] = '<';
    }
    for (int i = 0; i < 100; i++) {
        long_balanced[pos++] = '>';
        long_balanced[pos++] = '}';
        long_balanced[pos++] = ']';
        long_balanced[pos++] = ')';
    }
    long_balanced[pos] = '\0';
    assert(checkerBrackets(long_balanced) == 1);
    
    char long_unbalanced[1000];
    pos = 0;
    for (int i = 0; i < 100; i++) {
        long_unbalanced[pos++] = '(';
        long_unbalanced[pos++] = '[';
        long_unbalanced[pos++] = '{';
        long_unbalanced[pos++] = '<';
    }
    for (int i = 0; i < 99; i++) {
        long_unbalanced[pos++] = '>';
        long_unbalanced[pos++] = '}';
        long_unbalanced[pos++] = ']';
        long_unbalanced[pos++] = ')';
    }
    long_unbalanced[pos] = '\0';
    assert(checkerBrackets(long_unbalanced) == 0);
    
    printf("✓ checkerBrackets edge cases tests passed\n");
}

void test_check_brackets_performance() {
    printf("Testing checkerBrackets performance...\n");
    
    char max_brackets[MAX_STACK_SIZE * 2 + 1];
    int pos = 0;
    
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        max_brackets[pos++] = '(';
    }
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        max_brackets[pos++] = ')';
    }
    max_brackets[pos] = '\0';
    
    assert(checkerBrackets(max_brackets) == 1);
    
    printf("✓ checkerBrackets performance tests passed\n");
}

int main() {
    printf("Starting comprehensive tests for bracket checker...\n\n");
    
    test_stackInit();
    test_isStackEmpty();
    test_pushStack();
    test_topStack();
    test_popStack();
    test_deleteStack();
    test_getSize();
    test_check_brackets_basic();
    test_check_brackets_with_text();
    test_check_brackets_complex();
    test_check_brackets_edge_cases();
    test_check_brackets_performance();
    
    printf("\nAll bracket checker tests passed! ✓\n");
    return 0;
}