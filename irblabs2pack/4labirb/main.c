#include "./include/functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int roman = 0;
    char string[50];
    string[0] = '\0';
    int just_digit = 0;
    unsigned int zeck = 0; 
    int in_16_base = 0;
    int in_17_base = 0;
    float float_value = 0;
    
    printf("Enter: Roman_numeral String Integer Zeckendorf_repr HEX_uppercase HEX_lowercase Float\n");
    printf("Input: ");
    

    errorCodes result = overfscanf(stdin, "%Ro %s %d %Zr %CV %Cv %f", 
                                  &roman, string, &just_digit, &zeck, 
                                  &in_16_base, 16, &in_17_base, 17, &float_value);
    
    if (result == OK) {
        printf("\nParsing successful:\n");
        printf("Roman: %d\n", roman);
        printf("String: %s\n", string);
        printf("Digit: %d\n", just_digit);
        printf("Zeck: %u\n", zeck);
        printf("in 16 base: %d\n", in_16_base);
        printf("in 17 base: %d\n", in_17_base);
        printf("Float value: %f\n", float_value);
    } else {
        printf("\nParsing failed with error code: %d\n", result);
        
        printf("Partial results:\n");
        printf("Roman: %d\n", roman);
        printf("String: %s\n", string);
        printf("Digit: %d\n", just_digit);
        printf("Zeck: %u\n", zeck);
        printf("in 16 base: %d\n", in_16_base);
        printf("in 17 base: %d\n", in_17_base);
        printf("Float value: %f\n", float_value);
    }
    
    return 0;
}