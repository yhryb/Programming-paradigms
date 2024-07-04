//
// Created by MacUser on 29.06.2024.
//

#include "CLI.h"
#include "CaesarCipher.h"
#include "Text.h"
#include <iostream>
#include <cstring>
#include <fstream>

#define MAX_TEXT_LENGTH 4096

CLI::CLI() : running(true) {
        std::cout << "Welcome to Text Editor. Here is what you can do:\n"
                      << "Ask for available commands - 0;\n"
                      << "Enter new text - 1;\n"
                      << "Start a new line - 2;\n"
                      << "Save a file - 3;\n"
                      << "Load a file - 4;\n"
                      << "Print the current text to console - 5;\n"
                      << "Insert the text by line and symbol index - 6;\n"
                      << "Search - 7;\n"
                        <<"Undo - 9;\n"
                        << "Redo - 10;\n"
                        << "Delete - 11;\n"
                        << "Copy - 12;\n"
                        << "Paste - 13;\n"
                        << "Replace - 14;\n"
                        << "Encrypt - 15;\n"
                        << "Decrypt - 10;\n";
    }

CLI::~CLI() {

}

void CLI::RunProgram() {
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
                text.InputText();
            break;
            case 2: //new line
                text.NewLine();
            break;
            case 3: //saving a file
                text.SaveFile();
            break;
            case 4: //loading a file
                text.LoadFile();
            break;
            case 5: //printing the whole text
                text.PrintText();
            break;
            case 6: //inserting
                text.InsertText();
            break;
            case 7: //searching
                text.SearchText();
            break;
            case 9: //undoing
                text.Undo();
            break;
            case 10: //redoing
                text.Redo();
            break;
            case 11: //deleting
                text.Delete();
            break;
            case 12: //copying
                text.CopyText();
            break;
            case 13: //pasting
                text.PasteText();
            break;
            case 14: //replacing
                text.ReplaceText();
            break;
            case 15: { //encryption
                std::cout << "Enter filename for encrypting: ";
                char inputFile[100];
                std::cin.getline(inputFile, sizeof(inputFile));
                std::cout << "Enter filename for output: ";
                char outputFile[100];
                std::cin.getline(outputFile, sizeof(outputFile));
                int key = 0;
                std::cout << "Key: ";
                std::cin.ignore();
                caesarCipher.encryptFile(inputFile, outputFile, key);
                break;
            }
            case 16: { //decryption
                std::cout << "Enter filename for loading: ";
                char inputFile[100];
                std::cin.getline(inputFile, sizeof(inputFile));
                std::cout << "Enter filename for output: ";
                char outputFile[100];
                std::cin.getline(outputFile, sizeof(outputFile));
                int key = 0;
                std::cout << "Key: ";
                std::cin.ignore();
                caesarCipher.decryptFile(inputFile, outputFile, key);
                break;
            }
            default:
                std::cout << "The command is not implemented: \n";
            break;
        }
    }
}



