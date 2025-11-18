#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_DEFINE(VECTOR_TYPE, VECTOR_NAME) \
typedef struct { \
    VECTOR_TYPE *data; \
    size_t size; \
    size_t capacity; \
    VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE); \
    void (*DeleteFunc)(VECTOR_TYPE); \ // почему в задании deletevoidptr?
} VECTOR_NAME; \
\
static VECTOR_NAME VECTOR_NAME##_create(size_t initial_capacity, \
                                        VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), \
                                        void (*DeleteFunc)(VECTOR_TYPE)) { \
    VECTOR_NAME v; \
    v.data = NULL; \
    v.size = 0; \
    v.capacity = 0; \
    v.CopyFunc = CopyFunc; \
    v.DeleteFunc = DeleteFunc; \
    \
    if (initial_capacity > 0) { \
        v.data = (VECTOR_TYPE*)malloc(initial_capacity * sizeof(VECTOR_TYPE)); \
        if (v.data) { \
            v.capacity = initial_capacity; \
        } \
    } \
    return v; \
} \
static void VECTOR_NAME##_erase(VECTOR_NAME *v) { \
    if (v && v->data && v->DeleteFunc) { \
        for (size_t i = 0; i < v->size; i++) { \
            v->DeleteFunc(v->data[i]); \
        } \
    } \
    if (v && v->data) { \
        free(v->data); \
        v->data = NULL; \
    } \
    if (v) { \
        v->size = 0; \
        v->capacity = 0; \
    } \
} \
\
void erase_vector(Vector *v);
int is_equal_vector(const Vector *v1, const Vector *v2);
void copy_vector(Vector *dest, const Vector *src);
Vector *copy_vector_new(const Vector *src);
void push_back_vector(Vector *v, VECTOR_TYPE value);
void delete_at_vector(Vector *v, size_t index);
VECTOR_TYPE get_at_vector(const Vector *v, size_t index);
delete_vector(Vector *v);
