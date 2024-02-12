/*
Name: Milon Biswas
BlazerId: mbiswas
Project #: 02
To compile: <make>
To run: <./mbiswas_hw02> 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

// Global variables to store command-line options
int show_details = 0;       // Flag to determine whether to show file details (-S option)
int size_limit = -1;        // Limit on the size of files to be displayed (-s option)
char *substring = NULL;     // Substring to search in filenames (-f option)
int depth_limit = -1;       // Depth limit for directory traversal (-f option)
char type_filter = 'a';     // Filter for type of file/directory to display (-t option)

/**
 * Function to recursively list files and directories starting from a given path.
 * Depth is used for indentation and to limit the traversal based on depth_limit.
 */
void list_files(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat st, link_stat;
    char fullpath[1024];

    // Try to open the directory
    if ((dir = opendir(path)) == NULL) {
        printf("Error opening directory");
        return;
    }

    // Iterate over each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        // Handle symbolic links
        lstat(fullpath, &link_stat);
        if (S_ISLNK(link_stat.st_mode)) {
            char target[1024];
            int len = readlink(fullpath, target, sizeof(target) - 1);
            if (len != -1) {
                target[len] = '\0';
            }
            if (type_filter == 'a' || type_filter == 'f') {
                printf("%*s%s -> %s\n", depth, "", entry->d_name, target);
            }
            continue;
        }

        // Get the statistics of the current entry
        stat(fullpath, &st);

        // Handle directories
        if (S_ISDIR(st.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                if (type_filter == 'a' || type_filter == 'd') {
                    printf("%*s%s/\n", depth, "", entry->d_name);
                }
                // Recursive call to handle subdirectories
                if (depth_limit == -1 || depth < depth_limit) {
                    list_files(fullpath, depth + 4);
                }
            }
        } else { // Handle files
            int print = 1;

            if (size_limit != -1 && st.st_size > size_limit) print = 0;
            if (substring && !strstr(entry->d_name, substring)) print = 0;
            if (type_filter == 'd') print = 0;

            // Print file details if required
            if (print) {
                if (show_details) {
                    printf("%*s%s (Size: %ld, Permissions: %o, Last Access: %ld)\n", depth, "", entry->d_name, st.st_size, st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO), st.st_atime);
                } else {
                    printf("%*s%s\n", depth, "", entry->d_name);
                }
            }
        }
    }
    closedir(dir);
}

int main(int argc, char **argv) {
    char *path = ".";  // Default directory is current directory

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-S") == 0) {
            show_details = 1;
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            size_limit = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0 && i + 2 < argc) {
            substring = argv[++i];
            depth_limit = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            type_filter = argv[++i][0];
        } else {
            path = argv[i];
        }
    }
    printf("test me again");
    // Start the directory traversal
    list_files(path, 0);  
    return 0;
}
