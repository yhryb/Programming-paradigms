//
// Created by MacUser on 29.06.2024.
//

#ifndef CLI_H
#define CLI_H
#include "Text.h"
#include "CaesarCipher.h"

class CLI {
private:
    CaesarCipher caesarCipher;
    Text text;
    bool running;

public:
    CLI();
    ~CLI();
    void RunProgram();
    void SaveFileWithEncryption();
    void LoadFileWithDecryption();
};



#endif //CLI_H
