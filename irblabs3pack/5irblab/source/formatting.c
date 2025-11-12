#include "../include/include.h"

errorCodes formattingProcess(FILE* inputFile, FILE* outputFile) {
    if (inputFile == NULL || outputFile == NULL) {
        return INVALID_PARAMETER;
    }

    char line[1024];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        
        errorCodes lineResult = formatLine(line, outputFile);
        if (lineResult != OK) {
            return lineResult;
        }
    }
    
    if (ferror(inputFile)) {
        return READ_ERROR;
    }
    
    return OK;
}

errorCodes formatLine(char* line, FILE* outputFile) {
    if (line == NULL || outputFile == NULL) {
        return INVALID_PARAMETER;
    }

    char* words[1024];
    int wordCount = wordCounter(line, words);

    if (wordCount == 0) {
        if (fputc('\n', outputFile) == EOF) {
            return WRITE_ERROR;
        }
        return OK;
    }

    int length = 0;
    for (int i = 0; i < wordCount; i++) {
        length += strlen(words[i]);
    }

    if (length + (wordCount - 1) < 80) {
        for (int i = 0; i < wordCount; i++) {
            if (fprintf(outputFile, "%s", words[i]) < 0) {
                return WRITE_ERROR;
            }
            if (i < wordCount - 1) {
                if (fputc(' ', outputFile) == EOF) {
                    return WRITE_ERROR;
                }
            }
        }
        if (fputc('\n', outputFile) == EOF) {
            return WRITE_ERROR;
        }
        return OK;
    }

    int currentLength = 0;
    int lineStart = 0;

    for (int i = 0; i < wordCount; i++) {
        int wordLength = strlen(words[i]);

        if (currentLength + wordLength + (i - lineStart) > 80) {
            if (lineStart == i) {
                int written = 0;
                while (written < wordLength) {
                    int partSize = 80;
                    if (written + partSize > wordLength) {
                        partSize = wordLength - written;
                    }
                    if (fwrite(words[i] + written, 1, partSize, outputFile) != (size_t)partSize) {
                        return WRITE_ERROR;
                    }
                    if (fputc('\n', outputFile) == EOF) {
                        return WRITE_ERROR;
                    }
                    written += partSize;
                }
                lineStart = i + 1;
                currentLength = 0;
            } else {
                int totalSpaces = 80 - currentLength;
                int spaceSlots = i - lineStart - 1;
                
                if (spaceSlots > 0) {
                    int base_spaces = totalSpaces / spaceSlots;
                    int extra_spaces = totalSpaces % spaceSlots;
                    
                    for (int j = lineStart; j < i; j++) {
                        if (fprintf(outputFile, "%s", words[j]) < 0) {
                            return WRITE_ERROR;
                        }
                        if (j < i - 1) {
                            int spaces_to_add = base_spaces;
                            if (j - lineStart < extra_spaces) {
                                spaces_to_add++;
                            }
                            for (int k = 0; k < spaces_to_add; k++) {
                                if (fputc(' ', outputFile) == EOF) {
                                    return WRITE_ERROR;
                                }
                            }
                        }
                    }
                } else {
                    if (fprintf(outputFile, "%s", words[lineStart]) < 0) {
                        return WRITE_ERROR;
                    }
                }
                
                if (fputc('\n', outputFile) == EOF) {
                    return WRITE_ERROR;
                }
                lineStart = i;
                currentLength = wordLength;
            }
        } else {
            currentLength += wordLength;
        }
    }
    
    if (lineStart < wordCount) {
        for (int i = lineStart; i < wordCount; i++) {
            if (fprintf(outputFile, "%s", words[i]) < 0) {
                return WRITE_ERROR;
            }
            if (i < wordCount - 1) {
                if (fputc(' ', outputFile) == EOF) {
                    return WRITE_ERROR;
                }
            }
        }
        if (fputc('\n', outputFile) == EOF) {
            return WRITE_ERROR;
        }
    }
    
    return OK;
}

int wordCounter(char *line, char** words) {
    if (line == NULL || words == NULL) {
        return 0;
    }

    int wordsCount = 0;
    char* token = line;
    int inWord = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (is_readable(line[i])) {
            if (!inWord) {
                token = &line[i];
                inWord = 1;
            }
        } else {
            if (inWord) {
                line[i] = '\0';
                words[wordsCount] = token;
                wordsCount++;
                inWord = 0;           
            }
        }
    }

    if (inWord) {
        words[wordsCount] = token;
        wordsCount++;
    }

    return wordsCount;
}

int is_readable(char c) {
    return isprint((unsigned char)c) && c != ' ' && c != '\t' && c != '\n' && c != '\r';
}