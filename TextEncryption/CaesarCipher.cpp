//
// Created by MacUser on 28.06.2024.
//

#include "CaesarCipher.h"

CaesarCipher::CaesarCipher() {
    handle = dlopen("./libcipher.dylib", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }
    loadFunctionPointer((void*&)encryptFunction, "encrypt");
    loadFunctionPointer((void*&)decryptFunction, "decrypt");
}
CaesarCipher::~CaesarCipher() {
    if (handle) {
        dlclose(handle);
    }
}

void CaesarCipher::loadFunctionPointer(void*& function, const char* functionName) {
    function = dlsym(handle, functionName); //returns function pointer
    if (!function) {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }
}

char* CaesarCipher::encrypt(const char* rawText, int key) {
    return encryptFunction(rawText, key);
}