//
// Created by MacUser on 01.06.2024.
//
#include <iostream>
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
    int backupCount;
    char* backupLinesptr[MAX_TEXT_LENGTH];
    int redoCount;
    char* redoLinesptr [MAX_TEXT_LENGTH];
    char* copiedTextptr;
    int copiedLineCount;
    int copiedTextLength;

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
        BackupState();
        ClearRedo();
        std::cout << "Enter text to append: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0'; //removing new line character
        textBufferptr[lineCount] = new char[strlen(textInput) + 1];
        strcpy(textBufferptr[lineCount], textInput);
        textLinesptr[lineCount] = textBufferptr[lineCount];
        lineCount++;
    }

    void NewLine() {
        BackupState();
        ClearRedo();
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
        BackupState();
        ClearRedo();
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
            textBufferptr[lineNumber] = newLineptr;
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

    void ReplaceText() {
        BackupState();
        ClearRedo();
        std::cout << "Enter text to replace: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0';
        char replacementText[MAX_TEXT_LENGTH]; //holds replacement text
        std::cout << "Enter new text: \n";
        std::cin.getline(replacementText, sizeof(replacementText));
        replacementText[strcspn(replacementText, "\n")] = '\0';
        for (int i = 0; i< lineCount; i++) { //iterating through the text to find the searched text
            char* positionptr = strstr(textLinesptr[i], textInput);
            if (positionptr) { //validation of whether does the text exist or not
                int index = positionptr - textLinesptr[i]; //index of the position of the text to replace
                int searchedTextLength = strlen(textInput);
                int replacementTextLength = strlen(replacementText);
                int afterLength = strlen(textLinesptr[i]) - searchedTextLength + replacementTextLength;
                char* newLineptr = new char[afterLength + 1];
                strncpy(newLineptr, textLinesptr[i], index); //copying the part of the line before the text to replace
                strcpy(newLineptr + index, replacementText); //copying the replacement text into the new line
                strcpy(newLineptr + replacementTextLength, textLinesptr[i] + index + searchedTextLength); //copying the part after the replacement text
                delete[] textLinesptr[i];
                textLinesptr[i] = newLineptr;
                textBufferptr[i] = newLineptr;
            }
        }
    }

    void BackupState() {
        for (int i = 0; i < lineCount; i++) {
            backupLinesptr[i] = new char[strlen(textLinesptr[i]) + 1];
            strcpy(backupLinesptr[i], textLinesptr[i]);
        }
        backupCount = lineCount;
    }

    void ClearRedo() {
        for (int i = 0; i < redoCount; i++) {
            delete[] redoLinesptr[i];
        }
        redoCount = 0;
    }

    void Undo() {
        ClearRedo();
        for (int i = 0; i < lineCount; i++) { //saving the current state to redo buffer
            redoLinesptr[i] = new char[strlen(textLinesptr[i]) + 1];
            strcpy(redoLinesptr[i], textLinesptr[i]);
        }
        redoCount = lineCount;
        for (int i = 0; i < lineCount; i++) { //deleting the last actions on textLinesptr
            delete[] textLinesptr[i];
        }
        for (int i = 0; i < backupCount; i++) { //use the backup text
            textLinesptr[i] = backupLinesptr[i];
        }
        lineCount = backupCount;
    }

    void Redo() {
        BackupState();
        for (int i = 0; i < lineCount; i++) {
            delete[] textLinesptr[i];
        }
        for (int i = 0; i < redoCount; i++) {
            textLinesptr[i] = redoLinesptr[i];
        }
        lineCount = redoCount;
        ClearRedo();
    }

    void Delete() {
        BackupState();
        ClearRedo();
        std::cout << "Enter text to delete: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0';
        for (int i = 0; i < lineCount; i++) {
            char* positionptr = strstr(textLinesptr[i], textInput);
            if (positionptr) {
                int index = positionptr - textLinesptr[i];
                int searchTextLength = strlen(textInput);
                int afterLength = strlen(textLinesptr[i]) - searchTextLength;
                char* newLineptr = new char[afterLength + 1];
                strncpy(newLineptr, textLinesptr[i], index);
                strcpy(newLineptr + index, textLinesptr[i] + index + searchTextLength);
                delete[] textLinesptr[i];
                textLinesptr[i] = newLineptr;
                textBufferptr[i] = newLineptr;
            }
        }
    }

    void CopyText() {
        std::cout << "Enter the line number and starting index to copy from: \n";
        int lineNumber, startIndex, endIndex;
        std::cin >> lineNumber >> startIndex;
        std::cout << "Enter the ending index: \n";
        std::cin >> endIndex;
        std::cin.ignore();
        if (lineNumber < 0 || lineNumber >= lineCount) {
            std::cout << "Line number can not be negative.\n";
        } else if (startIndex < 0 || endIndex > strlen(textLinesptr[lineNumber])) {
            std::cout << "Index number can not be negative.\n";
        } else {
            if (copiedTextptr != nullptr) {
                delete[] copiedTextptr;
            }
            copiedTextLength = endIndex - startIndex + 1;
            copiedTextptr = new char[copiedTextLength + 1];
            strncpy(copiedTextptr, textLinesptr[lineNumber] + startIndex, copiedTextLength);
            copiedTextptr[copiedTextLength] = '\0';
            std::cout << "Copied text: " << copiedTextptr << "\n";
        }
    }

    void PasteText() {
        BackupState();
        ClearRedo();
        int lineNumber, startIndex, endIndex;
        std::cout << "Enter the line number and index to paste at: \n";
        int symbolIndex;
        std::cin >> lineNumber >> symbolIndex;
        std::cin.ignore();
        if (lineNumber < 0 || lineNumber >= lineCount) {
            std::cout << "Line number can not be negative.\n";
        } else if (startIndex < 0 || endIndex > strlen(textLinesptr[lineNumber])) {
            std::cout << "Index number can not be negative.\n";
        } else {
            int beforeLength = strlen(textLinesptr[lineNumber]);
            char* newLineptr = new char[beforeLength + copiedTextLength + 1];
            strncpy(newLineptr, textLinesptr[lineNumber], symbolIndex);
            strcpy(newLineptr + symbolIndex, copiedTextptr);
            strcpy(newLineptr + symbolIndex + copiedTextLength, textLinesptr[lineNumber] + symbolIndex);
            delete[] textLinesptr[lineNumber];
            textLinesptr[lineNumber] = newLineptr;
            textBufferptr[lineNumber] = newLineptr;
        }
    }

    void RunProgram() {
        int command;
        while (running) {
            std::cout << "Choose the command (1-14): \n";
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
                case 9: //undoing
                    Undo();
                break;
                case 10: //redoing
                    Redo();
                break;
                case 11:
                    Delete();
                break;
                case 12:
                    CopyText();
                break;
                case 13:
                    PasteText();
                break;
                case 14: //replacing
                    ReplaceText();
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

