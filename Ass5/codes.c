#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    // First fork to create the first child process
    pid1 = fork();

    if (pid1 < 0) {
        // Fork failed
        perror("First fork failed");
        return 1;
    }
    else if (pid1 == 0) {
        // First child process
        printf("First child process (PID=%d): executing 'ls -l'\n", getpid());
        // Replace the child process image with the 'ls -l' command
        execlp("ls", "ls", "-l", NULL);
        // If execlp returns, it must have failed
        perror("execlp failed in first child");
        return 1;
    }
    else {
        // Parent process
        // Second fork to create the second child process
        pid2 = fork();

        if (pid2 < 0) {
            // Fork failed
            perror("Second fork failed");
            return 1;
        }
        else if (pid2 == 0) {
            // Second child process
            printf("Second child process (PID=%d): executing 'date'\n", getpid());
            // Replace the child process image with the 'date' command
            execlp("date", "date", NULL);
            // If execlp returns, it must have failed
            perror("execlp failed in second child");
            return 1;
        }
        else {
            // Parent process
            int status1, status2;

            // Wait for the first child process to complete
            waitpid(pid1, &status1, 0);
            printf("First child process (PID=%d) completed with status %d\n", pid1, WEXITSTATUS(status1));

            // Wait for the second child process to complete
            waitpid(pid2, &status2, 0);
            printf("Second child process (PID=%d) completed with status %d\n", pid2, WEXITSTATUS(status2));

            printf("Parent process (PID=%d): Both child processes have completed.\n", getpid());
        }
    }

    return 0;
}
