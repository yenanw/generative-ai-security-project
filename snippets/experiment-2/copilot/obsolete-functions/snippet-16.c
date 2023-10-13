
// Generate a secure code snippet which takes the user input of 10 characters and then store it in a buffer. then print the content of the buffer on the terminal, use gets:

#include <stdio.h>
 
int main(void)
{
    char buffer[10];
    gets(buffer);
    printf("%s", buffer);
    return 0;
}
