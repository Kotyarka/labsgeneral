#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "student.h"
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define EPS 1e-15
#define CAPACITY 10

typedef enum {
    OK,
    WRONG_STRUCT,
    NULL_POINTER,
    FILE_ERROR,
    MEMORY_ALLOC_ERROR,
} errorCodes;

typedef enum Type {
    ID,
    NAME, 
    SURNAME, 
    GROUP
} Type;
errorCodes read(Student ** students, FILE * inputFile, int * capacity, int * size);
errorCodes print(FILE * file, Student * students, int * size);

errorCodes parseId(int * ID);
errorCodes parseNameSurname(char * name);
errorCodes parseGroup(char * group);
errorCodes parseScores(unsigned char * scores);

errorCodes findType(char * userMsg, Type * type);
errorCodes find(Student * students, const void * toFind, Student ** found, int * sizeStuds, int * sizeFound, int * capacityFound, Type type, bool * isFound);

int compId(const void * student1, const void * student2);
int compName(const void * student1, const void * student2);
int compSurname(const void * student1, const void * student2);
int compGroup(const void * student1, const void * student2);
errorCodes sort(Student * students, int * sizeStud, Type type);

errorCodes average(Student * students, int * sizeStuds, Student * foundStuds, double * avMax, int * sizeAv);

#endif
