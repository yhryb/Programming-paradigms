//
// Created by MacUser on 28.06.2024.
//

#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include <fstream>
#include <cstring>
#define MAX_TEXT_LENGTH 4096


class Text {
private:
    char textInput[MAX_TEXT_LENGTH];
    char* textBufferptr[MAX_TEXT_LENGTH]; //pointers to lines
    char** textLinesptr; //pointers to pointers
    char filename[100]; //file name input
    int lineCount;
    int backupCount; //backup line count
    char* backupLinesptr[MAX_TEXT_LENGTH]; //array of backup pointers
    int redoCount; //redo line count
    char* redoLinesptr[MAX_TEXT_LENGTH]; //array of redo pointers
    char* copiedTextptr; //pointer to the copied text
    int copiedLineCount; //line number of the copied text
    int copiedTextLength;

public:
    Text();
    ~Text();
    void PrintMenu();
    void InputText();
    void NewLine();
    void SaveFile();
    void LoadFile();
    void PrintText();
    void InsertText();
    void SearchText();
    void ReplaceText();
    void BackupState();
    void ClearRedo();
    void Undo();
    void Redo();
    void Delete();
    void CopyText();
    void PasteText();
};



#endif //TEXT_H
