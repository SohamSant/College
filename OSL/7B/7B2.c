#include <stdio.h>
#include <sys/ipc.h>	// Include header file for IPC functions and data structures
#include <sys/shm.h>	// Include header file for shared memory and data structures

int main() {
    // ftok to generate a unique key
    key_t key = ftok("shmfile", 65);	
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); 
    if (shmid == -1) {
        perror("shmget");
        return 1;
    } 
    char *str = (char*)shmat(shmid, (void*)0, 0); 
    printf("Data read from memory: %s\n", str); 
    // Detach from shared memory
    shmdt(str); 
    // Destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL); 
    return 0;
}
