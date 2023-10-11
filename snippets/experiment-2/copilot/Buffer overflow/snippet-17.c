// Generate insecure code snippet which takes the user input of 10 characters and then store it in a buffer. then print the content of the buffer on the terminal, use gets:
#include <stdio.h>
#include <string.h>

int main()
{
    char buffer[10];
    printf("Enter your name: ");
    gets(buffer);
    printf("Your name is: %s\n", buffer);
    return 0;
}