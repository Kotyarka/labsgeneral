#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    unsigned int id;
    char surname[30];
    char name[30];
    char patronymic[30];
    Date birth;
    char sex;
    double income;
} Liver;

typedef struct Node {
    Liver *data;
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

typedef enum {
    OP_ADD,
    OP_DELETE,
    OP_MODIFY
} OperationType;

typedef struct {
    OperationType type;
    size_t position;
    Liver *liver_data;
    Liver *old_data;
} UndoOperation;

typedef struct {
    LinkedList undo_stack;
    int modification_count;
} UndoSystem;

void init_undo_system(UndoSystem *us);
void clear_undo_system(UndoSystem *us);
void push_undo_operation(UndoSystem *us, OperationType type, size_t position,
                         Liver *liver_data, Liver *old_data);
void undo_modifications(LinkedList *list, UndoSystem *us);

int compare_dates(const Date *d1, const Date *d2);
int is_valid_name(const char *name);
int is_valid_date(const Date *date);

int find_liver_position(const LinkedList *list, unsigned int id);
size_t find_insert_position(const LinkedList *list, const Date *birth_date);

LinkedList read_from_file(const char *filename);
void save_to_file(const LinkedList *list, const char *filename);

void search_by_surname(const LinkedList *list, const char *surname);
void search_by_id(const LinkedList *list, unsigned int id);

void add_liver(LinkedList *list, UndoSystem *us);
void remove_liver(LinkedList *list, UndoSystem *us, unsigned int id);
void modify_liver(LinkedList *list, UndoSystem *us, unsigned int id);

void display_all(const LinkedList *list);
void print_menu();

#endif