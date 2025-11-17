#ifndef STACK_H
#define STACK_H
#define MAX_STACK_SIZE 1000
#include <stddef.h>
typedef struct Stack{
    int size;
    int capacity;
    char *data;
} Stack;

typedef enum errorCodes{
    OK = 0,
    BAD_INPUT = 1,
    FILE_ERROR = 2,
    MEMORY_ERROR = 3,
    OVERFLOW_ERROR = 4,
} errorCodes;

errorCodes stackInit(Stack *stack, int capacity);
int isStackEmpty(Stack*stack);
errorCodes pushStack(Stack *stack, char ch);
char topStack(const Stack *stack);
int popStack(Stack *stack);
size_t getSize(Stack *stack);
errorCodes deleteStack(Stack *stack);
int checkerBrackets(const char *str);

#endif