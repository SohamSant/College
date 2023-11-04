#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int pid, p;
    p = fork();
    if (p == 0) {
        int n;
        printf("This is the Child Process\n");
        printf("Enter the number of integers: ");
        scanf("%d", &n);

        int childArr[n];

        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &childArr[i]);
        }

        printf("PID: %d\n", getpid());

        // Sorting the array in the child process
        bubbleSort(childArr, n);

        printf("Sorted integers by Child Process: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", childArr[i]);
        }
        printf("\n");

        printf("Parent's Process ID: %d\n\n", getppid());
    } else {
        int n;
        printf("This is the Parent Process\n");
        printf("Enter the number of integers: ");
        scanf("%d", &n);

        int parentArr[n];

        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &parentArr[i]);
        }

        sleep(5);
        printf("PID: %d\n", getpid());

        // Sorting the array in the parent process
        bubbleSort(parentArr, n);

        printf("Sorted integers by Parent Process: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", parentArr[i]);
        }
        printf("\n");

        printf("Child's Process ID: %d\n\n", p);
    }

    return 0;
}
