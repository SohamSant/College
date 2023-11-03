#include <stdio.h>
#include <stdlib.h>

void displayArray(int arr[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Convert command line argument to array
    int size = argc - 1;
    int arr[size];

    for (int i = 1; i < argc; i++) {
        arr[i - 1] = atoi(argv[i]);
    }

    // Display the array in reverse order
    printf("Array in reverse order: ");
    displayArray(arr, size);

    return 0;
}
