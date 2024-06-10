//
// Created by MacUser on 01.06.2024.
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

#define MAX_TEXT_LENGTH 4096

class TextEditor {
private:
    char textInput[MAX_TEXT_LENGTH];
    char* textBufferptr[MAX_TEXT_LENGTH]; //pointers to lines
    char** textLinesptr; //pointers to pointers
    bool running;
    char filename[100]; //file name input
    int lineCount;

public:
    TextEditor () : running(true) {
        textLinesptr = new char*[MAX_TEXT_LENGTH];
        lineCount = 0;
    }

    ~TextEditor() {
        for (int i = 0; i < lineCount; i++) {
            delete[] textBufferptr[i];
        }
        delete[] textLinesptr;
    }

    void PrintMenu() {
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

    void InputText() {
        std::cout << "Enter text to append: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0'; //removing new line character
        textBufferptr[lineCount] = new char[strlen(textInput) + 1];
        strcpy(textBufferptr[lineCount], textInput);
        textLinesptr[lineCount] = textBufferptr[lineCount];
        lineCount++;
    }

    void NewLine() {
        textBufferptr[lineCount] = new char[1]; //allocating 1 byte for newline character at the place of the lineCount
        textBufferptr[lineCount][0] = '\n';
        textLinesptr[lineCount] = textBufferptr[lineCount];
        lineCount++;
    }

    void SaveFile() {
        std::cout << "Enter the file name for saving: \n" ;
        std::cin.getline(filename, sizeof(filename));
        textInput[strcspn(textInput, "\n")] = '\0';
        std::ofstream file(filename);
        for (int i = 0; i < lineCount; ++i) {
            file << textLinesptr[i] << '\n';
        }
        file.close();
    }

    void LoadFile() {
        std::cout << "Enter the file name for loading: \n" ;
        std::cin.getline(filename, sizeof(filename));
        std::ifstream file(filename);
        while (file.getline(textInput, sizeof(textInput))) {
            textBufferptr[lineCount] = new char[strlen(textInput) + 1]; //+1 for \n
            strcpy(textBufferptr[lineCount], textInput);
            textLinesptr[lineCount] = textBufferptr[lineCount];
            lineCount++;
        }
        file.close();
    }

    void PrintText() {
        for (int i = 0; i < lineCount; i++) {
            std::cout << textLinesptr[i];
        }
    }

    void InsertText() {
        int lineNumber, symbolIndex;
        std::cout << "Choose line and index: \n";
        std::cin >> lineNumber >> symbolIndex;
        std::cin.ignore();
        std::cout << "Enter text to insert: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0';
        if (lineNumber < 0 || lineNumber >= lineCount) {
            std::cout << "Line number can not be negative.\n";
        } else if (symbolIndex < 0 || symbolIndex > strlen(textLinesptr[lineNumber])) {
            std::cout << "Index number can not be negative.\n";
        } else {
            int beforeLength = strlen(textLinesptr[lineNumber]);
            int afterLength = strlen(textInput);
            char* newLineptr = new char[beforeLength + afterLength + 1];
            strncpy(newLineptr, textLinesptr[lineNumber], symbolIndex); //here we copy text from the starting line into buffer up to the intended index so that we can add new text after it
            strcpy(newLineptr + symbolIndex, textInput); //copies new inputted text at the intended index
            strcpy(newLineptr + symbolIndex + afterLength, textLinesptr[lineNumber] + symbolIndex); //copies the old text after the inserted text into buffer
            delete[] textLinesptr[lineNumber];
            textLinesptr[lineNumber] = newLineptr;
        }
    }

    void SearchText() {
        std::cout << "Enter text to search: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0';
        for (int i = 0; i < lineCount; i++) {
            if (strstr(textLinesptr[i], textInput)) {//strstr searches for first occurence
                std::cout << "Found in line " << i + 1 << "\n"; //i + 1 because computer counts from 0 and lineCount from 1
            }
        }
    }

    void RunProgram() {
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
                    InputText();
                break;
                case 2: //new line
                    NewLine();
                break;
                case 3: //saving a file
                    SaveFile();
                break;
                case 4: //loading a file
                    LoadFile();
                break;
                case 5: //printing the whole text
                    PrintText();
                break;
                case 6: //inserting
                    InsertText();
                break;
                case 7: //searching
                    SearchText();
                break;
                default:
                    std::cout << "The command is not implemented: \n";
                break;
            }
        }
    }
    };

int main() {
    TextEditor TextEditorObject;
    TextEditorObject.RunProgram();
    return 0;
}
