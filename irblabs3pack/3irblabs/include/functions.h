#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    double* data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} LinkedList;

