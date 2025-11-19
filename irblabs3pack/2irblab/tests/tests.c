#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/functions.h"
VECTOR_DEFINE(int)

int CopyInt(int value) {
    return value;
}

void DeleteInt(int value) {
    (void)value;
}

void test_create_vector() {
    printf("Testing create_vector...\n");
    
    Vector v = create_vector(10, CopyInt, DeleteInt);
    assert(v.data != NULL);
    assert(v.size == 0);
    assert(v.capacity == 10);
    assert(v.CopyFunc == CopyInt);
    assert(v.DeleteFunc == DeleteInt);
    erase_vector(&v);
    
    Vector v2 = create_vector(0, NULL, NULL);
    assert(v2.data == NULL);
    assert(v2.size == 0);
    assert(v2.capacity == 0);
    assert(v2.CopyFunc == NULL);
    assert(v2.DeleteFunc == NULL);
    erase_vector(&v2);
    
    printf("create_vector tests passed!\n\n");
}

void test_push_back_vector() {
    printf("Testing push_back_vector...\n");
    
    Vector v = create_vector(2, CopyInt, DeleteInt);
    

    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    assert(v.size == 2);
    assert(v.capacity == 2);
    assert(v.data[0] == 10);
    assert(v.data[1] == 20);
    
    push_back_vector(&v, 30);
    assert(v.size == 3);
    assert(v.capacity == 4); 
    assert(v.data[0] == 10);
    assert(v.data[1] == 20);
    assert(v.data[2] == 30);
    
    push_back_vector(&v, 40);
    push_back_vector(&v, 50);
    assert(v.size == 5);
    assert(v.capacity == 8);
    assert(v.data[3] == 40);
    assert(v.data[4] == 50);
    
    erase_vector(&v);
    printf("push_back_vector tests passed!\n\n");
}

void test_get_at_vector() {
    printf("Testing get_at_vector...\n");
    
    Vector v = create_vector(5, CopyInt, DeleteInt);
    
    for (int i = 0; i < 5; i++) {
        push_back_vector(&v, i * 10);
    }
    
    assert(get_at_vector(&v, 0) == 0);
    assert(get_at_vector(&v, 1) == 10);
    assert(get_at_vector(&v, 2) == 20);
    assert(get_at_vector(&v, 3) == 30);
    assert(get_at_vector(&v, 4) == 40);
    
    int value = get_at_vector(&v, 10); 
    assert(value == 0); 
    

    value = get_at_vector(NULL, 0);
    assert(value == 0);
    
    erase_vector(&v);
    printf("get_at_vector tests passed!\n\n");
}

void test_delete_at_vector() {
    printf("Testing delete_at_vector...\n");
    
    Vector v = create_vector(5, CopyInt, DeleteInt);
    
    for (int i = 0; i < 5; i++) {
        push_back_vector(&v, i * 10);
    }
    
    delete_at_vector(&v, 2);
    assert(v.size == 4);
    assert(v.data[0] == 0);
    assert(v.data[1] == 10);
    assert(v.data[2] == 30);
    assert(v.data[3] == 40);
    
    delete_at_vector(&v, 0);
    assert(v.size == 3);
    assert(v.data[0] == 10);
    assert(v.data[1] == 30);
    assert(v.data[2] == 40);
    
    delete_at_vector(&v, 2);
    assert(v.size == 2);
    assert(v.data[0] == 10);
    assert(v.data[1] == 30);
    
    delete_at_vector(&v, 10);
    assert(v.size == 2);
    delete_at_vector(NULL, 0); 
    
    erase_vector(&v);
    printf("delete_at_vector tests passed!\n\n");
}

void test_copy_vector() {
    printf("Testing copy_vector...\n");
    
    Vector src = create_vector(5, CopyInt, DeleteInt);
    
    for (int i = 0; i < 5; i++) {
        push_back_vector(&src, i * 10);
    }
    
    // Тест 1: копирование в пустой вектор
    Vector dest = create_vector(0, CopyInt, DeleteInt);
    copy_vector(&dest, &src);
    
    assert(dest.size == src.size);
    assert(dest.capacity == src.capacity);
    for (size_t i = 0; i < src.size; i++) {
        assert(dest.data[i] == src.data[i]);
    }
    
    // Тест 2: копирование в непустой вектор (должен очиститься)
    push_back_vector(&dest, 100); // Добавляем лишний элемент
    copy_vector(&dest, &src);
    assert(dest.size == src.size);
    for (size_t i = 0; i < src.size; i++) {
        assert(dest.data[i] == src.data[i]);
    }
    
    // Тест 3: копирование NULL
    copy_vector(NULL, &src);
    copy_vector(&dest, NULL);
    
    erase_vector(&src);
    erase_vector(&dest);
    printf("copy_vector tests passed!\n\n");
}

