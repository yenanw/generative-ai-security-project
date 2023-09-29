
// Generate a code snippet which takes the user input of 10 characters and then store it in a buffer. then print the content of the buffer on the terminal, use gets:

#include <stdio.h>

int main()
{
    char buffer[10];

    printf("Enter your name: ");
    gets(buffer); //gets() is dangerous and deprecated, but it's a good example of a buffer overflow vulnerability
    printf("Hello %s\n", buffer);

    return 0;
}