#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>



// Recursive function to list files and directories from a given path.
void listDir(const char *path, int *count) {
    struct dirent *dirent;
    DIR *dir;
    char fullPath[1024];

    // Opening the directory specified by the path.
    dir = opendir(path);
    if (dir == NULL) {
        printf("Error opening directory '%s'\n", path);
        return;
    }

    // Iterating over each entry in the directory.
    while ((dirent = readdir(dir)) != NULL) {
        struct stat statbuf;

        // Constructing the full path of the current entry.
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, dirent->d_name);

        // Fetching the status of the entry to see whether it's a file or directory.
        if (stat(fullPath, &statbuf) == -1) {
            perror("Failed to get file status");
            continue;
        }

        // Checking if the entry is a directory.
        if (S_ISDIR(statbuf.st_mode)) {
            // Skip the special entries "." and "..".
            if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
                continue;
            }

            // Printing the directory and recurse into it.
            printf("[%d] Directory: %s\n", (*count)++, fullPath);
            listDir(fullPath, count);
        } else {
            // Printing the file.
            printf("[%d] File: %s\n", (*count)++, fullPath);
        }
    }

    // Closing the directory after processing all entries.
    closedir(dir);
}

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage : %s <dirname>\n", argv[0]);
        exit(-1);
    }

    int count = 1;
    listDir(argv[1], &count);

    return 0;
}
