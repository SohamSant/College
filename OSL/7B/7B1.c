#include <stdio.h>
#include <sys/ipc.h>		// Include header file for IPC functions and data structures
#include <sys/shm.h>		// Include header file for shared memory and data structures
#include <string.h>

int main() 
{
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);	
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);	
    if (shmid == -1) 
    {
        perror("shmget");
        return 1;
    }
    char *str = (char*)shmat(shmid, (void*)0, 0); 
    printf("Write Data : ");
    fgets(str, 1024, stdin);	 
    printf("Data written in memory: %s\n", str); 
    // Detach from shared memory
    shmdt(str); 
    return 0;
}
