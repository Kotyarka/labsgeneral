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

LinkedList read_from_file(const char *filename) {
    LinkedList list = create_list();
    FILE *file = fopen(filename, "r");
    
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return list;
    }
    
    Liver liver;
    while (fscanf(file, "%u %29s %29s %29s %d %d %d %c %lf",
                 &liver.id, liver.surname, liver.name, liver.patronymic,
                 &liver.birth.day, &liver.birth.month, &liver.birth.year,
                 &liver.sex, &liver.income) == 9) {
        
        if (!is_valid_name(liver.surname) || !is_valid_name(liver.name) || 
            !is_valid_date(&liver.birth) || (liver.sex != 'M' && liver.sex != 'W') ||
            liver.income < 0) {
            printf("Пропущена невалидная запись для ID %u\n", liver.id);
            continue;
        }
        
        Liver *new_liver = malloc(sizeof(Liver));
        *new_liver = liver;
        
        Node *current = list.head;
        size_t index = 0;
        while (current != NULL) {
            if (compare_dates(&new_liver->birth, &current->data->birth) > 0) {
                break;
            }
            current = current->next;
            index++;
        }
        
        insert_at_list(&list, index, new_liver);
    }
    
    fclose(file);
    printf("Прочитано %zu записей из файла\n", list.size);
    return list;
}