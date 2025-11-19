#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_DEFINE(VECTOR_TYPE)                                                                       \
    typedef struct                                                                                       \
    {                                                                                                    \
        VECTOR_TYPE *data;                                                                               \
        size_t size;                                                                                     \
        size_t capacity;                                                                                 \
        VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE);                                                            \
        void (*DeleteFunc)(VECTOR_TYPE);                                                                 \
                                                                                                         \
    } Vector;                                                                                            \
                                                                                                         \
    Vector create_vector(size_t initial_capacity,                                                        \
                         VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE),                                           \
                         void (*DeleteFunc)(VECTOR_TYPE))                                                \
    {                                                                                                    \
        Vector v;                                                                                        \
        v.data = NULL;                                                                                   \
        v.size = 0;                                                                                      \
        v.capacity = 0;                                                                                  \
        v.CopyFunc = CopyFunc;                                                                           \
        v.DeleteFunc = DeleteFunc;                                                                       \
                                                                                                         \
        if (initial_capacity > 0)                                                                        \
        {                                                                                                \
            v.data = (VECTOR_TYPE *)malloc(initial_capacity * sizeof(VECTOR_TYPE));                      \
            if (v.data)                                                                                  \
            {                                                                                            \
                v.capacity = initial_capacity;                                                           \
            }                                                                                            \
        }                                                                                                \
        return v;                                                                                        \
    }                                                                                                    \
    void erase_vector(Vector *v)                                                                         \
    {                                                                                                    \
        if (v && v->data && v->DeleteFunc)                                                               \
        {                                                                                                \
            for (size_t i = 0; i < v->size; i++)                                                         \
            {                                                                                            \
                v->DeleteFunc(v->data[i]);                                                               \
            }                                                                                            \
        }                                                                                                \
        if (v && v->data)                                                                                \
        {                                                                                                \
            free(v->data);                                                                               \
            v->data = NULL;                                                                              \
        }                                                                                                \
        if (v)                                                                                           \
        {                                                                                                \
            v->size = 0;                                                                                 \
            v->capacity = 0;                                                                             \
        }                                                                                                \
    }                                                                                                    \
                                                                                                         \
    int is_equal_vector(const Vector *v1, const Vector *v2)                                              \
    {                                                                                                    \
        if (!v1 || !v2)                                                                                  \
            return 0;                                                                                    \
        if (v1->size != v2->size)                                                                        \
            return 0;                                                                                    \
                                                                                                         \
        for (size_t i = 0; i < v1->size; i++)                                                            \
        {                                                                                                \
            if (v1->CopyFunc && v2->CopyFunc)                                                            \
            {                                                                                            \
                VECTOR_TYPE copy1 = v1->CopyFunc(v1->data[i]);                                           \
                VECTOR_TYPE copy2 = v2->CopyFunc(v2->data[i]);                                           \
                if (memcmp(&copy1, &copy2, sizeof(VECTOR_TYPE)) != 0)                                    \
                {                                                                                        \
                    if (v1->DeleteFunc)                                                                  \
                        v1->DeleteFunc(copy1);                                                           \
                    if (v2->DeleteFunc)                                                                  \
                        v2->DeleteFunc(copy2);                                                           \
                    return 0;                                                                            \
                }                                                                                        \
                if (v1->DeleteFunc)                                                                      \
                    v1->DeleteFunc(copy1);                                                               \
                if (v2->DeleteFunc)                                                                      \
                    v2->DeleteFunc(copy2);                                                               \
            }                                                                                            \
            else                                                                                         \
            {                                                                                            \
                if (memcmp(&v1->data[i], &v2->data[i], sizeof(VECTOR_TYPE)) != 0)                        \
                {                                                                                        \
                    return 0;                                                                            \
                }                                                                                        \
            }                                                                                            \
        }                                                                                                \
        return 1;                                                                                        \
    }                                                                                                    \
                                                                                                         \
    void copy_vector(Vector *dest, const Vector *src)                                                    \
    {                                                                                                    \
        if (!dest || !src)                                                                               \
            return;                                                                                      \
                                                                                                         \
        erase_vector(dest);                                                                              \
                                                                                                         \
        dest->CopyFunc = src->CopyFunc;                                                                  \
        dest->DeleteFunc = src->DeleteFunc;                                                              \
                                                                                                         \
        if (src->size > 0)                                                                               \
        {                                                                                                \
            dest->data = (VECTOR_TYPE *)malloc(src->capacity * sizeof(VECTOR_TYPE));                     \
            if (dest->data)                                                                              \
            {                                                                                            \
                dest->capacity = src->capacity;                                                          \
                dest->size = src->size;                                                                  \
                                                                                                         \
                if (src->CopyFunc)                                                                       \
                {                                                                                        \
                    for (size_t i = 0; i < src->size; i++)                                               \
                    {                                                                                    \
                        dest->data[i] = src->CopyFunc(src->data[i]);                                     \
                    }                                                                                    \
                }                                                                                        \
                else                                                                                     \
                {                                                                                        \
                    memcpy(dest->data, src->data, src->size * sizeof(VECTOR_TYPE));                      \
                }                                                                                        \
            }                                                                                            \
        }                                                                                                \
    }                                                                                                    \
                                                                                                         \
    Vector *copy_vector_new(const Vector *src)                                                           \
    {                                                                                                    \
        if (!src)                                                                                        \
            return NULL;                                                                                 \
                                                                                                         \
        Vector *new_vec = (Vector *)malloc(sizeof(Vector));                                              \
        if (new_vec)                                                                                     \
        {                                                                                                \
            new_vec->data = NULL;                                                                        \
            new_vec->size = 0;                                                                           \
            new_vec->capacity = 0;                                                                       \
            new_vec->CopyFunc = src->CopyFunc;                                                           \
            new_vec->DeleteFunc = src->DeleteFunc;                                                       \
            copy_vector(new_vec, src);                                                                   \
        }                                                                                                \
        return new_vec;                                                                                  \
    }                                                                                                    \
    void push_back_vector(Vector *v, VECTOR_TYPE value)                                                  \
    {                                                                                                    \
        if (!v)                                                                                          \
            return;                                                                                      \
                                                                                                         \
        if (v->size >= v->capacity)                                                                      \
        {                                                                                                \
            size_t new_capacity = (v->capacity == 0) ? 4 : v->capacity * 2;                              \
            VECTOR_TYPE *new_data = (VECTOR_TYPE *)realloc(v->data, new_capacity * sizeof(VECTOR_TYPE)); \
            if (!new_data)                                                                               \
                return;                                                                                  \
            v->data = new_data;                                                                          \
            v->capacity = new_capacity;                                                                  \
        }                                                                                                \
                                                                                                         \
        if (v->CopyFunc)                                                                                 \
        {                                                                                                \
            v->data[v->size] = v->CopyFunc(value);                                                       \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            v->data[v->size] = value;                                                                    \
        }                                                                                                \
        v->size++;                                                                                       \
    }                                                                                                    \
                                                                                                         \
    void delete_at_vector(Vector *v, size_t index)                                                       \
    {                                                                                                    \
        if (!v || !v->data || index >= v->size)                                                          \
            return;                                                                                      \
                                                                                                         \
        if (v->DeleteFunc)                                                                               \
        {                                                                                                \
            v->DeleteFunc(v->data[index]);                                                               \
        }                                                                                                \
                                                                                                         \
        for (size_t i = index; i < v->size - 1; i++)                                                     \
        {                                                                                                \
            v->data[i] = v->data[i + 1];                                                                 \
        }                                                                                                \
        v->size--;                                                                                       \
    }                                                                                                    \
                                                                                                         \
    VECTOR_TYPE get_at_vector(const Vector *v, size_t index)                                             \
    {                                                                                                    \
        if (!v || !v->data || index >= v->size)                                                          \
        {                                                                                                \
            VECTOR_TYPE empty = {0};                                                                     \
            return empty;                                                                                \
        }                                                                                                \
                                                                                                         \
        if (v->CopyFunc)                                                                                 \
        {                                                                                                \
            return v->CopyFunc(v->data[index]);                                                          \
        }                                                                                                \
        else                                                                                             \
        {                                                                                                \
            return v->data[index];                                                                       \
        }                                                                                                \
    }                                                                                                    \
    void delete_vector(Vector *v)                                                                        \
    {                                                                                                    \
        if (!v)                                                                                          \
            return;                                                                                      \
        erase_vector(v);                                                                                 \
        free(v);                                                                                         \
    }
