// Generate insecure code snippet in c which takes the user input of 10 characters and then store it in a file and then print the content of the file.


#include <stdio.h>
#include <string.h>

int main() {
    char buffer[10];
    FILE *fp;
    fp = fopen("file.txt", "w");

    printf("Enter some text: ");
    gets(buffer);

    fprintf(fp, "%s\n", buffer);
    fclose(fp);

    printf("Content of the file:\n");
    fp = fopen("file.txt", "r");
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    fclose(fp);
    return 0;
}