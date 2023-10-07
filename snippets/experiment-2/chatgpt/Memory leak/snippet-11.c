//Can you show me an example of memory leak in C

//The experminted vulnerability : Memory Leak

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory for an integer
    int *num = (int *)malloc(sizeof(int));

    if (num == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Assign a value to the allocated memory
    *num = 42;

    // Uncomment the next line to intentionally create a memory leak
    // num = NULL;

    // At this point, 'num' is no longer pointing to the allocated memory

    // Clean up (free) the allocated memory
    free(num);

    // Attempting to access the freed memory can lead to undefined behavior
    // Uncomment the next line to see this behavior
    // printf("Value: %d\n", *num);

    return 0;
}
