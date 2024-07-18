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
### g++ -o main CLI.cpp TextEditor.cpp CaesarCipher.cpp -ldl
### ./main

# Assignment 5 command line
### g++ -o interpreter main.cpp
### python3 test_script.py
Test passed for input:
5 + 3 * 2

Test passed for input:
max(5, 2)

Test passed for input:
min(3, 4)

Test passed for input:
max(min(3 * 2, 2), 2)
