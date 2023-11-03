#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void bbsort(int arr[15],int n){
    int temp;
    for(int i =0; i<n-1;i++){
        for(int j =0 ; j< n-i-1;j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

}


int main(){
    int arr[15],n;
    int p;
    printf("\nEnter the size of the array:");
    scanf("%d",&n);
    printf("\nEnter the Numbers :");
    for(int i =0 ; i<n;i++){
        scanf("%d",&arr[i]);
    }
    bbsort(arr,n);
    p=fork();

   if (p == 0) {
        sleep(2);
        // CHILD PROCESS
        printf("\n\nIn Child Process\n");
        printf("The Sorted order:");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }

        // Execute the child program with the sorted array as command-line arguments
        char sortedArray[15][10];  // Assuming the maximum size of each number is 10 characters
        for (int i = 0; i < n; i++) {
            snprintf(sortedArray[i], sizeof(sortedArray[i]), "%d", arr[i]);
        }

        char *args[n + 2];  // n + 1 for the numbers and 1 for the NULL terminator
        args[0] = "./2b2";
        for (int i = 0; i < n; i++) {
            args[i + 1] = sortedArray[i];
        }
        args[n + 1] = NULL;

        printf("\nExecuting EXECVE ");
        execve(args[0], args, NULL);
        printf("\nCompleted Execve ");
        printf("\nExiting Child Process");  
    }
    
else{
        // PARENT PROCESS
        printf("\n\nIN PARENT PROCESS.Now Waiting");
        wait(NULL);
        printf("\n\nParent Process is complete.\n\nParent Exits...");
    }
    
    return 0;
}