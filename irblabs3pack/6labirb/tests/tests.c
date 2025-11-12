#include "../include/functions.h"
#include "../include/student.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_parseId() {
    printf("Testing parseId...\n");
    
    // Test valid ID
    int valid_id = 123;
    assert(parseId(&valid_id) == OK);
    
    // Test zero ID
    int zero_id = 0;
    assert(parseId(&zero_id) == WRONG_STRUCT);
    
    // Test NULL pointer
    assert(parseId(NULL) == WRONG_STRUCT);
    
    printf("✓ parseId tests passed\n");
}

void test_parseNameSurname() {
    printf("Testing parseNameSurname...\n");
    
    // Test valid name
    char valid_name[] = "John";
    assert(parseNameSurname(valid_name) == OK);
    
    // Test valid name with mixed case
    char mixed_name[] = "McDonald";
    assert(parseNameSurname(mixed_name) == OK);
    
    // Test name with numbers
    char number_name[] = "John123";
    assert(parseNameSurname(number_name) == WRONG_STRUCT);
    
    // Test name with spaces
    char space_name[] = "John Doe";
    assert(parseNameSurname(space_name) == WRONG_STRUCT);
    
    // Test name with special characters
    char special_name[] = "John@Doe";
    assert(parseNameSurname(special_name) == WRONG_STRUCT);
    
    // Test NULL pointer
    assert(parseNameSurname(NULL) == WRONG_STRUCT);
    
    printf("✓ parseNameSurname tests passed\n");
}

void test_parseGroup() {
    printf("Testing parseGroup...\n");
    
    // Test valid group (always returns OK in current implementation)
    char valid_group[] = "CS-101";
    assert(parseGroup(valid_group) == OK);
    
    // Test empty group
    char empty_group[] = "";
    assert(parseGroup(empty_group) == OK);
    
    // Test NULL pointer
    assert(parseGroup(NULL) == WRONG_STRUCT);
    
    printf("✓ parseGroup tests passed\n");
}

void test_parseScores() {
    printf("Testing parseScores...\n");
    
    // Test valid scores
    unsigned char valid_scores[] = {'A', 'B', 'C', 'D', 'E'};
    assert(parseScores(valid_scores) == OK);
    
    // Test scores with numbers
    unsigned char number_scores[] = {'1', '2', '3', '4', '5'};
    assert(parseScores(number_scores) == OK);
    
    // Test NULL pointer
    assert(parseScores(NULL) == WRONG_STRUCT);
    
    printf("✓ parseScores tests passed\n");
}

void test_findType() {
    printf("Testing findType...\n");
    
    Type type;
    
    // Test valid types
    char id_str[] = "id\n";
    assert(findType(id_str, &type) == OK);
    assert(type == ID);
    
    char name_str[] = "name\n";
    assert(findType(name_str, &type) == OK);
    assert(type == NAME);
    
    char surname_str[] = "surname\n";
    assert(findType(surname_str, &type) == OK);
    assert(type == SURNAME);
    
    char group_str[] = "group\n";
    assert(findType(group_str, &type) == OK);
    assert(type == GROUP);
    
    // Test invalid type
    char invalid_str[] = "invalid\n";
    assert(findType(invalid_str, &type) == WRONG_STRUCT);
    
    // Test NULL pointers
    assert(findType(NULL, &type) == NULL_POINTER);
    assert(findType(id_str, NULL) == NULL_POINTER);
    
    printf("✓ findType tests passed\n");
}

