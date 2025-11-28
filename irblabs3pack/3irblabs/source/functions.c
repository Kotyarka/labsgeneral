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
}

void push_back_list(LinkedList *list, Liver *value) {
    if (list == NULL) return;

    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Malloc failed\n");
        return;
    }

    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (list->tail != NULL)
        list->tail->next = new_node;
    else
        list->head = new_node;

    list->tail = new_node;
    list->size++;
}

void push_front_list(LinkedList *list, Liver *value) {
    if (list == NULL) return;

    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Malloc failed\n");
        return;
    }

    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = list->head;

    if (list->head != NULL)
        list->head->prev = new_node;
    else
        list->tail = new_node;

    list->head = new_node;
    list->size++;
}

Liver* pop_back_list(LinkedList *list) {
    if (!list || !list->tail) return NULL;

    Node *last = list->tail;
    Liver *value = last->data;

    if (last->prev) {
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
    if (!list || !list->head) return NULL;

    Node *first = list->head;
    Liver *value = first->data;

    if (first->next) {
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
    if (!list || index > list->size) return;

    if (index == 0) {
        push_front_list(list, value);
        return;
    }
    if (index == list->size) {
        push_back_list(list, value);
        return;
    }

    Node *current = list->head;
    for (size_t i = 0; i < index; i++)
        current = current->next;

    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
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
    if (!list || index >= list->size) return;

    if (index == 0) {
        pop_front_list(list);
        return;
    }
    if (index == list->size - 1) {
        pop_back_list(list);
        return;
    }

    Node *current = list->head;
    for (size_t i = 0; i < index; i++)
        current = current->next;

    current->prev->next = current->next;
    current->next->prev = current->prev;

    free(current);
    list->size--;
}

Liver* get_at_list(const LinkedList *list, size_t index) {
    if (!list || index >= list->size) return NULL;

    Node *current = list->head;
    for (size_t i = 0; i < index; i++)
        current = current->next;

    return current->data;
}

int is_equal_list(const LinkedList *l1, const LinkedList *l2) {
    if (!l1 || !l2) return 0;
    if (l1->size != l2->size) return 0;

    Node *a = l1->head;
    Node *b = l2->head;

    while (a && b) {
        if (a->data != b->data) return 0;
        a = a->next;
        b = b->next;
    }

    return 1;
}

void push_stack(LinkedList *stack, Liver *value) {
    push_front_list(stack, value);
}

Liver* pop_stack(LinkedList *stack) {
    return pop_front_list(stack);
}

Liver* peek_stack(const LinkedList *stack) {
    if (!stack || !stack->head) return NULL;
    return stack->head->data;
}

void init_undo_system(UndoSystem *us) {
    us->undo_stack = create_list();
    us->modification_count = 0;
}

void clear_undo_system(UndoSystem *us) {
    while (us->undo_stack.size > 0) {
        UndoOperation *op = (UndoOperation*)pop_stack(&us->undo_stack);
        if (op->liver_data) free(op->liver_data);
        if (op->old_data) free(op->old_data);
        free(op);
    }
    erase_list(&us->undo_stack);
    us->modification_count = 0;
}

void push_undo_operation(UndoSystem *us, OperationType type, size_t position,
                         Liver *liver_data, Liver *old_data)
{
    UndoOperation *op = malloc(sizeof(UndoOperation));
    if (!op) return;

    op->type = type;
    op->position = position;

    op->liver_data = liver_data ? malloc(sizeof(Liver)) : NULL;
    if (liver_data && op->liver_data)
        *op->liver_data = *liver_data;

    op->old_data = old_data ? malloc(sizeof(Liver)) : NULL;
    if (old_data && op->old_data)
        *op->old_data = *old_data;

    push_stack(&us->undo_stack, (Liver*)op);
    us->modification_count++;
}

int compare_dates(const Date *d1, const Date *d2) {
    if (d1->year != d2->year) return d1->year - d2->year;
    if (d1->month != d2->month) return d1->month - d2->month;
    return d1->day - d2->day;
}

int is_valid_name(const char *name) {
    if (!name || strlen(name) == 0) return 0;
    for (size_t i = 0; i < strlen(name); i++)
        if (!isalpha(name[i])) return 0;
    return 1;
}

int is_valid_date(const Date *date) {
    if (date->year < 1900 || date->year > 2024) return 0;
    if (date->month < 1 || date->month > 12) return 0;
    if (date->day < 1 || date->day > 31) return 0;

    int days_in_month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date->day > days_in_month[date->month - 1]) return 0;

    return 1;
}

int find_liver_position(const LinkedList *list, unsigned int id) {
    Node *cur = list->head;
    size_t pos = 0;

    while (cur) {
        if (cur->data->id == id)
            return pos;
        cur = cur->next;
        pos++;
    }
    return -1;
}

size_t find_insert_position(const LinkedList *list, const Date *birth_date) {
    Node *cur = list->head;
    size_t pos = 0;

    while (cur) {
        if (compare_dates(birth_date, &cur->data->birth) > 0)
            break;
        cur = cur->next;
        pos++;
    }
    return pos;
}

LinkedList read_from_file(const char *filename) {
    LinkedList list = create_list();

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return list;
    }

    Liver temp;
    while (fscanf(file, "%u %29s %29s %29s %d %d %d %c %lf",
                  &temp.id, temp.surname, temp.name, temp.patronymic,
                  &temp.birth.day, &temp.birth.month, &temp.birth.year,
                  &temp.sex, &temp.income) == 9)
    {
        if (!is_valid_name(temp.surname) ||
            !is_valid_name(temp.name) ||
            !is_valid_date(&temp.birth) ||
            (temp.sex != 'M' && temp.sex != 'W') ||
            temp.income < 0)
        {
            printf("Skipped invalid record (ID %u)\n", temp.id);
            continue;
        }

        Liver *l = malloc(sizeof(Liver));
        *l = temp;

        size_t pos = find_insert_position(&list, &l->birth);
        insert_at_list(&list, pos, l);
    }

    fclose(file);
    printf("Loaded: %zu records\n", list.size);
    return list;
}

