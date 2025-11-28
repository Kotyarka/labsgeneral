#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/functions.h"

void test_list_functions() {
    printf("Testing list functions...\n");
    
    LinkedList list = create_list();
    assert(list.head == NULL);
    assert(list.tail == NULL);
    assert(list.size == 0);
    
    Liver liver1 = {1, "Smith", "John", "A", {15, 5, 1980}, 'M', 2500.50};
    Liver liver2 = {2, "Johnson", "Mary", "B", {20, 8, 1975}, 'W', 3000.75};
    Liver liver3 = {3, "Williams", "Mike", "C", {10, 3, 1990}, 'M', 2000.25};
    
    Liver *l1 = malloc(sizeof(Liver));
    Liver *l2 = malloc(sizeof(Liver));
    Liver *l3 = malloc(sizeof(Liver));
    *l1 = liver1;
    *l2 = liver2;
    *l3 = liver3;
    
    push_back_list(&list, l1);
    assert(list.size == 1);
    assert(list.head != NULL);
    assert(list.tail != NULL);
    assert(list.head->data->id == 1);
    
    push_front_list(&list, l2);
    assert(list.size == 2);
    assert(list.head->data->id == 2);
    assert(list.tail->data->id == 1);
    
    insert_at_list(&list, 1, l3);
    assert(list.size == 3);
    assert(get_at_list(&list, 1)->id == 3);
    
    Liver* popped = pop_front_list(&list);
    assert(popped->id == 2);
    assert(list.size == 2);
    assert(list.head->data->id == 3);
    free(popped);
    
    popped = pop_back_list(&list);
    assert(popped->id == 1);
    assert(list.size == 1);
    assert(list.tail->data->id == 3);
    free(popped);
    
    // Освобождаем оставшийся элемент перед удалением списка
    popped = pop_back_list(&list);
    free(popped);
    
    assert(list.size == 0);
    assert(list.head == NULL);
    assert(list.tail == NULL);
    
    erase_list(&list);
    printf("List functions test passed!\n");
}

void test_validation_functions() {
    printf("Testing validation functions...\n");
    
    assert(is_valid_name("John") == 1);
    assert(is_valid_name("Mary") == 1);
    assert(is_valid_name("") == 0);
    assert(is_valid_name("John123") == 0);
    assert(is_valid_name("John Doe") == 0);
    
    Date valid_date = {15, 5, 1980};
    Date invalid_date_day = {32, 5, 1980};
    Date invalid_date_month = {15, 13, 1980};
    Date invalid_date_year = {15, 5, 1800};
    
    assert(is_valid_date(&valid_date) == 1);
    assert(is_valid_date(&invalid_date_day) == 0);
    assert(is_valid_date(&invalid_date_month) == 0);
    assert(is_valid_date(&invalid_date_year) == 0);
    
    Date date1 = {10, 1, 2000};
    Date date2 = {10, 1, 2000};
    Date date3 = {15, 1, 2000};
    Date date4 = {10, 2, 2000};
    Date date5 = {10, 1, 2001};
    
    assert(compare_dates(&date1, &date2) == 0);
    assert(compare_dates(&date1, &date3) < 0);
    assert(compare_dates(&date3, &date1) > 0);
    assert(compare_dates(&date1, &date4) < 0);
    assert(compare_dates(&date1, &date5) < 0);
    
    printf("Validation functions test passed!\n");
}

void test_undo_system() {
    printf("Testing undo system...\n");

    UndoSystem us;
    init_undo_system(&us);

    LinkedList list = create_list();

    Liver sample = {1, "Undo", "Test", "User", {1,1,2000}, 'M', 1000};
    Liver *copy = malloc(sizeof(Liver));
    *copy = sample;

    // Добавление операции
    push_undo_operation(&us, OP_ADD, 0, copy, NULL);
    free(copy); // Освобождаем исходную копию, так как внутри функции сделали дубликат

    assert(us.modification_count == 1);
    assert(us.undo_stack.size == 1);

    // Очистка undo-системы
    clear_undo_system(&us);
    assert(us.modification_count == 0);
    assert(us.undo_stack.size == 0);

    erase_list(&list);
    printf("Undo system test passed!\n");
}

