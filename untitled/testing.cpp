//
// Created by MacUser on 23.05.2024.
//

#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int command;
    char textInput[100];
    int lineLength = 0;
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
        printf("Choose the command (1-7), 8 for exiting: \n");
        scanf("%d", &command); //scans the inputted command
        switch (command) {
            case 1: //new text
                printf("Enter text to append: \n");
                fgets(textInput, sizeof(textInput), stdin);
                textInputptr = (char*)malloc(strlen(textInput)*size_of(char));
                lineLength += strlen(textInput);
                if (lineLength > 100) {
                    textInputptr = (char*)realloc(strlen(textInput)*size_of(char));
                // add array
                for (int i = 0; i < lineLength + 100; i++) {
                    textInputptr[i] = textInput;
                }
                for (int i; i < lineLength + 100; i++) {
                    printf("%c", textInputptr[i]);
                }
            break;

        }
    }

    free(textInput);
    return 0;
}
}