void save_to_file(const LinkedList *list, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error creating file %s\n", filename);
        return;
    }

    Node *cur = list->head;

    while (cur) {
        Liver *l = cur->data;
        fprintf(file, "%u %s %s %s %d %d %d %c %.2lf\n",
                l->id, l->surname, l->name, l->patronymic,
                l->birth.day, l->birth.month, l->birth.year,
                l->sex, l->income);
        cur = cur->next;
    }

    fclose(file);
    printf("Data saved to %s\n", filename);
}

void search_by_surname(const LinkedList *list, const char *surname) {
    Node *cur = list->head;
    int found = 0;

    printf("Search by surname: %s\n", surname);

    while (cur) {
        if (strcmp(cur->data->surname, surname) == 0) {
            Liver *l = cur->data;
            printf("ID %u - %s %s %s, %02d.%02d.%04d, %c, income %.2lf\n",
                   l->id, l->surname, l->name, l->patronymic,
                   l->birth.day, l->birth.month, l->birth.year,
                   l->sex, l->income);
            found = 1;
        }
        cur = cur->next;
    }

    if (!found)
        printf("No records found\n");
}

void search_by_id(const LinkedList *list, unsigned int id) {
    Node *cur = list->head;

    while (cur) {
        if (cur->data->id == id) {
            Liver *l = cur->data;
            printf("ID %u - %s %s %s, %02d.%02d.%04d, %c, income %.2lf\n",
                   l->id, l->surname, l->name, l->patronymic,
                   l->birth.day, l->birth.month, l->birth.year,
                   l->sex, l->income);
            return;
        }
        cur = cur->next;
    }

    printf("Resident with ID %u not found\n", id);
}

