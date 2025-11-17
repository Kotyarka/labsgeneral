#include "../include/include.h"

int main() {
    char result[34] = {0};

    convertToBase(127, result, 4);
    printf("127 with 2**4 = 16 base is %s", result);

    return 0;
}