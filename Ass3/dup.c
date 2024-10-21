#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_NAME "redirected_output.txt"

int main() {
    int fd;
    char *message = "This message is redirected to the file using dup2().\n";

    // Open or create the file with write permissions
    fd = open(FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Redirect stdout to the file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Error redirecting stdout");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // At this point, printf will write to the file
    printf("%s", message);

    // Close the file descriptor
    close(fd);

    // Verify the contents of the file
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file for verification");
        exit(EXIT_FAILURE);
    }

    printf("Verifying the content of '%s':\n", FILE_NAME);
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
