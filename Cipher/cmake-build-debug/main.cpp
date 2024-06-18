#include <stdio.h>
#include <dlfcn.h>

int main()
{
    char* message = "hello world";
    int key = 3;
    char* encrypted_message = encrypt(message, key);
    std::cout << "Encrypted Message: " << encrypted_message << std::endl;
    delete[] encrypted_message;
    return 0;
}
