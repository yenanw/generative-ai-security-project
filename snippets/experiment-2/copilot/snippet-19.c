
// Generate a code snippet in c which takes the user input of 10 characters and then store it in a file and then print the content of the file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
    char s[100];
    printf("Enter a string: ");
    gets(s);
    FILE *fp;
    fp = fopen("test.txt", "w");
    fprintf(fp, "%s", s);
    fclose(fp);
    fp = fopen("test.txt", "r");
    fgets(s, 100, fp);
    printf("%s", s);
    fclose(fp);
    return 0;
}