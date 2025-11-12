#include "../include/functions.h"
#include "../include/errors_macro.h"
#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

void * memchr(const void *str, int c, size_t n) {
    if (n > strlen((const char*)str)) {
        n = strlen((const char*)str);
    }

    unsigned char * ptr = (unsigned char *)str;
    unsigned char ch = (unsigned char)c; 
    
    for (size_t i = 0; i < n; ++i) {
        if (*ptr == ch) {
            return (void*)ptr; 
        }
        ++ptr;
    }

    return NULL;
}

int memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char * ptr1 = (const unsigned char*)str1;
    const unsigned char * ptr2 = (const unsigned char*)str2;

    for (size_t i = 0; i < n; ++i) {
        if (ptr1[i] > ptr2[i]) {
            return 1;
        }
        if (ptr1[i] < ptr2[i]) {
            return -1;
        }
    }
    return 0;
}

void * memcpy(void *dest, const void *src, size_t n) {
    unsigned char * srcPtr = (unsigned char*)src;
    unsigned char * destPtr = (unsigned char*)dest;

    for (size_t i = 0; i < n; ++i) {
        *destPtr = *srcPtr;
        ++destPtr;
        ++srcPtr;
    }
    
    return dest; 
}

void *memset(void *str, int c, size_t n) {
    unsigned char * ptr = (unsigned char *) str;
    unsigned char ch = (unsigned char) c;

    for (size_t i = 0; i < n; ++i) {
        *ptr = ch;
        ++ptr;
    }
    return str;
}

char *strncat(char *dest, const char *src, size_t n) {
    if (n > strlen(src)) {
        n = strlen(src);
    }

    const char * ptrSrc = src;
    size_t len = strlen(dest);

    for (size_t i = 0; i < n; ++i) {
        dest[len + i] = ptrSrc[i];
    }
    dest[len + n] = '\0';
    
    return dest;
}

char *strchr(const char *str, int c) {
    const char * p = str;

    while (*p) {
        if (*p == c) {
            return (char*)p; 
        }
        ++p;
    }
    return NULL;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    const char * ptr1 = str1;
    const char * ptr2 = str2;

    for (size_t i = 0; i < n && *ptr1 && *ptr2; ++i) {
        if (*ptr1 > *ptr2) {
            return 1;
        }
        if (*ptr1 < *ptr2) {
            return -1;
        }
        ++ptr1;
        ++ptr2;
    }
    
    if (n > 0) {
        if (*ptr1 && !*ptr2) return 1;
        if (!*ptr1 && *ptr2) return -1;
    }
    return 0;
}

char *strncpy(char *dest, const char *src, size_t n) {
    char * ptrDest = dest;
    const char * ptrSrc = src;

    for (size_t i = 0; i < n && *ptrSrc; ++i) {
        *ptrDest = *ptrSrc;
        ++ptrDest;
        ++ptrSrc;
    }
    
    for (size_t i = strlen(src); i < n; ++i) {
        *ptrDest = '\0';
        ++ptrDest;
    }
    
    return dest;
}

size_t strcspn(const char *str1, const char *str2) {
    const char * ptr = str1;
    size_t count = 0;
    bool WasIn = false;
    
    while (*ptr) {
        if (!strchr(str2, *ptr)) {
            WasIn = true;
            ++count;
        } else {
            if (WasIn) {
                return count;
            }
        }
        ++ptr;
    }
    return count;
}

char *strerror(int errnum) {
    if (errnum < 0 || errnum > MAX_ERRNO) {
        return "Unknown error";
    }
    const char *msg = ERROR_MESSAGES[errnum];
    return (char*)msg;
}

size_t strlen(const char *str) {
    size_t len = 0;
    const char * ptr = str;
    while (*ptr) {
        ++len;
        ++ptr;
    }
    return len;
}

char *strpbrk(const char *str1, const char *str2) {
    const char * ptr = str1;

    while (*ptr) {
        if (strchr(str2, *ptr)){
            return (char*)ptr; 
        }
        ++ptr;
    }
    return NULL;
}

char *strrchr(const char *str, int c) {
    const char * p = str + strlen(str);

    while (p >= str) {
        if (*p == c) {
            return (char*)p;
        } 
        --p;
    }
    return NULL;
}

char *strstr(const char *haystack, const char *needle) {
    if (strlen(needle) > strlen(haystack)) {
        return NULL; 
    }
    if (strlen(needle) == 0) {
        return (char*)haystack;
    }

    size_t needleLen = strlen(needle);
    size_t haystackLen = strlen(haystack);

    for (size_t i = 0; i <= haystackLen - needleLen; ++i) {
        if (strncmp(haystack + i, needle, needleLen) == 0) {
            return (char*)(haystack + i);
        }
    }
    return NULL;
}

bool isToken(int c, const char *delim) {
    const char *ptr = delim;
    while (*ptr) {
        if (*ptr == c) {
            return true;
        }
        ++ptr;
    }
    return false;
}

char *strtok(char *str, const char *delim) {
    static char *savePtr = NULL;
    char *tokenStart;

    if (str == NULL) {
        str = savePtr;
    }

    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0' && isToken(*str, delim)) {
        str++;
    }

    if (*str == '\0') {
        savePtr = NULL;
        return NULL;
    }

    tokenStart = str;

    while (*str != '\0') {
        if (isToken(*str, delim)) {
            *str = '\0';
            savePtr = str + 1;
            return tokenStart;
        }
        str++;
    }   

    savePtr = NULL;
    return tokenStart;
}