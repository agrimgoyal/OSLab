#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void fifoPageReplacement(int referenceString[], int n, int frameSize);
void lruPageReplacement(int referenceString[], int n, int frameSize);
void optimalPageReplacement(int referenceString[], int n, int frameSize);

int main() {
    int n, frameSize, choice;
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);

    int referenceString[n];
    printf("Enter the reference string (space-separated page numbers):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &referenceString[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameSize);

    // Menu-driven program
    do {
        printf("\nPage Replacement Algorithms:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifoPageReplacement(referenceString, n, frameSize);
                break;
            case 2:
                lruPageReplacement(referenceString, n, frameSize);
                break;
            case 3:
                optimalPageReplacement(referenceString, n, frameSize);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void fifoPageReplacement(int referenceString[], int n, int frameSize) {
    int frames[frameSize];
    int front = 0, pageFaults = 0;
    for (int i = 0; i < frameSize; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == referenceString[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[front] = referenceString[i];
            front = (front + 1) % frameSize;
            pageFaults++;
        }

        printf("Page %d -> Frames: ", referenceString[i]);
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

void lruPageReplacement(int referenceString[], int n, int frameSize) {
    int frames[frameSize];
    int counter[frameSize];
    int pageFaults = 0;
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("\nLRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == referenceString[i]) {
                found = 1;
                counter[j] = i;
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < frameSize; j++) {
                if (counter[j] < counter[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = referenceString[i];
            counter[lruIndex] = i;
            pageFaults++;
        }

        printf("Page %d -> Frames: ", referenceString[i]);
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

void optimalPageReplacement(int referenceString[], int n, int frameSize) {
    int frames[frameSize];
    int pageFaults = 0;
    for (int i = 0; i < frameSize; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == referenceString[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int farthestIndex = -1, farthestDistance = -1;
            for (int j = 0; j < frameSize; j++) {
                int distance = n + 1; // Set distance to a large value initially
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == referenceString[k]) {
                        distance = k - i;
                        break;
                    }
                }

                if (distance > farthestDistance) {
                    farthestDistance = distance;
                    farthestIndex = j;
                }
            }

            frames[farthestIndex] = referenceString[i];
            pageFaults++;
        }

        printf("Page %d -> Frames: ", referenceString[i]);
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}
