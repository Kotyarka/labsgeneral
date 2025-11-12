#include "../include/include.h"

int main() {
    FILE *inputFile = NULL, *outputFile = NULL;
    errorCodes result;
    char inputFilepath[256];
    char outputFilepath[256];
    
    printf("Enter input file path\n");
    if (fgets(inputFilepath, sizeof(inputFilepath), stdin) == NULL) {
        printf("Error: Failed to read input file path\n");
        return BAD_INPUT;
    }

    size_t len = strlen(inputFilepath);
    if (len > 0 && inputFilepath[len - 1] == '\n') {
        inputFilepath[len - 1] = '\0';
    }

    if (strlen(inputFilepath) == 0) {
        printf("Error: Input file path is empty\n");
        return BAD_FILENAME;
    }
  
    inputFile = fopen(inputFilepath, "r");
    if (inputFile == NULL) {
        printf("Error: Cannot open input file '%s'\n", inputFilepath);
        return OPEN_FILE_ERROR;
    }

    
    printf("Enter output file path\n");
    if (fgets(outputFilepath, sizeof(outputFilepath), stdin) == NULL) {
        printf("Error: Failed to read output file path\n");
        return BAD_INPUT;
    }

    len = strlen(outputFilepath);
    if (len > 0 && outputFilepath[len - 1] == '\n') {
        outputFilepath[len - 1] = '\0';
    }

    if (strlen(outputFilepath) == 0) {
        printf("Error: Output file path is empty\n");
        return BAD_FILENAME;
    }

    outputFile = fopen(outputFilepath, "w");
    if (outputFile == NULL) {
        printf("Error: Cannot open output file '%s'\n", outputFilepath);
        fclose(inputFile);
        return OPEN_FILE_ERROR;
    }

    result = formattingProcess(inputFile, outputFile);
    if (result != OK) {
        printf("Error during formatting process: %d\n", result);
    }

    if (fclose(inputFile) != 0) {
        printf("Error closing input file\n");
        return READ_ERROR;
    }
    
    if (fclose(outputFile) != 0) {
        printf("Error closing output file\n");
        return WRITE_ERROR;
    }

    printf("Formatting completed successfully\n");
    return OK;
}