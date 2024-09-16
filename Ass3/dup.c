#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILE_NAME "original.txt"

int main() {
    int fd_original, fd_dup;
    ssize_t bytes_written;
    char *message1 = "Message from original file descriptor.\n";
    char *message2 = "Message from duplicated file descriptor.\n";

    // Open or create the file with write permissions
    fd_original = open(FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_original < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Duplicate the file descriptor
    fd_dup = dup(fd_original);
    if (fd_dup < 0) {
        perror("Error duplicating file descriptor");
        close(fd_original);
        exit(EXIT_FAILURE);
    }

    // Write to the original file descriptor
    bytes_written = write(fd_original, message1, strlen(message1));
    if (bytes_written < 0) {
        perror("Error writing to original file descriptor");
        close(fd_original);
        close(fd_dup);
        exit(EXIT_FAILURE);
    }

    // Write to the duplicated file descriptor
    bytes_written = write(fd_dup, message2, strlen(message2));
    if (bytes_written < 0) {
        perror("Error writing to duplicated file descriptor");
        close(fd_original);
        close(fd_dup);
        exit(EXIT_FAILURE);
    }

    // Close the file descriptors
    close(fd_original);
    close(fd_dup);

    // Verify the contents of the file
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file for verification");
        exit(EXIT_FAILURE);
    }

    printf("Contents of '%s':\n", FILE_NAME);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
