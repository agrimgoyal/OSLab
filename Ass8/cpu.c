#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int start_time; // Time when process starts execution
    int end_time;   // Time when process finishes execution
    int wait_time;  // Waiting time
    int turnaround; // Turnaround time
} Process;
void fcfs(Process p[], int n) {
    int current_time = 0;
    printf("FCFS Scheduling:\n");

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival)
            current_time = p[i].arrival;
        
        p[i].start_time = current_time;
        p[i].wait_time = p[i].start_time - p[i].arrival;
        p[i].end_time = p[i].start_time + p[i].burst;
        p[i].turnaround = p[i].end_time - p[i].arrival;
        current_time = p[i].end_time;

        printf("Process %d: Waiting Time: %d, Turnaround Time: %d\n", 
               p[i].pid, p[i].wait_time, p[i].turnaround);
    }
}
int compare_burst(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->burst - p2->burst;
}

void sjf(Process p[], int n) {
    qsort(p, n, sizeof(Process), compare_burst);
    int current_time = 0;
    printf("\nSJF Scheduling:\n");

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival)
            current_time = p[i].arrival;
        
        p[i].start_time = current_time;
        p[i].wait_time = p[i].start_time - p[i].arrival;
        p[i].end_time = p[i].start_time + p[i].burst;
        p[i].turnaround = p[i].end_time - p[i].arrival;
        current_time = p[i].end_time;

        printf("Process %d: Waiting Time: %d, Turnaround Time: %d\n", 
               p[i].pid, p[i].wait_time, p[i].turnaround);
    }
}
void round_robin(Process p[], int n, int quantum) {
    int t = 0, x = n;
    int *burst_remaining = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        burst_remaining[i] = p[i].burst;

    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);

    while (x != 0) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= t && burst_remaining[i] > 0) {
                if (burst_remaining[i] > quantum) {
                    t += quantum;
                    burst_remaining[i] -= quantum;
                } else {
                    t += burst_remaining[i];
                    p[i].wait_time = t - p[i].burst - p[i].arrival;
                    p[i].turnaround = t - p[i].arrival;
                    burst_remaining[i] = 0;
                    x--;

                    printf("Process %d: Waiting Time: %d, Turnaround Time: %d\n", 
                           p[i].pid, p[i].wait_time, p[i].turnaround);
                }
            }
        }
    }
    free(burst_remaining);
}
int main() {
    Process processes[] = {{1, 0, 4}, {2, 1, 3}, {3, 2, 1}};
    int n = sizeof(processes) / sizeof(processes[0]);

    fcfs(processes, n);
    sjf(processes, n);
    int quantum = 2;
    round_robin(processes, n, quantum);

    return 0;
}