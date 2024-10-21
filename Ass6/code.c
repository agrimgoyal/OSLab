#include <stdio.h>     
#include <unistd.h>    
#include <stdlib.h>    
#include <sys/types.h> 
#include <sys/wait.h>  

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {

        printf("Child process (PID=%d): Started.\n", getpid());

        sleep(2);

        printf("Child process (PID=%d): Exiting with status 42.\n", getpid());
    } else {

        printf("Parent process (PID=%d): Waiting for child process (PID=%d) to finish.\n", getpid(), pid);

        pid_t waited_pid = wait(&status);

        if (waited_pid == -1) {
            perror("wait failed");
            exit(1);
        }

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Parent process (PID=%d): Child process (PID=%d) exited with status %d.\n", getpid(), waited_pid, exit_status);
        } else {
            printf("Parent process (PID=%d): Child process (PID=%d) did not terminate normally.\n", getpid(), waited_pid);
        }

        printf("Parent process (PID=%d): Exiting.\n", getpid());
    }

    return 0;
}
