#include "../include/functions.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

errorCodes read(Student ** students, FILE * inputFile, int * capacity, int * size) {
    if (students == NULL || capacity == NULL || inputFile == NULL) {
        return NULL_POINTER;
    }
    if (*capacity == 0) {
        *capacity = 1;
    }
    
    int id0 = 0;
    int res = 0; 
    char name0[STUD_CAP];
    char surname0[STUD_CAP];
    char group0[GROUP_CAP];
    unsigned char scores0[SCORES_SIZE] = {0};
    errorCodes errorCodes;
    
    res = fscanf(inputFile, "%d %s %s %s %c %c %c %c %c", &id0, name0, surname0, group0, 
                &scores0[0], &scores0[1], &scores0[2], &scores0[3], &scores0[4]);
    
    while (res != EOF) {
        if (res != 9) {
            return WRONG_STRUCT;
        }

        Student stud;

        if (*size == *capacity) {
            *capacity *= 2;
            Student * tmp = (Student*)realloc(*students, *capacity * sizeof(Student));
            if (!tmp) {
                return MEMORY_ALLOC_ERROR;
            }
            *students = tmp;
        }
        
        errorCodes = parseId(&id0);
        if (errorCodes == OK) {
            stud.id = id0;
        } else {
            return WRONG_STRUCT;
        }

        errorCodes = parseNameSurname(name0);
        if (errorCodes == OK) {
            strcpy(stud.name, name0);
        } else {
            return WRONG_STRUCT;
        }

        errorCodes = parseNameSurname(surname0);
        if (errorCodes == OK) {
            strcpy(stud.surname, surname0);
        } else {
            return WRONG_STRUCT;
        }

        errorCodes = parseGroup(group0);
        if (errorCodes == OK) {
            strcpy(stud.group, group0);
        } else {
            return WRONG_STRUCT;
        }

        errorCodes = parseScores(scores0);
        if (errorCodes == OK) {
            for (int i = 0; i < SCORES_SIZE; i++) {
                stud.scores[i] = scores0[i];
            }
        } else {
            return WRONG_STRUCT;
        }

        (*students)[*size] = stud;
        (*size)++;
        res = fscanf(inputFile, "%d %s %s %s %c %c %c %c %c", &id0, name0, surname0, group0, 
                    &scores0[0], &scores0[1], &scores0[2], &scores0[3], &scores0[4]);
    }
    return OK;
}

