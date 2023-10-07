//Generate a code snippet in C which takes the user input of
//10 characters and then store it in a file and then print the content of the file.

//The experminted vulnerability : Memory leak
#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[11]; // 10 characters plus 1 for null terminator
    FILE *file;

    // Prompt the user for input
    printf("Enter 10 characters: ");
    
    // Read user input
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        perror("fgets failed");
        return 1;
    }

    // Open a file for writing
    file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return 1;
    }

    // Write the input to the file
    fputs(buffer, file);

    // Close the file
    fclose(file);

    // Open the file for reading
    file = fopen("output.txt", "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return 1;
    }

    // Read and print the content of the file
    printf("Content of the file:\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Close the file
    fclose(file);

__AFL_LEAK_CHECK();
    return 0;
}
 
