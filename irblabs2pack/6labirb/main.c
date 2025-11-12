#include "include/functions.h"
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 0;
    }

    char Input[FILENAME_MAX];    
    char Output[FILENAME_MAX];
    FILE * inputFile;
    FILE * outputFile;

    strcpy(Input, argv[1]);
    strcpy(Output, argv[2]);

    inputFile = fopen(Input, "r");
    
    if (!inputFile) {
        printf("Error while opening an input file\n");
        return 0;
    }

    outputFile = fopen(Output, "w");
    if (!outputFile) {
        printf("Error while opening an output file\n");
        fclose(inputFile);
        return 0;
    }

    int capacityAll = CAPACITY;
    int capacityFound = CAPACITY;
    int sizeAll = 0;
    int sizeFound = 0;
    int sizeAv = 0;

    char userMsg[MAX_INPUT]; 
    char data[MAX_INPUT];
    Type type;
    bool isFound = false;
    errorCodes returnCode;
    double avMax = 0.0;
    char * endptr = NULL;

    Student * students = (Student*)malloc(capacityAll * sizeof(Student));

    if (!students) {
        printf("Some allocation error!\n");
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    }
    
    returnCode = read(&students, inputFile, &capacityAll, &sizeAll);

    if (returnCode != OK) {
        printf("Error reading file: ");
        switch (returnCode) {
            case WRONG_STRUCT:
                printf("Wrong struct error!\n");
                break;
            case NULL_POINTER:
                printf("Come across a null pointer!\n");
                break;
            case MEMORY_ALLOC_ERROR:
                printf("Allocation error!\n");
                break;
            default:
                printf("Unknown error!\n");
        }
        free(students);
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    }

    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. Find student\n");
        printf("2. Sort students\n");
        printf("3. Show students with max average scores\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        
        if (fgets(userMsg, MAX_INPUT, stdin) == NULL) {
            break;
        }
        
        choice = atoi(userMsg);
        
        switch (choice) {
            case 1: {
                printf("\n=== Find Student ===\n");
                printf("Select search parameter:\n");
                printf("1. ID\n");
                printf("2. Name\n");
                printf("3. Surname\n");
                printf("4. Group\n");
                printf("Enter parameter (1-4): ");
                
                fgets(userMsg, MAX_INPUT, stdin);
                int paramChoice = atoi(userMsg);
                
                switch (paramChoice) {
                    case 1: type = ID; break;
                    case 2: type = NAME; break;
                    case 3: type = SURNAME; break;
                    case 4: type = GROUP; break;
                    default:
                        printf("Invalid parameter choice!\n");
                        break;
                }
                
                if (paramChoice >= 1 && paramChoice <= 4) {
                    printf("Enter the data you want to find: ");
                    fgets(data, MAX_INPUT, stdin);

                    char * ptr = strchr(data, '\n');
                    if (ptr) {
                        *ptr = '\0';
                    }
                    
                    int id = 0;
                    switch (type) {
                        case ID:
                            id = strtol(data, &endptr, 10);
                            if (endptr == (const char*)data || *endptr != '\0') {
                                printf("Wrong input! Please enter a valid number.\n");
                                break;
                            }
                            returnCode = parseId(&id);
                            break;

                        case NAME:            
                        case SURNAME:
                            returnCode = parseNameSurname(data);
                            break;

                        case GROUP:
                            returnCode = parseGroup(data);
                            break;
                    }
                    
                    if (returnCode == OK) {
                        Student * found = (Student*)malloc(capacityFound * sizeof(Student));
                        if (!found) {
                            printf("Allocation error!\n");
                            break;
                        }
                        
                        returnCode = find(students, data, &found, &sizeAll, &sizeFound, &capacityFound, type, &isFound);                

                        if (returnCode == OK && isFound) {
                            printf("Found %i people with this parameter\n", sizeFound);
                            print(stdout, found, &sizeFound);
                            print(outputFile, found, &sizeFound);
                            isFound = false;
                            sizeFound = 0;
                        } else {
                            printf("Could not find anyone\n");
                        }
                        free(found);
                    } else {
                        printf("Invalid data format\n");
                    }
                }
                break;
            }
            
            case 2: {

                printf("\n=== Sort Students ===\n");
                printf("Select sort parameter:\n");
                printf("1. ID\n");
                printf("2. Name\n");
                printf("3. Surname\n");
                printf("4. Group\n");
                printf("Enter parameter (1-4): ");
                
                fgets(userMsg, MAX_INPUT, stdin);
                int sortChoice = atoi(userMsg);
                
                switch (sortChoice) {
                    case 1: type = ID; break;
                    case 2: type = NAME; break;
                    case 3: type = SURNAME; break;
                    case 4: type = GROUP; break;
                    default:
                        printf("Invalid parameter choice!\n");
                        break;
                }
                
                if (sortChoice >= 1 && sortChoice <= 4) {
                    returnCode = sort(students, &sizeAll, type);
                    if (returnCode == OK) {
                        print(stdout, students, &sizeAll);
                        print(outputFile, students, &sizeAll);
                        printf("Sorted successfully\n");
                    } else {
                        printf("Sorting failed\n");
                    }
                }
                break;
            }
            
            case 3: {
                printf("\n=== Students with Max Average Scores ===\n");
                Student * avStuds = (Student *)malloc(sizeAll * sizeof(Student));
                if (!avStuds) {
                    printf("Allocation error!\n");
                } else {
                    returnCode = average(students, &sizeAll, avStuds, &avMax, &sizeAv); 
                    if (returnCode == OK) {
                        print(stdout, avStuds, &sizeAv);
                        print(outputFile, avStuds, &sizeAv);
                        printf("Students with max average scores printed to file\n");
                    } else {
                        printf("Error calculating averages\n");
                    }
                    free(avStuds);
                }
                break;
            }
            
            case 4:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
                break;
        }
    } while (choice != 4);

    printf("See your result in the output file!\n");

    free(students);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}