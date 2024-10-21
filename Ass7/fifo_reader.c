#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      //tou For open()
#include <sys/stat.h>   // For mkfifo()
#include <unistd.h>     // For read(), close()
#include <string.h>     // For strlen()
#include <errno.h>      // For errno

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 128

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    // Open the FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    // Read the message from the FIFO
    ssize_t num_bytes = read(fd, buffer, BUFFER_SIZE);
    if (num_bytes == -1) {
        perror("read failed");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (num_bytes == 0) {
        printf("No data to read.\n");
    } else {
        printf("Received message: %s\n", buffer);
    }

    // Close the FIFO
    close(fd);

    // Remove the FIFO file
    if (unlink(FIFO_NAME) == -1) {
        perror("unlink failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
