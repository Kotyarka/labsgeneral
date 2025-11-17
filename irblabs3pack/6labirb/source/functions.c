#include "../include/functions.h"
#include <stdlib.h>

#define MAX_STACK_SIZE 1000

errorCodes stackInit(Stack *stack, int capacity) {
    stack->capacity = capacity;
    stack->data = malloc(sizeof(char) * capacity);
    if (stack->data == NULL) {
        return MEMORY_ERROR;
    }
    stack->size = -1;
    return OK;
}

int isStackEmpty(Stack *stack) {
    return stack->size== -1;
}

errorCodes pushStack(Stack *stack, char ch) {
    if (stack->capacity <= (stack->size + 1)) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity * sizeof(char));
        if (stack->data == NULL) {
            return MEMORY_ERROR;
        }
    }
    stack->size++;
    stack->data[stack->size] = ch;
    return OK;
}


char topStack(const Stack *stack) {
    if (stack->size != -1) {
        return stack->data[stack->size];
    }
    return ' ';
}


int popStack(Stack *stack) {
    if (stack->size != -1) {
        stack->size--;
        return OK;
    }
    return OVERFLOW_ERROR;
}

errorCodes deleteStack(Stack *stack) {
    if (stack->data != NULL) {
        free(stack->data);
        return OK;
    }
    return MEMORY_ERROR;
}

size_t getSize(Stack *stack) {
    return stack->size + 1;
}

int checkerBrackets(const char *str) {
    if (str == NULL) {
        return 0;
    }

    Stack stack;
    if (stackInit(&stack, MAX_STACK_SIZE) != OK) {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        char current = str[i];
        
        if (current == '(' || current == '[' || current == '{' || current == '<') {
            if (pushStack(&stack, current) != OK) {
                deleteStack(&stack);
                return 0;
            }
        }
        else if (current == ')' || current == ']' || current == '}' || current == '>') {
            if (isStackEmpty(&stack)) {
                deleteStack(&stack);
                return 0;
            }
            
            char size = topStack(&stack); 
            
            if ((current == ')' && size == '(') ||
                (current == ']' && size == '[') ||
                (current == '}' && size == '{') ||
                (current == '>' && size == '<')) {
                popStack(&stack); 
            } else {
                deleteStack(&stack);
                return 0;
            }
        }
    }

    int result = isStackEmpty(&stack);
    deleteStack(&stack);
    
    return result;
}