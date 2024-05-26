
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TEXT_LENGTH 4096

int main() {
    int command;
    char textInput[MAX_TEXT_LENGTH];
    int textLength = 0;
    char** textLinesptr = NULL;
    int running = 1;
    char filename[100]; //file name input
    FILE* file;
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
            case 1: //new text
                printf("Enter text to append: \n");
            fgets(textInput, sizeof(textInput), stdin);
            textInput[strcspn(textInput, "\n")] = '\0'; //to not store \0
            //int lineCount = 0;
            //counting lines of text:
            lineCount = 1; //if the input is empty it's still one line
            for (int i = 0; textInput[i] != '\0'; i++) { //\0 signifies end of the sentence but not the end of a line
                if (textInput[i] == '\n') {
                    lineCount++; //\n marks end of the current line, moves cursor to the next line
                }
            }
            textLinesptr = (char**)malloc(lineCount * sizeof(char*)); //allocating memory for an array of pointers based on number of lines
            for (int i = 0; i < lineCount; i++) {
                textLinesptr[i] = (char*)malloc((textLength + 1) * sizeof(char)); //+1 to store /0 to terminate
            }

            for (int i = 0; i < lineCount; i++) {
                strcpy(textLinesptr[i], textInput);
            }
            printf("Entered text:\n");
            for (int i = 0; i < lineCount; i++) {
                printf("%s\n", textLinesptr[i]); //%s for strings, \n to print each line separately; [i] is the index of the string in the array of pointers
            }
            free(textLinesptr);
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
            file = fopen(filename, "w");
            if (file != NULL)
            {
                fputs("Hello, files world!", file);
                fclose(file);
            }

            break;
            case 4: //loading a file
                printf("Enter the file name for loading: \n");
            file = fopen(filename, "r");
            if (file == NULL)
            {
                printf("Error opening file");
            }
            else
            {
                if (fgets(textInput, 100, file) != NULL)
                {
                    printf("%s", textInput);
                }
                fclose(file);
            }

            break;
            case 5: // printing the whole text
                printf(textInput, "\n");
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
                printf("Invalid line number.\n");
            } else if (symbolIndex < 0 || symbolIndex > strlen(textLinesptr[lineNumber])) {
                printf("Invalid symbol index.\n");
            } else {
                int beforeLength = textLength;
                int afterLength = strlen(textInput);
                char* newLineptr = (char*)malloc(beforeLength + afterLength + 1);
                strncpy(newLineptr, textLinesptr[lineNumber], symbolIndex); //here we copy text from the starting line into buffer up to the intended index so that we can add new text after it
                strcpy(newLineptr + symbolIndex, textInput); //copies new inputted text at the intended index
                strcpy(newLineptr + symbolIndex + afterLength, textLinesptr[lineNumber] + symbolIndex); //copies the old text after the inserted text into buffer
                free(textLinesptr[lineNumber]); //releasing the old memory for the before line
            }

                break;
            case 7:
                    //printf("Enter text to search: \n");
                    //break;
                default:
                    printf("The command is not implemented: \n");
                break;
            }
        }

    return 0;
    }