void test_copy_vector_new() {
    printf("Testing copy_vector_new...\n");
    
    Vector src = create_vector(5, CopyInt, DeleteInt);
    
    // Заполняем исходный вектор
    for (int i = 0; i < 5; i++) {
        push_back_vector(&src, i * 10);
    }
    
    // Тест 1: создание копии
    Vector *copy = copy_vector_new(&src);
    assert(copy != NULL);
    assert(copy->size == src.size);
    assert(copy->capacity == src.capacity);
    assert(copy->CopyFunc == src.CopyFunc);
    assert(copy->DeleteFunc == src.DeleteFunc);
    
    for (size_t i = 0; i < src.size; i++) {
        assert(copy->data[i] == src.data[i]);
    }
    
    // Тест 2: копирование NULL
    Vector *null_copy = copy_vector_new(NULL);
    assert(null_copy == NULL);
    
    delete_vector(copy);
    erase_vector(&src);
    printf("copy_vector_new tests passed!\n\n");
}

void test_is_equal_vector() {
    printf("Testing is_equal_vector...\n");
    
    Vector v1 = create_vector(5, CopyInt, DeleteInt);
    Vector v2 = create_vector(5, CopyInt, DeleteInt);
    Vector v3 = create_vector(5, CopyInt, DeleteInt);
    
    // Заполняем векторы
    for (int i = 0; i < 5; i++) {
        push_back_vector(&v1, i * 10);
        push_back_vector(&v2, i * 10);
        push_back_vector(&v3, i * 20); // Другие значения
    }
    
    // Тест 1: одинаковые векторы
    assert(is_equal_vector(&v1, &v2) == 1);
    
    // Тест 2: разные векторы
    assert(is_equal_vector(&v1, &v3) == 0);
    
    // Тест 3: разные размеры
    delete_at_vector(&v2, 0);
    assert(is_equal_vector(&v1, &v2) == 0);
    
    // Тест 4: NULL векторы
    assert(is_equal_vector(NULL, &v1) == 0);
    assert(is_equal_vector(&v1, NULL) == 0);
    assert(is_equal_vector(NULL, NULL) == 0);
    
    // Тест 5: пустые векторы
    Vector empty1 = create_vector(0, CopyInt, DeleteInt);
    Vector empty2 = create_vector(0, CopyInt, DeleteInt);
    assert(is_equal_vector(&empty1, &empty2) == 1);
    
    erase_vector(&v1);
    erase_vector(&v2);
    erase_vector(&v3);
    erase_vector(&empty1);
    erase_vector(&empty2);
    printf("is_equal_vector tests passed!\n\n");
}

void test_erase_and_delete_vector() {
    printf("Testing erase_vector and delete_vector...\n");
    
    // Тест 1: erase_vector
    Vector v = create_vector(5, CopyInt, DeleteInt);
    for (int i = 0; i < 5; i++) {
        push_back_vector(&v, i * 10);
    }
    
    erase_vector(&v);
    assert(v.data == NULL);
    assert(v.size == 0);
    assert(v.capacity == 0);
    
    // Тест 2: delete_vector
    Vector *v_ptr = (Vector *)malloc(sizeof(Vector));
    *v_ptr = create_vector(3, CopyInt, DeleteInt);
    for (int i = 0; i < 3; i++) {
        push_back_vector(v_ptr, i * 5);
    }
    
    delete_vector(v_ptr);
    
    // Тест 3: erase_vector с NULL
    erase_vector(NULL); // Не должно падать
    
    printf("erase_vector and delete_vector tests passed!\n\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    // Тест 1: вектор без функций копирования/удаления
    Vector v = create_vector(3, NULL, NULL);
    push_back_vector(&v, 100);
    push_back_vector(&v, 200);
    assert(v.size == 2);
    assert(v.data[0] == 100);
    assert(v.data[1] == 200);
    
    // Проверяем, что get_at_vector работает без CopyFunc
    assert(get_at_vector(&v, 0) == 100);
    
    erase_vector(&v);
    
    // Тест 2: многократное добавление и удаление
    Vector v2 = create_vector(1, CopyInt, DeleteInt);
    for (int i = 0; i < 100; i++) {
        push_back_vector(&v2, i);
    }
    assert(v2.size == 100);
    assert(v2.capacity >= 100);
    
    while (v2.size > 0) {
        delete_at_vector(&v2, 0);
    }
    assert(v2.size == 0);
    
    erase_vector(&v2);
    
    printf("Edge cases tests passed!\n\n");
}

int main() {
    printf("Starting vector tests...\n\n");
    
    test_create_vector();
    test_push_back_vector();
    test_get_at_vector();
    test_delete_at_vector();
    test_copy_vector();
    test_copy_vector_new();
    test_is_equal_vector();
    test_erase_and_delete_vector();
    test_edge_cases();
    
    printf("All tests passed! ✓\n");
    return 0;
}