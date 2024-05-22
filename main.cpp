#include <stdlib.h>
#include <stdio.h>

int main()
{
    int command;
    char textInput[100];
    size_t textInputSize = 100;
    char* textInputptr = NULL;
    size_t textLength = 0; //current length of the text
    running = 1

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
        printf("Choose the command (0-7), 8 for exitting: \n");
        scanf("%d", &command); //scans the inputted command
        switch (command) {
            case 1: //new text
                printf("Enter text to append: \n");
            fgets(textInput, sizeof(textInput), stdin);
            break;
            case 2: //new line
                printf("New line is started \n");
            fgets(textInput, sizeof(textInput), stdin);
            break;
            case 3: //saving a file
                printf("Enter the file name for saving: \n");
            break;
            case 4: //loading a file
                printf("Enter the file name for loading: \n");
            break;
            case 8: //stop the program
                running = 0;
            printf("Exiting the text editor.\n");
            break;
            default:
                printf("The command is not implemented: \n");
            break;
        }
    }

    free(textInput);
    return 0;
}
