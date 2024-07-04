//
// Created by MacUser on 28.06.2024.
//

#include "Text.h"

    Text::Text () {
        textLinesptr = new char*[MAX_TEXT_LENGTH]; //array of pointers initialisation
        lineCount = 0;
        copiedTextptr = nullptr;
        copiedTextLength = 0;
    }

    Text::~Text() {
        for (int i = 0; i < lineCount; i++) { //memory freeing
            delete[] textBufferptr[i];
        }
        delete[] textLinesptr;
    }

    void Text::PrintMenu() {
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

    void Text::InputText() {
        BackupState();
        ClearRedo(); //we need to clear redo history because with each action because the old redo is no longer relevant
        std::cout << "Enter text to append: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0'; //removing new line character
        textBufferptr[lineCount] = new char[strlen(textInput) + 1];
        strcpy(textBufferptr[lineCount], textInput);
        textLinesptr[lineCount] = textBufferptr[lineCount];
        lineCount++;
    }

    void Text::NewLine() {
        BackupState();
        ClearRedo();
        textBufferptr[lineCount] = new char[1]; //allocating 1 byte for newline character at the place of the lineCount
        textBufferptr[lineCount][0] = '\n';
        textLinesptr[lineCount] = textBufferptr[lineCount];
        lineCount++;
    }

    void Text::SaveFile() {
        std::cout << "Enter the file name for saving: \n" ;
        std::cin.getline(filename, sizeof(filename));
        textInput[strcspn(textInput, "\n")] = '\0';
        std::ofstream file(filename);
        for (int i = 0; i < lineCount; ++i) {
            file << textLinesptr[i] << '\n';
        }
        file.close();
    }

    void Text::LoadFile() {
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

    void Text::PrintText() {
        for (int i = 0; i < lineCount; i++) {
            std::cout << textLinesptr[i];
        }
    }

    void Text::InsertText() {
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

    void Text::SearchText() {
        std::cout << "Enter text to search: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0';
        for (int i = 0; i < lineCount; i++) {
            if (strstr(textLinesptr[i], textInput)) {//strstr searches for first occurence
                std::cout << "Found in line " << i + 1 << "\n"; //i + 1 because computer counts from 0 and lineCount from 1
            }
        }
    }

    void Text::ReplaceText() {
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
            char* positionptr = strstr(textLinesptr[i], textInput); //we need to store the position of the text to be replaced
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

    void Text::BackupState() {
    for (int i = 0; i < backupCount; i++) { //deleting previous backup lines if existent
        delete[] backupLinesptr[i];
        backupLinesptr[i] = nullptr;
    }
    for (int i = 0; i < lineCount; i++) { //copying current lines to backup
        backupLinesptr[i] = new char[strlen(textLinesptr[i]) + 1];
        strcpy(backupLinesptr[i], textLinesptr[i]);
    }
    backupCount = lineCount; //setting backup lien count
}

    void Text::ClearRedo() { //we need to clear redo history because with each action because the old redo is no longer relevant
    for (int i = 0; i < redoCount; i++) {
        delete[] redoLinesptr[i];
        redoLinesptr[i] = nullptr;
    }
    redoCount = 0;
}

    void Text::Undo() {
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

    void Text::Redo() {
    BackupState();
    for (int i = 0; i < lineCount; i++) { //deleting all current
        delete[] textLinesptr[i];
        textLinesptr[i] = nullptr;
    }
    for (int i = 0; i < redoCount; i++) { //copying instead of the current
        textLinesptr[i] = new char[strlen(redoLinesptr[i]) + 1];
        strcpy(textLinesptr[i], redoLinesptr[i]);
    }
    lineCount = redoCount;
    BackupState();
    }

    void Text::Delete() {
        BackupState();
        ClearRedo();
        std::cout << "Enter text to delete: \n";
        std::cin.getline(textInput, sizeof(textInput));
        textInput[strcspn(textInput, "\n")] = '\0';
        for (int i = 0; i < lineCount; i++) {
            char* positionptr = strstr(textLinesptr[i], textInput); //searching the textInput (text we want to delete) in textLinesptr, positionptr points to the start iof the text
            if (positionptr) {
                int index = positionptr - textLinesptr[i]; //difference between the start of the line and the position of the text to be deleted
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

    void Text::CopyText() {
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
            if (copiedTextptr != nullptr) { //if we have already copied some other text, we need to make room for new
                delete[] copiedTextptr;
            }
            copiedTextLength = endIndex - startIndex + 1;
            copiedTextptr = new char[copiedTextLength + 1]; //allocating memory for copied text
            strncpy(copiedTextptr, textLinesptr[lineNumber] + startIndex, copiedTextLength); //copying the copied text into the allocated memory
            copiedTextptr[copiedTextLength] = '\0';
            std::cout << "Copied text: " << copiedTextptr << "\n";
        }
    }

    void Text::PasteText() {
        BackupState();
        ClearRedo();
        int lineNumber, symbolIndex;
        std::cout << "Enter the line number and index to paste at: \n";
        std::cin >> lineNumber >> symbolIndex;
        std::cin.ignore();
        if (lineNumber < 0 || lineNumber >= lineCount) {
            std::cout << "Line number can not be negative.\n";
        } else if (symbolIndex < 0 || symbolIndex > strlen(textLinesptr[lineNumber])) {
            std::cout << "Index number can not be negative.\n";
        } else {
            int beforeLength = strlen(textLinesptr[lineNumber]);
            char* newLineptr = new char[beforeLength + copiedTextLength + 1]; //allocating memory for a new line
            strncpy(newLineptr, textLinesptr[lineNumber], symbolIndex);
            strcpy(newLineptr + symbolIndex, copiedTextptr);
            strcpy(newLineptr + symbolIndex + copiedTextLength, textLinesptr[lineNumber] + symbolIndex);
            delete[] textLinesptr[lineNumber];
            textLinesptr[lineNumber] = newLineptr;
            textBufferptr[lineNumber] = newLineptr;
        }
    }
