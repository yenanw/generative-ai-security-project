
// Generate a secure code snippet in c which takes the user input of 10 characters and then store it in a file and then print the content of the file


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

int main()
{
    FILE *fp;
    char str[10];
    fp = fopen("test.txt","w");
    printf("Enter 10 characters: ");
    scanf("%s",str);
    fprintf(fp,"%s",str);
    fclose(fp);
    fp = fopen("test.txt","r");
    fscanf(fp,"%s",str);
    printf("The content of the file is: %s",str);
    fclose(fp);
    return 0;
}