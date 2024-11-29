#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTITIONS 10
#define MAX_PROCESSES 10

// Structures to hold partition and process data
typedef struct {
    int id;
    int size;
    int isAllocated;
    int processId;
} Partition;

typedef struct {
    int id;
    int size;
    int isAllocated;
} Process;

// Function prototypes
void displayPartitions(Partition partitions[], int partitionCount);
void firstFit(Partition partitions[], int partitionCount, Process processes[], int processCount);
void bestFit(Partition partitions[], int partitionCount, Process processes[], int processCount);
void worstFit(Partition partitions[], int partitionCount, Process processes[], int processCount);

int main() {
    Partition partitions[MAX_PARTITIONS];
    Process processes[MAX_PROCESSES];
    int partitionCount, processCount, choice;

    // Input number of partitions
    printf("Enter number of partitions: ");
    scanf("%d", &partitionCount);

    // Input partition sizes
    for (int i = 0; i < partitionCount; i++) {
        printf("Enter size of partition %d: ", i + 1);
        partitions[i].id = i + 1;
        scanf("%d", &partitions[i].size);
        partitions[i].isAllocated = 0; // Mark as free initially
        partitions[i].processId = -1; // No process assigned
    }

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &processCount);

    // Input process sizes
    for (int i = 0; i < processCount; i++) {
        printf("Enter size of process %d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d", &processes[i].size);
        processes[i].isAllocated = 0; // Mark as unallocated initially
    }

    // Menu for allocation methods
    do {
        printf("\nMemory Allocation Methods:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Display Partitions\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                firstFit(partitions, partitionCount, processes, processCount);
                break;
            case 2:
                bestFit(partitions, partitionCount, processes, processCount);
                break;
            case 3:
                worstFit(partitions, partitionCount, processes, processCount);
                break;
            case 4:
                displayPartitions(partitions, partitionCount);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void displayPartitions(Partition partitions[], int partitionCount) {
    printf("\nPartition Status:\n");
    printf("Partition\tSize\tStatus\t\tProcess ID\n");
    for (int i = 0; i < partitionCount; i++) {
        printf("%d\t\t%d\t%s\t%d\n",
               partitions[i].id,
               partitions[i].size,
               partitions[i].isAllocated ? "Allocated" : "Free",
               partitions[i].isAllocated ? partitions[i].processId : -1);
    }
}

void firstFit(Partition partitions[], int partitionCount, Process processes[], int processCount) {
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < partitionCount; j++) {
            if (!partitions[j].isAllocated && partitions[j].size >= processes[i].size) {
                partitions[j].isAllocated = 1;
                partitions[j].processId = processes[i].id;
                processes[i].isAllocated = 1;
                printf("Process %d allocated to Partition %d\n", processes[i].id, partitions[j].id);
                break;
            }
        }
        if (!processes[i].isAllocated) {
            printf("Process %d could not be allocated\n", processes[i].id);
        }
    }
}

void bestFit(Partition partitions[], int partitionCount, Process processes[], int processCount) {
    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < processCount; i++) {
        int bestIndex = -1;
        for (int j = 0; j < partitionCount; j++) {
            if (!partitions[j].isAllocated && partitions[j].size >= processes[i].size) {
                if (bestIndex == -1 || partitions[j].size < partitions[bestIndex].size) {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1) {
            partitions[bestIndex].isAllocated = 1;
            partitions[bestIndex].processId = processes[i].id;
            processes[i].isAllocated = 1;
            printf("Process %d allocated to Partition %d\n", processes[i].id, partitions[bestIndex].id);
        } else {
            printf("Process %d could not be allocated\n", processes[i].id);
        }
    }
}

void worstFit(Partition partitions[], int partitionCount, Process processes[], int processCount) {
    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < processCount; i++) {
        int worstIndex = -1;
        for (int j = 0; j < partitionCount; j++) {
            if (!partitions[j].isAllocated && partitions[j].size >= processes[i].size) {
                if (worstIndex == -1 || partitions[j].size > partitions[worstIndex].size) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            partitions[worstIndex].isAllocated = 1;
            partitions[worstIndex].processId = processes[i].id;
            processes[i].isAllocated = 1;
            printf("Process %d allocated to Partition %d\n", processes[i].id, partitions[worstIndex].id);
        } else {
            printf("Process %d could not be allocated\n", processes[i].id);
        }
    }
}
