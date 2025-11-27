#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node {
    Liver* data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} LinkedList;

LinkedList create_list(void);
void erase_list(LinkedList *list);
void delete_list(LinkedList *list);
void push_back_list(LinkedList *list, Liver *value);
void push_front_list(LinkedList *list, Liver *value);
Liver* pop_back_list(LinkedList *list);
Liver* pop_front_list(LinkedList *list);
void insert_at_list(LinkedList *list, size_t index, Liver *value);
void delete_at_list(LinkedList *list, size_t index);
Liver* get_at_list(const LinkedList *list, size_t index);
int is_equal_list(const LinkedList *l1, const LinkedList *l2);
void push_stack(LinkedList *stack, Liver* value);
Liver* pop_stack(LinkedList *stack);
Liver* peek_stack(const LinkedList *stack);

typedef struct {
    unsigned int id;
    char surname[30];
    char name[30];
    char patronymic[30];
    Date birth;
    char sex;
    double income;
} Liver;
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    LinkedList undo_stack;
    LinkedList redo_stack;
    int modification_count;
} HistoryManager;

typedef struct {
    int operation_type; // 0 - добавление, 1 - удаление, 2 - изменение
    Liver *old_data;
    Liver *new_data;
    size_t position;
} Operation;

#endif