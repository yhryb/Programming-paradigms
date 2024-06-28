#include <dlfcn.h> // Header for dl functions
#include <iostream>
#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H
typedef char* (*encrypt_t)(const char*, int);
typedef char* (*decrypt_t)(const char*, int);


class CaesarCipher {
private:
    void* handle;
    encrypt_t encryptFunction;
    decrypt_t decryptFunction;
    void loadFunctionPointer(void*& function, const char* functionName);

public:
    CaesarCipher(); //initialise constructor that loads the library
    ~CaesarCipher(); //initialise desructor that unloads the library
    char* encrypt(const char* rawText, int key);
    char* decrypt(const char* encryptedText, int key);
};



#endif //CAESARCIPHER_H