void test_compId() {
    printf("Testing compId...\n");
    
    Student student1 = {100, "John", "Doe", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    Student student2 = {200, "Jane", "Smith", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    Student student3 = {100, "Bob", "Brown", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    
    // Test student1 < student2
    assert(compId(&student1, &student2) < 0);
    
    // Test student2 > student1
    assert(compId(&student2, &student1) > 0);
    
    // Test student1 == student3
    assert(compId(&student1, &student3) == 0);
    
    printf("✓ compId tests passed\n");
}

void test_compName() {
    printf("Testing compName...\n");
    
    Student student1 = {100, "Alice", "Doe", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    Student student2 = {200, "Bob", "Smith", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    Student student3 = {300, "Alice", "Brown", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    
    // Test student1 < student2
    assert(compName(&student1, &student2) < 0);
    
    // Test student2 > student1
    assert(compName(&student2, &student1) > 0);
    
    // Test student1 == student3
    assert(compName(&student1, &student3) == 0);
    
    printf("✓ compName tests passed\n");
}

void test_compSurname() {
    printf("Testing compSurname...\n");
    
    Student student1 = {100, "John", "Adams", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    Student student2 = {200, "Jane", "Zoe", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    Student student3 = {300, "Bob", "Adams", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    
    // Test student1 < student2
    assert(compSurname(&student1, &student2) < 0);
    
    // Test student2 > student1
    assert(compSurname(&student2, &student1) > 0);
    
    // Test student1 == student3
    assert(compSurname(&student1, &student3) == 0);
    
    printf("✓ compSurname tests passed\n");
}

void test_compGroup() {
    printf("Testing compGroup...\n");
    
    Student student1 = {100, "John", "Doe", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    Student student2 = {200, "Jane", "Smith", "CS201", {'A', 'B', 'C', 'D', 'E'}};
    Student student3 = {300, "Bob", "Brown", "CS101", {'A', 'B', 'C', 'D', 'E'}};
    
    // Test student1 < student2
    assert(compGroup(&student1, &student2) < 0);
    
    // Test student2 > student1
    assert(compGroup(&student2, &student1) > 0);
    
    // Test student1 == student3
    assert(compGroup(&student1, &student3) == 0);
    
    printf("✓ compGroup tests passed\n");
}

void test_sort() {
    printf("Testing sort...\n");
    
    Student students[3] = {
        {300, "Charlie", "Brown", "CS201", {'A', 'B', 'C', 'D', 'E'}},
        {100, "Alice", "Adams", "CS101", {'A', 'B', 'C', 'D', 'E'}},
        {200, "Bob", "Clark", "CS101", {'A', 'B', 'C', 'D', 'E'}}
    };
    int size = 3;
    
    // Test sorting by ID
    assert(sort(students, &size, ID) == OK);
    assert(students[0].id == 100);
    assert(students[1].id == 200);
    assert(students[2].id == 300);
    
    // Test sorting by name
    assert(sort(students, &size, NAME) == OK);
    assert(strcmp(students[0].name, "Alice") == 0);
    assert(strcmp(students[1].name, "Bob") == 0);
    assert(strcmp(students[2].name, "Charlie") == 0);
    
    // Test NULL pointers
    assert(sort(NULL, &size, ID) == NULL_POINTER);
    assert(sort(students, NULL, ID) == NULL_POINTER);
    
    printf("✓ sort tests passed\n");
}

void test_average() {
    printf("Testing average...\n");
    
    // Используем числовые значения для оценок, а не буквы
    // 'A' = 65, 'B' = 66, но лучше использовать явные числовые значения
    Student students[3] = {
        {100, "John", "Doe", "CS101", {90, 90, 90, 90, 90}}, // Average: 90.0
        {200, "Jane", "Smith", "CS101", {85, 85, 85, 85, 85}}, // Average: 85.0
        {300, "Bob", "Brown", "CS101", {90, 90, 90, 90, 90}}  // Average: 90.0
    };
    int size = 3;
    Student foundStuds[3];
    double avMax;
    int sizeAv = 0;
    
    // Test average calculation
    assert(average(students, &size, foundStuds, &avMax, &sizeAv) == OK);
    assert(sizeAv == 2); // Should find two students with max average (90.0)
    
    // Verify the correct students were found
    bool foundJohn = false, foundBob = false;
    for (int i = 0; i < sizeAv; i++) {
        if (foundStuds[i].id == 100) foundJohn = true;
        if (foundStuds[i].id == 300) foundBob = true;
    }
    assert(foundJohn && foundBob);
    
    // Test NULL pointers
    assert(average(NULL, &size, foundStuds, &avMax, &sizeAv) == NULL_POINTER);
    assert(average(students, NULL, foundStuds, &avMax, &sizeAv) == NULL_POINTER);
    assert(average(students, &size, NULL, &avMax, &sizeAv) == NULL_POINTER);
    assert(average(students, &size, foundStuds, NULL, &sizeAv) == NULL_POINTER);
    assert(average(students, &size, foundStuds, &avMax, NULL) == NULL_POINTER);
    
    printf("✓ average tests passed\n");
}
void test_find() {
    printf("Testing find...\n");
    
    Student students[3] = {
        {100, "John", "Doe", "CS101", {'A', 'B', 'C', 'D', 'E'}},
        {200, "Jane", "Doe", "CS201", {'A', 'B', 'C', 'D', 'E'}},
        {300, "Bob", "Smith", "CS101", {'A', 'B', 'C', 'D', 'E'}}
    };
    int sizeStuds = 3;
    int sizeFound = 0;
    int capacityFound = 10;
    bool isFound = false;
    
    Student* found = (Student*)malloc(capacityFound * sizeof(Student));
    
    // Test finding by surname
    char surname_to_find[] = "Doe";
    assert(find(students, surname_to_find, &found, &sizeStuds, &sizeFound, &capacityFound, SURNAME, &isFound) == OK);
    assert(isFound == true);
    assert(sizeFound == 2);
    
    // Test finding by ID
    char id_to_find[] = "200";
    sizeFound = 0;
    isFound = false;
    assert(find(students, id_to_find, &found, &sizeStuds, &sizeFound, &capacityFound, ID, &isFound) == OK);
    assert(isFound == true);
    assert(sizeFound == 1);
    assert(found[0].id == 200);
    
    // Test finding non-existent
    char not_found[] = "NonExistent";
    sizeFound = 0;
    isFound = false;
    assert(find(students, not_found, &found, &sizeStuds, &sizeFound, &capacityFound, NAME, &isFound) == OK);
    assert(isFound == false);
    assert(sizeFound == 0);
    
    free(found);
    
    printf("✓ find tests passed\n");
}

void test_print() {
    printf("Testing print...\n");
    
    Student students[2] = {
        {100, "John", "Doe", "CS101", {'A', 'B', 'C', 'D', 'E'}},
        {200, "Jane", "Smith", "CS201", {'F', 'G', 'H', 'I', 'J'}}
    };
    int size = 2;
    
    // Test printing to file
    FILE* test_file = fopen("test_output.txt", "w");
    assert(test_file != NULL);
    assert(print(test_file, students, &size) == OK);
    fclose(test_file);
    
    // Test NULL pointers - create new file for each test
    FILE* test_file2 = fopen("test_output2.txt", "w");
    assert(test_file2 != NULL);
    assert(print(NULL, students, &size) == NULL_POINTER);
    fclose(test_file2);
    
    FILE* test_file3 = fopen("test_output3.txt", "w");
    assert(test_file3 != NULL);
    assert(print(test_file3, NULL, &size) == NULL_POINTER);
    fclose(test_file3);
    
    FILE* test_file4 = fopen("test_output4.txt", "w");
    assert(test_file4 != NULL);
    assert(print(test_file4, students, NULL) == NULL_POINTER);
    fclose(test_file4);
    
    // Clean up
    remove("test_output.txt");
    remove("test_output2.txt");
    remove("test_output3.txt");
    remove("test_output4.txt");
    
    printf("✓ print tests passed\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");
    
    // Test with single student instead of zero-size array
    Student single_student = {1, "A", "B", "C", {'A', 'A', 'A', 'A', 'A'}};
    Student single_array[1] = {single_student};
    int single_size = 1;
    Student single_found[1];
    double single_avMax;
    int single_sizeAv = 0;
    
    assert(average(single_array, &single_size, single_found, &single_avMax, &single_sizeAv) == OK);
    assert(single_sizeAv == 1);
    
    // Test with minimum values - use int instead of unsigned int for ID
    Student min_student = {1, "A", "B", "C", {'A', 'A', 'A', 'A', 'A'}};
    int min_id = min_student.id; // Extract ID as int for testing parseId
    Student min_array[1] = {min_student};
    int min_size = 1;
    
    assert(parseId(&min_id) == OK);
    assert(parseNameSurname(min_student.name) == OK);
    assert(parseNameSurname(min_student.surname) == OK);
    assert(parseGroup(min_student.group) == OK);
    
    printf("✓ Edge cases tests passed\n");
}

int main() {
    printf("Starting comprehensive tests for student management system...\n\n");
    
    test_parseId();
    test_parseNameSurname();
    test_parseGroup();
    test_parseScores();
    test_findType();
    test_compId();
    test_compName();
    test_compSurname();
    test_compGroup();
    test_sort();
    test_average();
    test_find();
    test_print();
    test_edge_cases();
    
    printf("\nAll student management system tests passed! ✓\n");
    return 0;
}