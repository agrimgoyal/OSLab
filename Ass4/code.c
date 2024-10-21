#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>  // Added this line

void list_directory_recursive(const char *base_path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(base_path);
    if (dir == NULL) {
        fprintf(stderr, "Failed to open directory '%s': %s\n", base_path, strerror(errno));
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char path[PATH_MAX];
        struct stat statbuf;

        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path
        if (snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name) >= sizeof(path)) {
            fprintf(stderr, "Path length exceeds buffer size.\n");
            continue;
        }

        // Retrieve file status
        if (lstat(path, &statbuf) == -1) {
            fprintf(stderr, "Failed to stat '%s': %s\n", path, strerror(errno));
            continue;
        }

        // Print the path
        if (S_ISDIR(statbuf.st_mode)) {
            printf("%s/\n", path);
            // Recursively list subdirectories
            list_directory_recursive(path);
        } else {
            printf("%s\n", path);
        }
    }

    closedir(dir);
}

int main() {
    char current_path[PATH_MAX];

    // Get the current working directory
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        fprintf(stderr, "Failed to get current directory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Start recursive listing from the current directory
    list_directory_recursive(current_path);

    return 0;
}
