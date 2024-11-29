#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semaphore declaration
sem_t semaphore;

void *workerThread(void *arg) {
    printf("Worker: Starting task...\n");
    sleep(2);  // Simulate work with sleep
    printf("Worker: Task completed.\n");

    // Signal that the task is done
    sem_post(&semaphore);

    return NULL;
}

void *managerThread(void *arg) {
    printf("Manager: Waiting for Worker to complete task...\n");

    // Wait for the Worker to complete
    sem_wait(&semaphore);

    // Proceed after Worker has completed
    printf("Manager: Worker completed task. Proceeding...\n");

    return NULL;
}

int main() {
    pthread_t worker, manager;

    // Initialize the semaphore with a count of 0, so manager waits initially
    sem_init(&semaphore, 0, 0);

    // Create the threads
    pthread_create(&worker, NULL, workerThread, NULL);
    pthread_create(&manager, NULL, managerThread, NULL);

    // Wait for both threads to complete
    pthread_join(worker, NULL);
    pthread_join(manager, NULL);

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}
