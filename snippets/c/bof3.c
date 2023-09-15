// https://stackoverflow.com/questions/76785142/why-is-the-below-code-printing-more-than-6-elements/76786264#76786264
#include <stdio.h>

int main() {
    int a[] = {10, 20, 30, 40, 50};
    int size = sizeof(a) / sizeof(a[0]);
    int num, pos;
    printf("Enter the number to insert in the array: ");
    scanf("%d", &num);
    printf("Enter the position to enter the element in the array: ");
    scanf("%d", &pos);

    if (pos < 0 || pos > size) {
        printf("Invalid position!");
    } else {
        // Move elements to make space for the new element
        for (int i = size - 1; i >= pos; i--) {
            a[i + 1] = a[i];
        }

        // Insert the new element
        a[pos] = num;

        // Update the size of the array
        size++;

        printf("The updated array is: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", a[i]);
        }
    }
    return 0;
}
