#include "./include/functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include <unistd.h>

errorCodes testFunc() {
    overfprintf(stdout, "155 in Roman: %Ro\n", 155);
    overfprintf(stdout, "-1124 in Roman: %Ro\n", -1124);
    overfprintf(stdout, "150 in Zerkendorf repr: %Zr\n", 150);
    overfprintf(stdout, "In 2 base 124: %CV\n", 124, 2);
    overfprintf(stdout, "In 10 base -52: %CV\n", -52, 10);
    overfprintf(stdout, "In small 12 base 124: %Cv\n", 124, 12);
    overfprintf(stdout, "In BIG 12 base 124: %CV\n", 124, 12);
    overfprintf(stdout, "In 2 base 124: %CV\n", 124, 2);
    overfprintf(stdout, "b123 in 13 base = %to in 10 base\n", "b123", 13);
    overfprintf(stdout, "B321 in 13 base = %TO in 10 base\n", "B321", 13);
    overfprintf(stdout, "Dump of int 1: %mi\n", 1);
    overfprintf(stdout, "Dump of uint INT_MAX + 2: %mu\n", ((unsigned int)INT_MAX + 2));
    overfprintf(stdout, "Dump of double 1.1: %md\n", (double)1.1);
    overfprintf(stdout, "Dump of float  1.2: %mf\n", (float)1.1);
    overfprintf(stdout, "Default flags %d %s %.15f\n", 15, "hello", 1.23);
    char a[128]; 
    oversprintf(a , "test string", 5);
    printf("%s\n", a);
    oversprintf(a, "Default flags %d %s %.15f\n", 15, "hello", 1.23);
    printf("%s\n", a);  
    oversprintf(a, "5023 in Roman > 4000: %Ro\n", 5023);
    printf("%s\n", a);     
    oversprintf(a, "In 2 base 124: %CV", 124, 2);
    printf("%s\n", a);
    oversprintf(a, "In 10 base -52: %CV", -52, 10);
    printf("%s\n", a);  
    oversprintf(a, "In small 12 base 124: %Cv", 124, 12);
    printf("%s\n", a);  
    oversprintf(a, "In BIG 12 base 124: %CV", 124, 12);
    printf("%s\n", a);  
    oversprintf(a, "In 2 base 124: %CV", 124, 2);
    printf("%s\n", a);   
    return OK;
}

int main() {
    testFunc();
    return OK;
}