void add_liver(LinkedList *list, UndoSystem *us) {
    Liver new_liver;

    printf("Enter ID: ");
    scanf("%u", &new_liver.id);
    getchar();

    if (find_liver_position(list, new_liver.id) != -1) {
        printf("Error: ID already exists.\n");
        return;
    }

    printf("Enter surname: ");
    fgets(new_liver.surname, sizeof(new_liver.surname), stdin);
    new_liver.surname[strcspn(new_liver.surname, "\n")] = 0;
    if (!is_valid_name(new_liver.surname)) {
        printf("Invalid surname.\n");
        return;
    }

    printf("Enter name: ");
    fgets(new_liver.name, sizeof(new_liver.name), stdin);
    new_liver.name[strcspn(new_liver.name, "\n")] = 0;
    if (!is_valid_name(new_liver.name)) {
        printf("Invalid name.\n");
        return;
    }

    printf("Enter patronymic: ");
    fgets(new_liver.patronymic, sizeof(new_liver.patronymic), stdin);
    new_liver.patronymic[strcspn(new_liver.patronymic, "\n")] = 0;

    printf("Enter birth date (dd mm yyyy): ");
    scanf("%d %d %d", &new_liver.birth.day, &new_liver.birth.month, &new_liver.birth.year);
    getchar();
    if (!is_valid_date(&new_liver.birth)) {
        printf("Invalid date.\n");
        return;
    }

    printf("Enter sex (M/W): ");
    scanf("%c", &new_liver.sex);
    getchar();
    new_liver.sex = toupper(new_liver.sex);
    if (new_liver.sex != 'M' && new_liver.sex != 'W') {
        printf("Invalid sex.\n");
        return;
    }

    printf("Enter income: ");
    scanf("%lf", &new_liver.income);
    getchar();
    if (new_liver.income < 0) {
        printf("Invalid income.\n");
        return;
    }

    Liver *copy = malloc(sizeof(Liver));
    *copy = new_liver;

    size_t pos = find_insert_position(list, &copy->birth);
    insert_at_list(list, pos, copy);

    push_undo_operation(us, OP_ADD, pos, copy, NULL);

    printf("Resident added.\n");
}

void remove_liver(LinkedList *list, UndoSystem *us, unsigned int id) {
    int pos = find_liver_position(list, id);
    if (pos == -1) {
        printf("Resident not found.\n");
        return;
    }

    Liver *l = get_at_list(list, pos);
    if (!l) return;

    Liver *backup = malloc(sizeof(Liver));
    *backup = *l;

    delete_at_list(list, pos);

    push_undo_operation(us, OP_DELETE, pos, backup, NULL);

    printf("Resident removed.\n");
}

void modify_liver(LinkedList *list, UndoSystem *us, unsigned int id) {
    int pos = find_liver_position(list, id);
    if (pos == -1) {
        printf("Resident with ID %u not found.\n", id);
        return;
    }

    Liver *old = get_at_list(list, pos);
    Liver backup_old = *old;

    Liver new_liver = *old;

    getchar();
    char input[128];

    printf("Surname [%s]: ", old->surname);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        input[strcspn(input, "\n")] = 0;
        if (!is_valid_name(input)) {
            printf("Invalid surname.\n");
            return;
        }
        strcpy(new_liver.surname, input);
    }

    printf("Name [%s]: ", old->name);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        input[strcspn(input, "\n")] = 0;
        if (!is_valid_name(input)) {
            printf("Invalid name.\n");
            return;
        }
        strcpy(new_liver.name, input);
    }

    printf("Patronymic [%s]: ", old->patronymic);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        input[strcspn(input, "\n")] = 0;
        strcpy(new_liver.patronymic, input);
    }

    printf("Birth date [%02d.%02d.%04d] (dd mm yyyy): ",
           old->birth.day, old->birth.month, old->birth.year);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        Date new_date;
        if (sscanf(input, "%d %d %d", &new_date.day, &new_date.month, &new_date.year) == 3) {
            if (!is_valid_date(&new_date)) {
                printf("Invalid date.\n");
                return;
            }
            new_liver.birth = new_date;
        }
    }

    printf("Sex [%c] (M/W): ", old->sex);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        char s = toupper(input[0]);
        if (s != 'M' && s != 'W') {
            printf("Invalid sex.\n");
            return;
        }
        new_liver.sex = s;
    }

    printf("Income [%.2lf]: ", old->income);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        double inc;
        if (sscanf(input, "%lf", &inc) != 1 || inc < 0) {
            printf("Invalid income.\n");
            return;
        }
        new_liver.income = inc;
    }

    delete_at_list(list, pos);

    Liver *new_copy = malloc(sizeof(Liver));
    *new_copy = new_liver;

    size_t new_pos = find_insert_position(list, &new_copy->birth);
    insert_at_list(list, new_pos, new_copy);

    Liver *old_copy = malloc(sizeof(Liver));
    *old_copy = backup_old;

    push_undo_operation(us, OP_MODIFY, pos, old_copy, new_copy);

    printf("Data modified.\n");
}

