#include "../include/include.h"

int main() {
    int results[3];

    errorCodes result = isFinitePresent(2, results, 3, 0.3333333333333333333, 0.25, 0.1);
    
    if (result == OK) {
        for (int i = 0; i < 3; i++) {
            printf("Number %d: %s\n", i+1, results[i] ? "finite" : "infinite");
        }
    } else if (result == BAD_BASE) {
        printf("Incorrect base");
    } else if (result == BAD_INPUT) {
        printf("Incorrect input of one of the numbers");
    } else if (result == MALLOC_ERROR) {
        printf("Error occured while allocation memory for the list");
    }
    
    return 0;
}