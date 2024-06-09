//
// Created by MacUser on 01.06.2024.
//
#include <iostream>
#include <cstdlib>
#include<cstring>
#include <fstream>

#define MAX_TEXT_LENGTH 4096

class textEditor {
private:
    char textInput[MAX_TEXT_LENGTH];
    char** textLinesptr = NULL;
    bool running;
    char filename[100]; //file name input
    FILE* fileptr;
    int lineCount = 0;

public:
    void printMenu() {
        std::cout << "Welcome to Text Editor. Here is what you can do:\n"
                      << "Ask for available commands - 0;\n"
                      << "Enter new text - 1;\n"
                      << "Start a new line - 2;\n"
                      << "Save a file - 3;\n"
                      << "Load a file - 4;\n"
                      << "Print the current text to console - 5;\n"
                      << "Insert the text by line and symbol index - 6;\n"
                      << "Search - 7;\n";
                      }

    void inputText() {
        std::cout << "Enter text to append: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0'; //removing new line character
        textLinesptr[lineCount] = new char[strlen(textInput) + 1];
        strcpy(textLinesptr[lineCount], textInput);
        lineCount++;
    }

    void newLine() {
        textLinesptr[lineCount] = new char[1]; //allocating 1 byte for newline character at the place of the lineCount
        textLinesptr[lineCount][0] = '\n';
        lineCount++;
    }

    void saveFile() {
        std::cout << "Enter the file name for saving: \n" ;
        std::cin.getline(filename, sizeof(filename));
        textInput[strcspn(textInput, "\n")] = '\0';
        std::ofstream file(filename);
        if (fileptr != nullptr) {
            for (int i = 0; i < lineCount; ++i) {
                file << textInput[i] << '\n';
            }
            file.close();
        }
    }

    void loadFile() {
        std::cout << "Enter the file name for loading: \n" ;
        std::cin.getline(filename, sizeof(filename));
        std::ifstream file(filename);
        textLinesptr[lineCount] = new char[strlen(textInput) + 1];
        strcpy(textLinesptr[lineCount], textInput);
        lineCount++;
    }

    void printText() {
        for (int i = 0; i < lineCount; i++) {
            std::cout << textLinesptr[i];
        }
    }

    void insertText() {
        int lineNumber, symbolIndex;
        std::cout << "Choose line and index: \n";
        std::cin >> lineNumber >> symbolIndex;
        textInput[strcspn(textInput, "\n")] = '\0';
        printf("Enter text to insert: \n");
        std::cin.getline(filename, sizeof(filename));
        textInput[strcspn(textInput, "\n")] = '\0';
        if (lineNumber < 0 || lineNumber >= lineCount) {
            std::cout << "Line number can not be negative.\n";
        } else if (symbolIndex < 0 || symbolIndex > strlen(textLinesptr[lineNumber])) {
            std::cout << "Index number can not be negative.\n";
        } else {
            int beforeLength = strlen(textLinesptr[lineNumber]);
            int afterLength = beforeLength + strlen(textInput);
            memmove(textLinesptr[lineNumber] + symbolIndex + strlen(textInput), textLinesptr[lineNumber] + symbolIndex, beforeLength - symbolIndex + 1);
            memcpy(textLinesptr[lineNumber] + symbolIndex, textInput, strlen(textInput));
        }
    }

    void searchText() {
        std::cout << "Enter text to search: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0';
        for (int i = 0; i < lineCount; i++) {
            if (strstr(textLinesptr[i], textInput)) {//strstr searches for first occurence
                std::cout << "Found in line" << i + 1 << "\n"; //i + 1 because computer counts from 0 and lineCount from 1
            }
        }
    }

    void runProgram() {
        int command;
        while (running) {
            std::cout << "Choose the command (1-7): \n";
            std::cin >> command; //scans the inputted command
            std::cin.ignore(); //consumes leftover so that input is allowed
            switch (command) {
                case 0:
                    running = false;
                break;
                case 1: //new text
                    inputText();
                break;
                case 2: //new line
                    newLine();
                break;
                case 3: //saving a file
                    saveFile();
                break;
                case 4: //loading a file
                    loadFile();
                break;
                case 5: //printing the whole text
                    printText();
                break;
                case 6: //inserting
                    insertText();
                break;
                case 7: //searching
                    searchText();
                break;
                default:
                    std::cout << "The command is not implemented: \n";
                break;
            }
        }
    }
    };

int main() {
    textEditor textEditorObject;
    textEditorObject.runProgram;
    return 0;
}
