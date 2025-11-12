#include "include/functions.h"
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <stddef.h>
#include <stdio.h>


int main() {
    printf("\033[3;35m      === Testing Memory and String Functions ===\033[0m\n");
    
    printf("\033[1;36m=== 1. memchr: ===\033[0m\n");
    {
        char str[] = "anbbsbdbsdb123jgfr";
        int c = 'r';
        int n = 18; // Reduced from 22 to match actual string length
        char *result1 = memchr(str, c, n);
        if (result1) {
            printf("    In first %d bytes of string '%s' character '%c' is found on position %ld\n", n, str, c, result1 - str);
        } else {
            printf("    In first %d bytes of string '%s' character '%c' is not found\n", n, str, c);
        }

        n = 5;
        c = '2';
        char *result2 = memchr(str, c, n);
        if (result2) {
            printf("    In first %d bytes of string '%s' character '%c' is found on position %ld\n", n, str, c, result2 - str);
        } else {
            printf("    In first %d bytes of string '%s' character '%c' is not found\n", n, str, c);
        }

        char str2[] = "test";
        char *result3 = memchr(str2, c, n);
        if (result3) {
            printf("    In first %d bytes of string '%s' character '%c' is found on position %ld\n", n, str2, c, result3 - str2);
        } else {
            printf("    In first %d bytes of string '%s' character '%c' is not found\n", n, str2, c);
        }

    }
    
    printf("\033[1;36m\n=== 2. memcmp: ===\033[0m\n");    
    {
        char str1[20] = "1a0a0fhdf1   g"; 
        char str2[20] = "1a0a045zx gh"; 
        int n = 6;
        int result = memcmp(str1, str2, n);
        printf("   memcmp(%s, %s, %d) = %d\n", str1, str2, n, result); 
        n = 15; 
        int result1 = memcmp(str1, str2, n);
        printf("   memcmp(%s, %s, %d) = %d\n", str1, str2, n, result1); 
    }
    
    printf("\033[1;36m\n=== 3. memcpy: ===\033[0m\n");    
    {
        char src[] = "ababa00 string00gbfgr";
        char dest[50] = "gfhh";
        memcpy(dest, src, 20);
        printf("   Source: %s\n", src);
        printf("   Destination: %s\n", dest);
    }
    
    printf("\033[1;36m\n=== 4. memset: ===\033[0m\n");    
    {
        char buffer[30] = "123  h456 ghjj jfjd4";
        int c = 'A'; int n = 8;
        memset(buffer, c, n);
        printf("   After memset with '%c' for %d symbols: %s\n", c, n, buffer); 
    }
    
    printf("\033[1;36m\n=== 5. strncat: ===\033[0m\n");    
    {
        char dest[50] = "Hellooooo";
        char src[] = " , World!";
        int n = 12;
        printf("   Before strncat: Dest: %s, Src: %s\n", dest, src);
        strncat(dest, src, n);
        printf("   After strncat (%d symbols): %s\n", n, dest); 
    }
    
    printf("\033[1;36m\n=== 6. strchr: ===\033[0m\n");    
    {
        char str[] = "Hello, World!";
        int c = 'H';
        char *result = strchr(str, c);
        if (result) {
            printf("   First %c found at position: %ld, substring: %s\n", c, result - str, result);
        } else {
            printf("Could not find anything\n");
        }
    }
    
    printf("\033[1;36m\n=== 7. strncmp: ===\033[0m\n");    
    {
        char str1[20] = "aaabbbT fjj gf"; 
        char str2[20] = "aaabbb7";      
        char str3[20] = "aaabbffdfghgf12"; 
        int n = 15; 
        int result = strncmp(str1, str2, n);
        printf("   strncmp('%s', '%s', %d) = %d\n", str1, str2, n, result); 
        n = 5;
        result = strncmp(str1, str2, n);
        printf("   strncmp('%s', '%s', %d) = %d\n", str1, str2, n, result); 

        n = 15;
        result = strncmp(str2, str3, n);
        printf("   strncmp('%s', '%s', %d) = %d\n", str2, str3, n, result); 
    }

    printf("\033[1;36m\n=== 8. strncpy: ===\033[0m\n");    
    {
        char src[] = "Hello, fellows!";
        char dest[11] = "aba";
        int n = 10;
        printf("   Source: %s, dest: %s\n", src, dest);
        strncpy(dest, src, n);
        dest[10] = '\0';
        printf("   Result (first %d chars): %s\n", n, dest); 
    }
    
    printf("\033[1;36m\n=== 9. strcspn: ===\033[0m\n");    
    {
        char str1[] = "wertyuik12fghj7sdfgh734";
        char str2[] = "1234567";
        size_t result = strcspn(str1, str2);
        printf("    strcspn('%s', '%s') = %zu\n", str1, str2, result);
        char str3[] = "1234567";
        size_t result1 = strcspn(str2, str3);
        printf("    strcspn('%s', '%s') = %zu\n", str3, str3, result1);
    }
    
    printf("\033[1;36m\n=== 10. strerror: ===\033[0m\n");
    {
        int errnum = EFAULT;
        printf("   System strerror('%d'): %s\n", errnum, strerror(errnum));
    }
    
    printf("\033[1;36m\n=== 11. strlen: ===\033[0m\n");    
    {
        char str[] = "Hello, Martians!";
        size_t result = strlen(str);
        printf("   strlen('%s') = %zu\n", str, result);
    }
    
    printf("\033[1;36m\n=== 12. strpbrk: ===\033[0m\n");    
    {
        char str1[] = "Hello, World!";
        char str2[] = "!LLjf";
        char *result = strpbrk(str1, str2);
        if (result) {
            printf("   First symbol of str1: '%s' that is not in str2: '%s' found at position: %ld, character: %c\n", str1, str2, result - str1, *result);
        }
    }

    printf("\033[1;36m\n=== 13. strrchr: ===\033[0m\n");    
    {
        char str[] = "Abababababababcgd 456d";
        int c = 'a';
        char *result = strrchr(str, c);
        if (result) {
            printf("   Last '%c' found in string '%s' at position '%ld'\n", c, str, result - str);
        } 
    }
    
    printf("\033[1;36m\n=== 14. strstr: ===\033[0m\n");    
    {
        char haystack[] = "aboba";
        char needle[] = "bo";
        char *result = strstr(haystack, needle);
        if (result) {
            printf("   Found '%s' in string '%s' at position '%ld'\n", needle, haystack, result - haystack);
        }
    }
    
    printf("\033[1;36m\n=== 15. strtok: ===\033[0m\n");
    {
        char str[] = "Hello.World:Test ,aboba, pomogite";
        printf("String: %s\n", str);
        char *token = strtok(str, ",.:");
        int count = 1;
        printf("   Tokens:\n");
        while (token != NULL) {
            printf("   %d: %s\n", count++, token);
            token = strtok(NULL, ",.:");
        }
    }
    
    return 0;
}