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

void save_to_file(const LinkedList *list, const char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (!file) {
        printf("Ошибка создания файла %s\n", filename);
        return;
    }
    
    Node *current = list->head;
    while (current != NULL) {
        Liver *liver = current->data;
        fprintf(file, "%u %s %s %s %d %d %d %c %.2lf\n",
                liver->id, liver->surname, liver->name, liver->patronymic,
                liver->birth.day, liver->birth.month, liver->birth.year,
                liver->sex, liver->income);
        current = current->next;
    }
    
    fclose(file);
    printf("Данные сохранены в файл %s\n", filename);
}

void search_by_id(const LinkedList *list, unsigned int id) {
    Node *current = list->head;
    
    while (current != NULL) {
        if (current->data->id == id) {
            Liver *l = current->data;
            printf("Найден житель: ID: %u, %s %s %s, %02d.%02d.%d, %c, Доход: %.2lf\n",
                   l->id, l->surname, l->name, l->patronymic,
                   l->birth.day, l->birth.month, l->birth.year,
                   l->sex, l->income);
            return;
        }
        current = current->next;
    }
    
    printf("Житель с ID %u не найден\n", id);
} // naher ne nado

void modify_liver(LinkedList *list, HistoryManager *history, unsigned int id) {
    Node *current = list->head;
    size_t index = 0;
    
    // Поиск жителя
    while (current != NULL && current->data->id != id) {
        current = current->next;
        index++;
    }
    
    if (current == NULL) {
        printf("Житель с ID %u не найден\n", id);
        return;
    }
    
    Liver *old_liver = current->data;
    Liver *new_liver = malloc(sizeof(Liver));
    *new_liver = *old_liver; // Копируем старые данные
    
    printf("Изменение данных жителя (ID: %u):\n", id);
    printf("Введите новые данные (оставьте пустым для сохранения текущего значения):\n");
    
    char input[100];
    
    // Фамилия
    printf("Фамилия [%s]: ", old_liver->surname);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        input[strcspn(input, "\n")] = 0;
        if (is_valid_name(input)) {
            strcpy(new_liver->surname, input);
        } else {
            printf("Неверная фамилия\n");
            free(new_liver);
            return;
        }
    }
    
    // Имя
    printf("Имя [%s]: ", old_liver->name);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        input[strcspn(input, "\n")] = 0;
        if (is_valid_name(input)) {
            strcpy(new_liver->name, input);
        } else {
            printf("Неверное имя\n");
            free(new_liver);
            return;
        }
    }
    
    // Отчество
    printf("Отчество [%s]: ", old_liver->patronymic);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        input[strcspn(input, "\n")] = 0;
        strcpy(new_liver->patronymic, input);
    }
    
    // Дата рождения
    printf("Дата рождения [%02d.%02d.%d] (в формате дд мм гггг): ", 
           old_liver->birth.day, old_liver->birth.month, old_liver->birth.year);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        Date new_date;
        if (sscanf(input, "%d %d %d", &new_date.day, &new_date.month, &new_date.year) == 3) {
            if (is_valid_date(&new_date)) {
                new_liver->birth = new_date;
            } else {
                printf("Неверная дата\n");
                free(new_liver);
                return;
            }
        }
    }
    
    // Пол
    printf("Пол [%c] (M/W): ", old_liver->sex);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        char new_sex = toupper(input[0]);
        if (new_sex == 'M' || new_sex == 'W') {
            new_liver->sex = new_sex;
        } else {
            printf("Неверный пол\n");
            free(new_liver);
            return;
        }
    }
    
    // Доход
    printf("Доход [%.2lf]: ", old_liver->income);
    if (fgets(input, sizeof(input), stdin) && strlen(input) > 1) {
        double new_income;
        if (sscanf(input, "%lf", &new_income) == 1 && new_income >= 0) {
            new_liver->income = new_income;
        } else {
            printf("Неверный доход\n");
            free(new_liver);
            return;
        }
    }
    
    // Удаляем старую запись и вставляем новую в правильную позицию
    delete_at_list(list, index);
    
    // Находим правильную позицию для новой записи
    Node *curr = list->head;
    size_t new_index = 0;
    while (curr != NULL) {
        if (compare_dates(&new_liver->birth, &curr->data->birth) > 0) {
            break;
        }
        curr = curr->next;
        new_index++;
    }
    
    insert_at_list(list, new_index, new_liver);
    history->modification_count++;
    
    printf("Данные успешно изменены\n");
}

