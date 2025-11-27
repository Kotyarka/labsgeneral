#include "../include/functions.h"

LinkedList create_list(void) {
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return list;
}

void erase_list(LinkedList *list) {
    if (list == NULL) return;

    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_list(LinkedList *list) {
    if (list == NULL) return;
    erase_list(list);
    free(list);
}

void push_back_list(LinkedList *list, Liver *value) {
    if (list == NULL) return;

    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Malloc failes");
        return;
    }

    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (list->tail != NULL){
        list->tail->next = new_node;
    } else {
        list->head=new_node;
    }
    list->tail = new_node;
    list->size++;
}

void push_front_list(LinkedList *list, Liver *value) {
    if (list == NULL) return;
    
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return;
    }
    
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = list->head;
    
    if (list->head != NULL) {
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }
    
    list->head = new_node;
    list->size++;
}

Liver* pop_back_list(LinkedList *list) {
    if (list == NULL || list->tail == NULL) {
        fprintf(stderr, "List is empty\n");
        return 0;
    }
    
    Node *last = list->tail;
    Liver *value = last->data;
    
    if (last->prev != NULL) {
        last->prev->next = NULL;
        list->tail = last->prev;
    } else {
        list->head = NULL;
        list->tail = NULL;
    }
    
    free(last);
    list->size--;
    return value;
}

Liver* pop_front_list(LinkedList *list) {
    if (list == NULL || list->head == NULL) {
        fprintf(stderr, "List is empty\n");
        return 0;
    }
    
    Node *first = list->head;
    Liver *value = first->data;
    
    if (first->next != NULL) {
        first->next->prev = NULL;
        list->head = first->next;
    } else {
        list->head = NULL;
        list->tail = NULL;
    }
    
    free(first);
    list->size--;
    return value;
}

void insert_at_list(LinkedList *list, size_t index, Liver *value) {
    if (list == NULL || index > list->size) {
        fprintf(stderr, "Invalid index\n");
        return;
    }
    
    if (index == 0) {
        push_front_list(list, value);
        return;
    }
    
    if (index == list->size) {
        push_back_list(list, value);
        return;
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return;
    }
    
    new_node->data = value;
    new_node->prev = current->prev;
    new_node->next = current;
    
    current->prev->next = new_node;
    current->prev = new_node;
    
    list->size++;
}

void delete_at_list(LinkedList *list, size_t index) {
    if (list == NULL || index >= list->size) {
        fprintf(stderr, "Invalid index\n");
        return;
    }
    
    if (index == 0) {
        pop_front_list(list);
        return;
    }
    
    if (index == list->size - 1) {
        pop_back_list(list);
        return;
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    
    free(current);
    list->size--;
}

Liver* get_at_list(const LinkedList *list, size_t index) {
    if (list == NULL || index >= list->size) {
        fprintf(stderr, "Invalid index\n");
        return 0;
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

int is_equal_list(const LinkedList *l1, const LinkedList *l2) {
    if (l1 == NULL || l2 == NULL) return 0;
    if (l1->size != l2->size) return 0;
    
    Node *node1 = l1->head;
    Node *node2 = l2->head;
    
    while (node1 != NULL && node2 != NULL) {
        if (node1->data != node2->data) {
            return 0;
        }
        node1 = node1->next;
        node2 = node2->next;
    }
    
    return 1;
}

void push_stack(LinkedList *stack, Liver* value) {
    push_front_list(stack, value);
}

Liver* pop_stack(LinkedList *stack) {
    return pop_front_list(stack);
}

Liver* peek_stack(const LinkedList *stack) {
    if (stack == NULL || stack->head == NULL) {
        fprintf(stderr, "Stack is empty\n");
        return 0;
    }
    return stack->head->data;
}

Node* read_from_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) { perror("Error opening file"); return NULL; }

    Node* head = NULL;
    Liver l;
    while (fscanf(f, "%u %30s %30s %30s %d %d %d %c %lf",
                  &l.id, l.surname, l.name, l.patronymic,
                  &l.birth.day, &l.birth.month, &l.birth.year,
                  &l.sex, &l.income) == 9) {
        insert_sorted(&head, l);
    }
    fclose(f);
    return head;
}

void insert_sorted(Node** head, Liver l) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = l;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (!*head || compare_dates(l.birth, (*head)->data.birth_date) < 0) {
        new_node->next = *head;
        if (*head) {
            (*head)->prev = new_node;
        }
        *head = new_node;
        return;
    }

    Node* cur = *head;
    
    while (cur->next && compare_dates(cur->next->data.birth_date, l.birth) <= 0) {
        cur = cur->next;
    }

    new_node->next = cur->next;
    new_node->prev = cur;
    
    if (cur->next) {
        cur->next->prev = new_node;
    }
    
    cur->next = new_node;
}