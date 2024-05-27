
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 4096

int main() {
    int command;
    char textInput[MAX_TEXT_LENGTH];
    char** textLinesptr = NULL;
    int running = 1;
    char filename[100]; //file name input
    FILE* fileptr;
    int lineCount = 0;

    printf("Welcome to Text Editor. Here is what you can do:\n"
    "Ask for available commands - 0;\n"
    "Enter new text - 1;\n"
    "Start a new line - 2;\n"
    "Save a file - 3;\n"
    "Load a file - 4;\n"
    "Print the current text to console - 5;\n"
    "Insert the text by line and symbol index - 6;\n"
    "Search - 7;\n");

    while (running) {
        printf("Choose the command (1-7): \n");
        scanf("%d", &command); //scans the inputted command
        getchar(); //consumes leftover so that input is allowed
        switch (command) {
            case 0:
                running = 0;
                break;
            case 1: //new text
                printf("Enter text to append: \n");
                fgets(textInput, sizeof(textInput), stdin);
                textInput[strcspn(textInput, "\n")] = '\0'; //removing new line character
                textLinesptr = (char**)realloc(textLinesptr, (lineCount + 1) * sizeof(char*)); //allocating memory for an array of strings,
                textLinesptr[lineCount] = (char*)malloc(strlen(textInput) + 1); //allocating memory for new text based on the length of the input, plus 1 for null operator
                strcpy(textLinesptr[lineCount], textInput);
                lineCount++;
            break;
            case 2: //new line
                textLinesptr = (char**)realloc(textLinesptr, (lineCount + 1) * sizeof(char*)); //allocating plus 1 line in memory
                if (textLinesptr != NULL) {
                    textLinesptr[lineCount] = (char*)malloc(sizeof(char)); //allocating 1 byte for newline character at the place of the lineCount
                    textLinesptr[lineCount][0] = '\n';
                    lineCount++;
                }
                printf("New line is started \n");
                break;
            case 3: //saving a file
                printf("Enter the file name for saving: \n");
                fgets(filename, sizeof(filename), stdin);
                fileptr = fopen(filename, "w"); //w mode for write
                if (fileptr != NULL) {
                    for (int i = 0; i < lineCount; i++) {
                        fputs(textLinesptr[i], fileptr);
                        fputs("\n", fileptr);
                    }
                }
                break;
            case 4: //loading a file
                FILE* file;
                file = fopen(filename, "r");
                if (file == NULL)
                {
                    printf("Error opening file");
                }
                else
                {
                    for (int i = 0; i < lineCount; i++) {
                        printf("%s\n", textLinesptr[i]);
                    }
                    fclose(file);
                }
                break;
            case 5: // printing the whole text
                for (int i = 0; i < lineCount; i++) {
                    printf("%s", textLinesptr[i]);
                }
                break;
            case 6:
                    int lineNumber, symbolIndex;
                    printf("Choose line and index: \n");
                    scanf("%d %d", &lineNumber, &symbolIndex);
                    getchar();
                    printf("Enter text to insert: \n");
                    fgets(textInput, sizeof(textInput), stdin);
                    textInput[strcspn(textInput, "\n")] = '\0';
                    if (lineNumber < 0 || lineNumber >= lineCount) {
                        printf("Line number can not be negative.\n");
                    } else if (symbolIndex < 0 || symbolIndex > strlen(textLinesptr[lineNumber])) {
                        printf("Index number can not be negative.\n");
                    } else {
                        int beforeLength = strlen(textLinesptr[lineNumber]);
                        int afterLength = strlen(textInput);
                        char* newLineptr = (char*)malloc(beforeLength + afterLength + 1);
                        strncpy(newLineptr, textLinesptr[lineNumber], symbolIndex); //here we copy text from the starting line into buffer up to the intended index so that we can add new text after it
                        strcpy(newLineptr + symbolIndex, textInput); //copies new inputted text at the intended index
                        strcpy(newLineptr + symbolIndex + afterLength, textLinesptr[lineNumber] + symbolIndex); //copies the old text after the inserted text into buffer
                        free(textLinesptr[lineNumber]); //releasing the old memory for the before line
                        strcpy(textLinesptr[lineNumber] + symbolIndex + afterLength, textLinesptr[lineNumber] + symbolIndex);
                    }
                    break;
                    case 7:
                            printf("Enter text to search: \n");
                            fgets(textInput, sizeof(textInput), stdin);
                            textInput[strcspn(textInput, "\n")] = '\0';
                            for (int i = 0; i < lineCount; i++) {
                                if (strstr(textLinesptr[i], textInput)) {//strstr searches for first occurence
                                    printf("Found in line %d\n", i + 1, textLinesptr[i]); //i + 1 because computer counts from 0 and lineCount from 1
                                }
                            }
                            break;

                                default:
                                    printf("The command is not implemented: \n");
                        break;
                }
        }
    free(textLinesptr);
    return 0;
    }


