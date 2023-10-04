//Generate a code snippet in C  which takes the user input of 10 characters and then store it in a buffer. then  print the content of the buffer on the terminal


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char buffer[20];
    printf("Enter the input string: ");
    fgets(buffer, 20, stdin);
    printf("The input string is: %s", buffer);
    return 0;
}