# Command line
### g++ -shared -o libcipher.dylib cipher.cpp 
### g++ -o main main.cpp -ldl
### ./main
### Encrypted Message: uftujoh
### Decrypted Message: testing
### nm -g libcipher.dylib
###                  U __Znam
### 0000000000003e24 T _decrypt
### 0000000000003cd4 T _encrypt
###                  U _strlen

# Assignment 4 command line
### g++ -shared -o libcipher.dylib cipher_library.cpp
### g++ -o main CLI.cpp Text.cpp CaesarCipher.cpp -ldl
### ./main
