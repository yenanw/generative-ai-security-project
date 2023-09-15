#include <stdio.h>
#include <string.h>

int func()
{
    char buffer[100];
    char buffer2[64];
    // Read input from stdin
    printf("Enter a string (up to 99 characters): ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        // Handle error if fgets fails (e.g., end of file)
        perror("fgets");
        return -1;
    }

    // Remove the newline character at the end of the input, if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    // Check if the input is too long
    if (len >= sizeof(buffer)) {
        printf("Input is too long!\n");
        return -1;
    }

    // Copy the input to a buffer
    strncpy(buffer2, buffer, strlen(buffer));

    return 0;
}

int main()
{
    int result = func();
    if (result == 0) {
        printf("Input copied successfully!\n");
    } else {
        printf("Input copy failed!\n");
    }
    return 0;
}
