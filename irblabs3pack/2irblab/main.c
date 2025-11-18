#include <stdio.h>

int copy_int(int value) {
    return value;
}

void delete_int(int value) {
    (void)value;
}

int main() {
    IntVector int_vec = IntVector_create(10, copy_int, delete_int);
}