errorCodes print(FILE * file, Student * students, int * size) {
    if (!students || !size || !file) {
        return NULL_POINTER;
    }
    
    for (int i = 0; i < *size; ++i) {
        Student student = students[i];
        int code = fprintf(file, "%u %s %s %s ", student.id, student.name, student.surname, student.group);

        if (code < 0) {
            return WRONG_STRUCT;
        }

        for (int j = 0; j < SCORES_SIZE; ++j) {
            if (fprintf(file, "%c ", student.scores[j]) < 0) {
                return WRONG_STRUCT;
            }
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
    return OK;
}

errorCodes parseId(int * ID) {
    if (ID == NULL || *ID <= 0) {
        return WRONG_STRUCT;
    }
    return OK;
}

errorCodes parseNameSurname(char * name) {
    if (!name) {
        return WRONG_STRUCT;
    }

    char * ptr = name;
    int isWrong = 0;
    while (*ptr) {
        if (!isalpha(*ptr)) {
            isWrong = 1;
            break;
        }
        ++ptr;
    }

    if (isWrong) {
        return WRONG_STRUCT;
    }
    return OK;
}

errorCodes parseGroup(char * group) {
    if (!group) {
        return WRONG_STRUCT;
    }
    return OK;
}

errorCodes parseScores(unsigned char * scores) {
    if (!scores) {
        return WRONG_STRUCT;
    }

    for (int i = 0; i < SCORES_SIZE; i++) {
        if (!isalnum((char)scores[i])) {
            return WRONG_STRUCT;
        }
    }

    return OK;
}

errorCodes findType(char * userMsg, Type * type) {
    if (userMsg == NULL || type == NULL) {
        return NULL_POINTER;
    }
    
    errorCodes errorCodes = WRONG_STRUCT;
    char * ptr = strchr(userMsg, '\n');
    if (ptr) {
        *ptr = '\0';
    }

    if (strcmp(userMsg, "id") == 0) {
        *type = ID;
        errorCodes = OK;
    } else if (strcmp(userMsg, "name") == 0) {
        *type = NAME;
        errorCodes = OK;
    } else if (strcmp(userMsg, "surname") == 0) {
        *type = SURNAME;
        errorCodes = OK;
    } else if (strcmp(userMsg, "group") == 0) {
        *type = GROUP;
        errorCodes = OK;
    }
    
    return errorCodes;
}

errorCodes find(Student * students, const void * toFind, Student ** found, int * sizeStuds, int * sizeFound, int * capacityFound, Type type, bool * isFound) {
    
    if (students == NULL || toFind == NULL || found == NULL || sizeFound == NULL || capacityFound == NULL  || sizeStuds == NULL || isFound == NULL) {
        return NULL_POINTER;
    }
    
    long int id = 0;
    bool foundSmth = false;
    
    if (*capacityFound == 0) {
        *capacityFound = 1; 
    }

    if (type == ID) {
        char * endptr;
        id = strtol(toFind, &endptr, 10);
        if (endptr == (const char*)toFind || *endptr != '\0') {
            return WRONG_STRUCT; 
        }
    }

    for (int i = 0; i < *sizeStuds; ++i) {
        if (*sizeFound == *capacityFound) {
            *capacityFound *= 2;
            Student * tmp = (Student*)realloc(*found, *capacityFound * sizeof(Student));
            if (!tmp) {
                return MEMORY_ALLOC_ERROR;
            }
            *found = tmp;
        }

        switch (type) {
            case ID:
                if (students[i].id == id) {
                    foundSmth = true;
                    *isFound = true;
                }                  
                break;
            case NAME:
                if (strcmp(students[i].name, (char*)toFind) == 0) {
                    foundSmth = true;
                    *isFound = true;
                }                    
                break;
            case SURNAME:
                if (strcmp(students[i].surname, (char*)toFind) == 0) {
                    foundSmth = true;
                    *isFound = true;
                }                      
                break;          
            case GROUP:
                if (strcmp(students[i].group, (char*)toFind) == 0) {
                    foundSmth = true;
                    *isFound = true;
                }                    
                break;
        }
        if (foundSmth) {
            (*found)[*sizeFound] = students[i];
            (*sizeFound)++;
            foundSmth = false; 
        }
    }
    
    return OK;
}

int compId(const void * student1, const void * student2) {
    const Student * stud1 = (const Student*) student1;
    const Student * stud2 = (const Student*) student2;
    return (stud1->id > stud2->id) - (stud1->id < stud2->id);
}

int compName(const void * student1, const void * student2) {
    const Student * stud1 = (const Student*) student1;
    const Student * stud2 = (const Student*) student2;
    return strcmp(stud1->name, stud2->name);
}

int compSurname(const void * student1, const void * student2) {
    const Student * stud1 = (const Student*) student1;
    const Student * stud2 = (const Student*) student2;
    return strcmp(stud1->surname, stud2->surname);
}

int compGroup(const void * student1, const void * student2) {
    const Student * stud1 = (const Student*) student1;
    const Student * stud2 = (const Student*) student2;
    return strcmp(stud1->group, stud2->group);
}

errorCodes sort(Student * students, int * sizeStud, Type type) {
    if (students == NULL || sizeStud == NULL) {
        return NULL_POINTER;
    }
    
    switch (type) {
        case NAME:
            qsort(students, *sizeStud, sizeof(Student), compName);
            break;
        case SURNAME:
            qsort(students, *sizeStud, sizeof(Student), compSurname);
            break;
        case GROUP:
            qsort(students, *sizeStud, sizeof(Student), compGroup);
            break;
        case ID:
            qsort(students, *sizeStud, sizeof(Student), compId);
            break;
    }
    return OK;
}

errorCodes average(Student * students, int * sizeStuds, Student * foundStuds, double * avMax, int * sizeAv) {
    if (students == NULL || sizeStuds == NULL || foundStuds == NULL || avMax == NULL || sizeAv == NULL) {
        return NULL_POINTER;
    }
    
    *avMax = 0.0;
    double av = 0.0;

    for (int i = 0; i < *sizeStuds; ++i) {
        av = 0.0;
        for (int j = 0; j < SCORES_SIZE; ++j) {
            av += (double)(students[i].scores[j]);
        }

        av /= SCORES_SIZE;
        if (av > *avMax) {
            *avMax = av;
        }
    }

    for (int i = 0; i < *sizeStuds; ++i) {
        av = 0.0;
        for (int j = 0; j < SCORES_SIZE; ++j) {
            av += (double)(students[i].scores[j]);
        }

        av /= SCORES_SIZE;
        if (fabs(av - *avMax) < EPS) {
            foundStuds[*sizeAv] = students[i]; 
            ++(*sizeAv);
        }
    }

    return OK;
}
