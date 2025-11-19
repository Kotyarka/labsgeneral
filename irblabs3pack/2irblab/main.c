#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/functions.h"

VECTOR_DEFINE(int)

int int_copy(int value) {
    return value;
}

void int_delete(int value) {
    (void)value;
}

int main() {
    printf("Vector hand testing\n");

    Vector v = create_vector(5, int_copy, int_delete);
    
    for (int i = 0; i < 10; i++) {
        push_back_vector(&v, i * 10);
    }
    
    printf("Vector contents:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("v[%zu] = %d\n", i, get_at_vector(&v, i));
    }
    
    printf("Vector size: %zu, capacity: %zu\n", v.size, v.capacity);
    
    delete_at_vector(&v, 0);
    delete_at_vector(&v, 3);
    
    printf("\nAfter deletion:\n");
    for (size_t i = 0; i < v.size; i++) {
        printf("v[%zu] = %d\n", i, get_at_vector(&v, i));
    }
    
    erase_vector(&v);
    
    return 0;
}