void undo_modifications(LinkedList *list, UndoSystem *us) {
    if (us->modification_count == 0) {
        printf("No operations to undo.\n");
        return;
    }

    int undo_count = us->modification_count / 2;
    if (undo_count == 0)
        undo_count = 1;

    printf("Undoing %d operations...\n", undo_count);

    for (int i = 0; i < undo_count; i++) {
        UndoOperation *op = (UndoOperation*)pop_stack(&us->undo_stack);
        if (!op) break;

        switch (op->type) {
        case OP_ADD: {
            int pos = find_liver_position(list, op->liver_data->id);
            if (pos != -1) {
                delete_at_list(list, pos);
                printf("Undone addition of ID %u\n", op->liver_data->id);
            }
        } break;

        case OP_DELETE: {
            Liver *l_copy = malloc(sizeof(Liver));
            *l_copy = *op->liver_data;

            size_t pos = find_insert_position(list, &l_copy->birth);
            insert_at_list(list, pos, l_copy);
            printf("Undone removal of ID %u\n", op->liver_data->id);
        } break;

        case OP_MODIFY: {
            int pos = find_liver_position(list, op->liver_data->id);
            if (pos != -1)
                delete_at_list(list, pos);

            Liver *old_copy = malloc(sizeof(Liver));
            *old_copy = *op->liver_data;

            size_t pos2 = find_insert_position(list, &old_copy->birth);
            insert_at_list(list, pos2, old_copy);

            printf("Undone modification of ID %u\n", op->liver_data->id);
        } break;
        }

        if (op->liver_data) free(op->liver_data);
        if (op->old_data) free(op->old_data);
        free(op);

        us->modification_count--;
    }

    printf("Undo completed. Remaining operations: %d\n",
           us->modification_count);
}

void display_all(const LinkedList *list) {
    if (list->size == 0) {
        printf("List is empty.\n");
        return;
    }

    printf("Total records: %zu\n", list->size);
    printf("=================================================================\n");
    printf("ID | Surname | Name | Patronymic | Date | Sex | Income\n");
    printf("=================================================================\n");

    Node *cur = list->head;
    while (cur) {
        Liver *l = cur->data;
        printf("%u | %s %s %s | %02d.%02d.%04d | %c | %.2lf\n",
               l->id, l->surname, l->name, l->patronymic,
               l->birth.day, l->birth.month, l->birth.year,
               l->sex, l->income);
        cur = cur->next;
    }
    printf("=================================================================\n");
}

void print_menu() {
    printf("\n=== Menu ===\n");
    printf("1. Show all residents\n");
    printf("2. Search by surname\n");
    printf("3. Search by ID\n");
    printf("4. Add resident\n");
    printf("5. Modify data\n");
    printf("6. Remove resident\n");
    printf("7. Save to file\n");
    printf("8. Undo changes\n");
    printf("9. Exit\n");
    printf("Choose action: ");
}