#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h> 

#define MAX_CMD_LENGTH 1024

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file for reading
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error opening input file");
        return 1;
    }

    char cmd[MAX_CMD_LENGTH];
    char logFileName[] = "output.log";
    FILE *logFile = fopen(logFileName, "a"); // Open log file for appending

    if (logFile == NULL) {
        printf("Error opening log file");
        fclose(inputFile);
        return 1;
    }

    while (fgets(cmd, MAX_CMD_LENGTH, inputFile) != NULL) {
        // Remove newline character from the command
        cmd[strcspn(cmd, "\n")] = '\0';

        time_t startTime, endTime;
        time(&startTime);

        pid_t pid = fork();

        if (pid == 0) { // Child process
        // Execute the command using /bin/sh
            execl("/bin/sh", "sh", "-c", cmd, NULL);
            printf("execl");
            exit(EXIT_FAILURE);
        } else if (pid > 0) { // Parent process
            int status;
            wait(&status);

            time(&endTime);

            if (WIFEXITED(status)) { // Child process terminated normally
                // Log the command, start time, and end time
                fprintf(logFile, "%s\t%s\t%s\n", cmd, ctime(&startTime), ctime(&endTime));
            } else {
                // Log if the command failed
                fprintf(logFile, "Command failed: %s\n", cmd);
            }
        } else {
            printf("fork");
            exit(EXIT_FAILURE);
        }
    }

    fclose(inputFile);
    fclose(logFile);

    return 0;
}
