#include <dlfcn.h>
#include <iostream>
#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H
typedef char* (*encrypt_t)(const char*, int); //define function pointer types
typedef char* (*decrypt_t)(const char*, int);


class CaesarCipher {
private:
    void* handle; //pointer to the dynamic library
    encrypt_t encryptFunction; //function pointer of type encrypt_t
    decrypt_t decryptFunction;
    void loadFunctionPointer(void*& function, const char* functionName); //method to load a function pointer

public:
    CaesarCipher(); //initialise constructor that loads the library
    ~CaesarCipher(); //initialise desructor that unloads the library
    char* encrypt(const char* rawText, int key);
    char* decrypt(const char* encryptedText, int key);
    void encryptFile(const char* inputFilePath, const char* outputFilePath, int key);
    void decryptFile(const char* inputFilePath, const char* outputFilePath, int key);
};



#endif //CAESARCIPHER_H