void add_liver(LinkedList *list, HistoryManager *history) {
    Liver *new_liver = malloc(sizeof(Liver));
    
    printf("Добавление нового жителя:\n");
    
    // ID
    printf("Введите ID: ");
    scanf("%u", &new_liver->id);
    getchar(); // consume newline
    
    // Проверка уникальности ID
    Node *current = list->head;
    while (current != NULL) {
        if (current->data->id == new_liver->id) {
            printf("Ошибка: ID %u уже существует\n", new_liver->id);
            free(new_liver);
            return;
        }
        current = current->next;
    }
    
    // Фамилия
    printf("Введите фамилию: ");
    fgets(new_liver->surname, sizeof(new_liver->surname), stdin);
    new_liver->surname[strcspn(new_liver->surname, "\n")] = 0;
    if (!is_valid_name(new_liver->surname)) {
        printf("Неверная фамилия\n");
        free(new_liver);
        return;
    }
    
    // Имя
    printf("Введите имя: ");
    fgets(new_liver->name, sizeof(new_liver->name), stdin);
    new_liver->name[strcspn(new_liver->name, "\n")] = 0;
    if (!is_valid_name(new_liver->name)) {
        printf("Неверное имя\n");
        free(new_liver);
        return;
    }
    
    // Отчество
    printf("Введите отчество: ");
    fgets(new_liver->patronymic, sizeof(new_liver->patronymic), stdin);
    new_liver->patronymic[strcspn(new_liver->patronymic, "\n")] = 0;
    
    // Дата рождения
    printf("Введите дату рождения (дд мм гггг): ");
    scanf("%d %d %d", &new_liver->birth.day, &new_liver->birth.month, &new_liver->birth.year);
    getchar(); // consume newline
    if (!is_valid_date(&new_liver->birth)) {
        printf("Неверная дата\n");
        free(new_liver);
        return;
    }
    
    // Пол
    printf("Введите пол (M/W): ");
    scanf("%c", &new_liver->sex);
    getchar(); // consume newline
    new_liver->sex = toupper(new_liver->sex);
    if (new_liver->sex != 'M' && new_liver->sex != 'W') {
        printf("Неверный пол\n");
        free(new_liver);
        return;
    }
    
    // Доход
    printf("Введите доход: ");
    scanf("%lf", &new_liver->income);
    getchar(); // consume newline
    if (new_liver->income < 0) {
        printf("Неверный доход\n");
        free(new_liver);
        return;
    }
    
    // Вставка в упорядоченный список
    Node *curr = list->head;
    size_t index = 0;
    while (curr != NULL) {
        if (compare_dates(&new_liver->birth, &curr->data->birth) > 0) {
            break;
        }
        curr = curr->next;
        index++;
    }
    
    insert_at_list(list, index, new_liver);
    history->modification_count++;
    
    printf("Житель успешно добавлен\n");
}

// Функция для удаления жителя
void remove_liver(LinkedList *list, HistoryManager *history, unsigned int id) {
    Node *current = list->head;
    size_t index = 0;
    
    while (current != NULL && current->data->id != id) {
        current = current->next;
        index++;
    }
    
    if (current == NULL) {
        printf("Житель с ID %u не найден\n", id);
        return;
    }
    
    delete_at_list(list, index);
    history->modification_count++;
    
    printf("Житель с ID %u удален\n", id);
}