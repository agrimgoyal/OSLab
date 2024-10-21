#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // For open()
#include <sys/stat.h>   // For mkfifo()
#include <unistd.h>     // For write(), close()
#include <string.h>     // For strlen()
#include <errno.h>      // For errno

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 128

int main() {
    int fd;
    char message[BUFFER_SIZE];

    // Create the FIFO (named pipe) if it does not exist
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo failed");
            exit(EXIT_FAILURE);
        }
    }

    // Open the FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    // Get the message to send
    printf("Enter a message to send: ");
    if (fgets(message, BUFFER_SIZE, stdin) == NULL) {
        perror("fgets failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Remove newline character from fgets
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }

    // Write the message to the FIFO
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("write failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", message);

    // Close the FIFO
    close(fd);

    return 0;
}
