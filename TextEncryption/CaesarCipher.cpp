//
// Created by MacUser on 28.06.2024.
//

#include "CaesarCipher.h"
#include <fstream>

CaesarCipher::CaesarCipher() {
    handle = dlopen("./libcipher.dylib", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }
    loadFunctionPointer((void*&)encryptFunction, "encrypt"); //loading function pointer
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

char* CaesarCipher::decrypt(const char* encryptedText, int key) {
    return decryptFunction(encryptedText, key);
}

void CaesarCipher::encryptFile(const char* inputFilePath, const char* outputFilePath, int key) { //encrypting file
    std::ifstream inputFile(inputFilePath, std::ios::binary); //binary to allow encrypting byte sequences of any size
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputFilePath;
    }
    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilePath;
        inputFile.close();
    }
    inputFile.seekg(0, std::ios::end); //moves the reading position to the end of the file to calculate its size
    std::streamsize size = inputFile.tellg(); //gets size of the file
    inputFile.seekg(0, std::ios::beg); //moves to the beginning
    char* fileBuffer = new char[size]; //allocates memory for size of the file
    if (inputFile.read(fileBuffer, size)) {
        char* encryptedBuffer = encrypt(fileBuffer, key); //encrypting the file
        outputFile.write(encryptedBuffer, strlen(encryptedBuffer)); //writing encrypted content into the output file
        delete[] encryptedBuffer;
    } else {
        std::cerr << "Failed to read input file: " << inputFilePath;
        delete[] fileBuffer;
        inputFile.close();
        outputFile.close();
    }
    delete[] fileBuffer;
    inputFile.close();
    outputFile.close();
}

void CaesarCipher::decryptFile(const char* inputFilePath, const char* outputFilePath, int key) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputFilePath;
    }
    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilePath;
        inputFile.close();
    }
    inputFile.seekg(0, std::ios::end);
    std::streamsize size = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    char* fileBuffer = new char[size];
    if (inputFile.read(fileBuffer, size)) {
        char* decryptedBuffer = decrypt(fileBuffer, key);
        outputFile.write(decryptedBuffer, strlen(decryptedBuffer));
        delete[] decryptedBuffer;
    } else {
        std::cerr << "Failed to read input file: " << inputFilePath;
        delete[] fileBuffer;
        inputFile.close();
        outputFile.close();
    }
    delete[] fileBuffer;
    inputFile.close();
    outputFile.close();
}