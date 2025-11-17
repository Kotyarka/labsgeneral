#include "../include/include.h"

int add(int a, int b){
    int carry;
    while (b != 0){
        carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

int strSize(const char *str) {
    if (!str) {
        return 0;
    }
    int k = 0;
    while (str[k] != '\0') {
        k = add(k, 1);
    }
    return k;
}

errorCodes reverse(char* array){
    int i = 0;
    int b = add(strSize(array), -1);
    while (i < b){
        char t = array[i];
        array[i] = array[b];
        array[b] = t;
        i = add(i, 1);
        b = add(b, -1);
    }
    return OK;
}

errorCodes rightShift(char* array){
    int size = strSize(array);
    array[add(size, 1)] = '\0';
    for (int i = size; i > 0; i = add(i, -1)){
        array[i] = array[add(i, -1)];
    }
    return OK;
}

errorCodes convertToBase(int decimal, char* result, int r){
    if (!result) {
        return POINTER_ERROR;
    }
    if (decimal == 0){
        result[0] = '0';
        result[1] = '\0';
        return OK;
    }
    int a  = decimal;
    int mask = 1;
    for (int i = 0; i < r - 1; i = add(i, 1)){
        mask = mask << 1;
        mask = mask | 1;
    }
    int sign = 0;
    if (decimal < 0){
        a = add(~decimal, 1);
        sign = 1;
    }
    char* alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
    for (int i = 0; i <= 31 && a > 0; i = add(i, 1)){
        result[i] = alphabet[a & mask];
        a = a >> r;
    }
    reverse(result);
    if (sign){
        rightShift(result);
        result[0] = '-';
    }
    return OK;
}
