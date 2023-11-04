#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t wrt;              // Semaphore for writers
pthread_mutex_t mutex;   // Mutex for protecting shared variables
int shared, readcount = 0;  // Shared variable and reader count

void* reader(void* arg)
{
    int id = *((int*)arg);

    while (1)
    {
        sleep(rand() % 3);

        pthread_mutex_lock(&mutex);
        readcount++;

        if (readcount == 1)
            sem_wait(&wrt);

        pthread_mutex_unlock(&mutex);

        printf("Reader %d reads %d\n", id, shared);
        sleep(rand() % 3);

        pthread_mutex_lock(&mutex);
        readcount--;

        if (readcount == 0)
            sem_post(&wrt);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* writer(void* arg)
{
    int id = *((int*)arg);

    while (1)
    {
        sleep(rand() % 5);

        sem_wait(&wrt);
        shared = rand() % 10;

        printf("Writer %d writes %d\n", id, shared);

        sem_post(&wrt);
    }

    pthread_exit(NULL);
}

int main()
{
    int rd_count, wr_count;
    pthread_t* readers, *writers;

    printf("Enter reader count => ");
    scanf("%d", &rd_count);

    printf("Enter writer count => ");
    scanf("%d", &wr_count);

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    readers = (pthread_t*)malloc(rd_count * sizeof(pthread_t));
    writers = (pthread_t*)malloc(wr_count * sizeof(pthread_t));

    for (int i = 0; i < rd_count; i++)
        pthread_create(&readers[i], NULL, reader, (void*)&i);

    for (int i = 0; i < wr_count; i++)
        pthread_create(&writers[i], NULL, writer, (void*)&i);

    for (int i = 0; i < rd_count; i++)
        pthread_join(readers[i], NULL);

    for (int i = 0; i < wr_count; i++)
        pthread_join(writers[i], NULL);

    free(readers);
    free(writers);

    return 0;
}
