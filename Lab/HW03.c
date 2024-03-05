/* 
Name: Milon Biswas
Blazer id:mbiswas
Projects: Homework 03
To compile:
make
./HW03 -f png 2 -E "tar -cvf png.tar" ../projects2/pic
$ tar -xvf png.tar
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024

// Global variables for command-line options
int show_details = 0;
int size_limit = -1;
char *substring = NULL;
int depth_limit = -1;
char type_filter = 'a';

char *exec_each = NULL;      // UNIX command to be executed for each file
char *exec_all = NULL;       // UNIX command to be executed with all files as arguments
char files_accumulated[MAX_CMD_LENGTH * 10] = "";  // String to accumulate filenames for `-E` option

// Function to execute the UNIX command with provided arguments
void execute_unix_command(const char *command, const char *arg) {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        execl("/bin/sh", "sh", "-c", command, arg, NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // Parent process
        wait(NULL);  // Wait for the child to complete
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void list_files(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat st, link_stat;
    char fullpath[1024];

    // Try to open the directory
    if ((dir = opendir(path)) == NULL) {
        perror("Error opening directory");
        return;
    }

    // Iterate over each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        lstat(fullpath, &link_stat);

        // Handle symbolic links
        if (S_ISLNK(link_stat.st_mode)) {
            char target[1024];
            int len = readlink(fullpath, target, sizeof(target) - 1);
            if (len != -1) {
                target[len] = '\0';
            }
            if (type_filter == 'a' || type_filter == 'l') {
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
                if (depth_limit == -1 || depth < depth_limit) {
                    list_files(fullpath, depth + 4);
                }
            }
        } else {
            int print = 1;
            if (size_limit != -1 && st.st_size > size_limit) print = 0;
            if (substring && !strstr(entry->d_name, substring)) print = 0;
            if (type_filter == 'd') print = 0;

            // Execute UNIX command for each file (-e option)
            if (print && exec_each) {
                char full_cmd[MAX_CMD_LENGTH * 2];
                snprintf(full_cmd, sizeof(full_cmd), exec_each, fullpath);
                execute_unix_command(full_cmd, NULL);
            }

            // Accumulate filenames for `-E` option
            if (print && exec_all) {
                strcat(files_accumulated, "\"");
                strcat(files_accumulated, fullpath);
                strcat(files_accumulated, "\" ");
            }

            // Print file details
            // if (print && !exec_each && !exec_all) {
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

int main(int argc, char **argv) 
{
    char *path = ".";  // Default directory is the current directory

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
        } else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            exec_each = argv[++i];
        } else if (strcmp(argv[i], "-E") == 0 && i + 1 < argc) {
            exec_all = argv[++i];
        } else {
            path = argv[i];
        }
    }

    list_files(path, 0);


    if (exec_all && strlen(files_accumulated) > 0) 
    {
        char full_cmd[MAX_CMD_LENGTH * 12];
        snprintf(full_cmd, sizeof(full_cmd), "%s %s", exec_all, files_accumulated);
        execute_unix_command(full_cmd, NULL);
    }

    return 0;
}
