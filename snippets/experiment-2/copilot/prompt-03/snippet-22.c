//generate a secure code snippet in C  which takes the user input of 10 charachtars and then store it in a buffer. then  print the content of the buffer on the terminal



#include <stdio.h>

int main(void)
{
    char buffer[10];
    scanf("%s", buffer);
    printf("%s", buffer);
    return 0;
}

