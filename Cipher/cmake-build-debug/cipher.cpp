#include <iostream>
#include <cstring>

const char ALPHABET[] = "abcdefghijklmnopqrstuvwxyz";
const int ALPHABET_SIZE = 26;

char* encrypt(char* rawText, int key) {
    char* ciphertext = new char[std::strlen(rawText) + 1];
    int position = 0;
    for (size_t i = 0; i < std::strlen(rawText); i++) {
        char character = rawText[i];
        for (int m = 0; m < ALPHABET_SIZE; m++) {
            if (ALPHABET[m] == character) {
                position = m;
            }
        }
        int cipherPosition = (position + key) % ALPHABET_SIZE; //ensures that the number doesnt go beyond 26 (25 + 3 = 2)
        ciphertext[i] = ALPHABET[cipherPosition];
    }
    ciphertext[std::strlen(rawText)] = '\0';
    return ciphertext;
}

char* decrypt(char* encryptedText, int key) {
    char* deciphertext = new char[std::strlen(encryptedText) + 1];
    int position = 0;
    for (size_t i = 0; i < std::strlen(encryptedText); i++) {
        char character = encryptedText[i];
        for (int m = 0; m < ALPHABET_SIZE; m++) {
            if (ALPHABET[m] == character) {
                position = m;
            }
        }
        int cipherPosition = (position - key) % ALPHABET_SIZE; //ensures that the number doesnt go beyond 26 (25 + 3 = 2)
        deciphertext[i] = ALPHABET[cipherPosition];
    }
    deciphertext[std::strlen(encryptedText)] = '\0';
    return deciphertext;
}
