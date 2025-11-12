#ifndef STUDENT_H
#define STUDENT_H

#define STUD_CAP 100
#define SCORES_SIZE 5
#define GROUP_CAP 15

typedef struct Student {
    unsigned int id;
    char name[STUD_CAP];
    char surname[STUD_CAP];
    char group[GROUP_CAP];
    unsigned char scores[SCORES_SIZE];
} Student;

#endif
