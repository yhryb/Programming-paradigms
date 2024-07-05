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
## Testing plan
<img width="776" alt="Screenshot 2024-07-05 at 16 18 35" src="https://github.com/yhryb/Programming-paradigms/assets/155826018/debb382f-3c4a-40e3-9052-9a3dd57e1201">
<img width="641" alt="Screenshot 2024-07-05 at 16 18 13" src="https://github.com/yhryb/Programming-paradigms/assets/155826018/60626507-9ef6-4fc3-baf1-f66fa2f3d973">

