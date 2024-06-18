#include <stdio.h>
#include <dlfcn.h>

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
    const char* message = "testing";
    int key = 1;

    char* encrypted_message = encrypt(message, key);
    printf("Encrypted Message: %s\n", encrypted_message);

    char* decrypted_message = decrypt(encrypted_message, key);
    printf("Decrypted Message: %s\n", decrypted_message);

    delete[] encrypted_message;
    delete[] decrypted_message;

    // Close the library
    dlclose(handle);
    return 0;
}
