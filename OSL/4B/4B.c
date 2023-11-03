#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>  // Added for intptr_t

sem_t wrt;              // Semaphore for writers
pthread_mutex_t mutex;   // Mutex for protecting shared variables
int shared, readcount = 0;  // Shared variable and reader count

void* readers(void* arg)
{
    intptr_t i = (intptr_t)arg;  // Convert void pointer to intptr_t for thread ID
    while (1)
    {
        sleep(rand() % 10);
        pthread_mutex_lock(&mutex);
        readcount++;
        printf("\nReader %ld arrives\n", i);  // Print reader arrival
        if (readcount == 1)
        {
            printf("-------------------------------------------------\n");
            printf("\nReader %ld is the first reader....", i);
            printf("...Writers are blocked\n");
            sem_wait(&wrt);  // Block writers if this is the first reader
        }
        printf("\nReadcount: %d", readcount);
        pthread_mutex_unlock(&mutex);

        printf("\nReader %ld reads %d", i, shared);
        sleep(2);

        pthread_mutex_lock(&mutex);
        readcount--;
        printf("\nReader %ld is leaving!", i);
        printf("\nReadcount: %d", readcount);
        if (readcount == 0)
        {
            printf("\nReader %ld is the last reader!\nEnabling writers!\n", i);
            printf("-------------------------------------------------\n");
            sem_post(&wrt);  // Release writers if this is the last reader
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* writers(void* arg)
{
    intptr_t i = (intptr_t)arg;  // Convert void pointer to intptr_t for thread ID
    while (1)
    {
        sem_wait(&wrt);  // Wait for access to the shared resource
        shared = rand() % 10;  // Write to the shared resource
        printf("-------------------------------------------------\n");
        printf("\nWriter %ld is entering", i);
        printf("\nWriter %ld is writing %d", i, shared);
        printf("\nWriter %ld is leaving!\n", i);
        printf("-------------------------------------------------\n");
        sem_post(&wrt);  // Release access to the shared resource
        sleep(rand() % 10);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t* reader, *writer;  // Arrays to hold reader and writer threads
    int rd_count, wr_count;
    intptr_t i;  // Loop variable for thread creation

    printf("\nEnter reader count => ");
    scanf("%d", &rd_count);

    printf("\nEnter writer count => ");
    scanf("%d", &wr_count);

    sem_init(&wrt, 0, 1);  // Initialize semaphore for writers with initial value 1
    pthread_mutex_init(&mutex, NULL);  // Initialize mutex

    reader = (pthread_t*)malloc(rd_count * sizeof(pthread_t));  // Allocate memory for reader threads
    writer = (pthread_t*)malloc(wr_count * sizeof(pthread_t));  // Allocate memory for writer threads

    for (i = 0; i < rd_count; i++)
    {
        pthread_create(&reader[i], NULL, readers, (void*)i);  // Create reader threads
        printf("\nReader %ld starting!\n", i);
    }

    for (i = 0; i < wr_count; i++)
    {
        pthread_create(&writer[i], NULL, writers, (void*)i);  // Create writer threads
        printf("\nWriter %ld starting!\n", i);
    }

    for (i = 0; i < rd_count; i++)
    {
        pthread_join(reader[i], NULL);  // Wait for reader threads to finish
        printf("\nReader %ld joined!\n", i);
    }

    for (i = 0; i < wr_count; i++)
    {
        pthread_join(writer[i], NULL);  // Wait for writer threads to finish
        printf("\nWriter %ld joined!\n", i);
    }

    return 0;
}
