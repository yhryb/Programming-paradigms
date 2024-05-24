
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int command;
    char textInput[100];
    int lineLength = strlen(textInput);
    char* textInputptr = NULL;
    int running = 1;
    char filename[100]; //file name input
    FILE* file;

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
                textInputptr = (char*)malloc(lineLength + 1);
                if (textInputptr != NULL) {
                strcpy(textInputptr, textInput);
                    textInput[strcspn(textInput, "\n")] = '\0';
                int extraLineLength = strlen(textInput);
                if (lineLength > 100) {
                    lineLength += extraLineLength;
                    if (textInputptr!= NULL) {
                        textInputptr = (char*)realloc(textInputptr, lineLength + 1);
                        strcpy(textInputptr + extraLineLength, textInput);
                    }
                }
                    printf("Entered text: %s\n", textInputptr);
                    free(textInputptr);
            }
                break;
                case 2: //new line
                    printf("New line is started \n");
                fgets(textInput, sizeof(textInput), stdin);
                // \0
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
                return 0;
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
                return 0;
                break;
                case 5:
                    // fputs(inputText);
                        break;
                case 6:
                    printf("Choose line and index: \n");
                printf("Enter text to insert: \n");
                break;
                case 7:
                    printf("Enter text to search: \n");
                break;
                default:
                    printf("The command is not implemented: \n");
                break;
            }
        }


        return 0;
    }