void test_position_functions() {
    printf("Testing position functions...\n");
    
    LinkedList list = create_list();
    
    Liver liver1 = {1, "A", "A", "A", {1, 1, 1970}, 'M', 1000.0};
    Liver liver2 = {2, "B", "B", "B", {1, 1, 1980}, 'W', 2000.0};
    Liver liver3 = {3, "C", "C", "C", {1, 1, 1990}, 'M', 3000.0};
    
    Liver *l1 = malloc(sizeof(Liver));
    Liver *l2 = malloc(sizeof(Liver));
    Liver *l3 = malloc(sizeof(Liver));
    *l1 = liver1;
    *l2 = liver2;
    *l3 = liver3;
    
    push_back_list(&list, l1);
    push_back_list(&list, l2);
    push_back_list(&list, l3);
    
    assert(find_liver_position(&list, 1) == 0);
    assert(find_liver_position(&list, 2) == 1);
    assert(find_liver_position(&list, 3) == 2);
    assert(find_liver_position(&list, 999) == -1);
    
    Date older_date = {1, 1, 1960};
    Date middle_date = {1, 1, 1975};
    Date younger_date = {1, 1, 2000};
    
    assert(find_insert_position(&list, &older_date) == 0);
    assert(find_insert_position(&list, &middle_date) == 1);
    assert(find_insert_position(&list, &younger_date) == 3);
    
    // Освобождаем все элементы перед удалением списка
    while (list.size > 0) {
        Liver *popped = pop_back_list(&list);
        free(popped);
    }
    
    erase_list(&list);
    printf("Position functions test passed!\n");
}

void test_stack_functions() {
    printf("Testing stack functions...\n");
    
    LinkedList stack = create_list();
    
    Liver liver1 = {1, "Stack", "Test1", "A", {1, 1, 2000}, 'M', 1000.0};
    Liver liver2 = {2, "Stack", "Test2", "B", {1, 1, 2000}, 'W', 2000.0};
    
    Liver *l1 = malloc(sizeof(Liver));
    Liver *l2 = malloc(sizeof(Liver));
    *l1 = liver1;
    *l2 = liver2;
    
    push_stack(&stack, l1);
    assert(stack.size == 1);
    assert(peek_stack(&stack)->id == 1);
    
    push_stack(&stack, l2);
    assert(stack.size == 2);
    assert(peek_stack(&stack)->id == 2);
    
    Liver* popped = pop_stack(&stack);
    assert(popped->id == 2);
    assert(stack.size == 1);
    free(popped);
    
    popped = pop_stack(&stack);
    assert(popped->id == 1);
    assert(stack.size == 0);
    free(popped);
    
    assert(pop_stack(&stack) == NULL);
    assert(peek_stack(&stack) == NULL);
    
    erase_list(&stack);
    printf("Stack functions test passed!\n");
}

void test_list_equality() {
    printf("Testing list equality...\n");
    
    LinkedList list1 = create_list();
    LinkedList list2 = create_list();
    
    Liver liver = {1, "Test", "Equal", "List", {1, 1, 2000}, 'M', 1000.0};
    Liver *l1 = malloc(sizeof(Liver));
    Liver *l2 = malloc(sizeof(Liver));
    *l1 = liver;
    *l2 = liver;
    
    push_back_list(&list1, l1);
    push_back_list(&list2, l2);
    
    assert(is_equal_list(&list1, &list2) == 1);
    
    Liver *l3 = malloc(sizeof(Liver));
    *l3 = liver;
    l3->id = 2;
    push_back_list(&list2, l3);
    
    assert(is_equal_list(&list1, &list2) == 0);
    
    // Освобождаем все элементы перед удалением списков
    while (list1.size > 0) {
        Liver *popped = pop_back_list(&list1);
        free(popped);
    }
    while (list2.size > 0) {
        Liver *popped = pop_back_list(&list2);
        free(popped);
    }
    
    erase_list(&list1);
    erase_list(&list2);
    printf("List equality test passed!\n");
}

void run_all_tests() {
    printf("Running all tests...\n\n");
    
    test_list_functions();
    test_validation_functions();
    test_undo_system();
    test_position_functions();
    test_stack_functions();
    test_list_equality();
    
    printf("\nAll tests passed successfully!\n");
}

int main() {
    run_all_tests();
    return 0;
}