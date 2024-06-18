#include <stdio.h>
#include <dlfcn.h>
#include <iostream>

extern "C" {
    char* encrypt(const char* rawText, int key);
    char* decrypt(const char* encryptedText, int key);
}

int main() {
    // Load the dynamic library
    void* handle = dlopen("./libcipher.dylib", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    // Load the function from the library
    typedef char* (*encrypt_t)(const char*, int);
    encrypt_t encrypt = (encrypt_t)dlsym(handle, "encrypt");
    if (!encrypt) {
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    typedef char* (*decrypt_t)(const char*, int);
    decrypt_t decrypt = (decrypt_t)dlsym(handle, "decrypt");
    if (!decrypt) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    // Call the function
    char functionChoice;
    int key;
    char input[100];

    std::cout << "Encrypt/Decrypt: ";
    std::cin >> functionChoice;
    std::cin.ignore();

    if (functionChoice == 'Encrypt') {
        std::cout << "Message to encrypt: ";
        std::cin.getline(input, sizeof(input));
        std::cout << "Key: ";
        std::cin >> key;
        std::cin.ignore();
        char* encrypted_message = encrypt(input, key);
        std::cout << "Encrypted Message: " << encrypted_message << std::endl;
        delete[] encrypted_message;
    }
    else if (functionChoice == 'Decrypt') {
        std::cout << "Message to decrypt: ";
        std::cin.getline(input, sizeof(input));
        std::cout << "Key: ";
        std::cin >> key;
        std::cin.ignore();
        char* decrypted_message = decrypt(input, key);
        std::cout << "Decrypted Message: " << decrypted_message << std::endl;
        delete[] decrypted_message;
    }

    // Close the library
    dlclose(handle);
    return 0;
}

