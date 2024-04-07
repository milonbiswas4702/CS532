#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 256

int main() {
    char command[MAX_COMMAND_LENGTH];

    printf("$ ./lab11\n");

    while (1) {
        // Prompt the user for a command
        printf("Enter command: ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            printf("Error reading command.\n");
            continue;
        }

        // Remove newline character if present
        command[strcspn(command, "\n")] = 0;

        // Check for the quit command
        if (strcmp(command, "quit") == 0) {
            printf("Exiting program...bye!\n");
            break;
        }

        // Execute the command using popen
        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            printf("Failed to run command\n");
            exit(1);
        }

        // Display the output from the command
        char result[MAX_COMMAND_LENGTH];
        while (fgets(result, MAX_COMMAND_LENGTH, fp) != NULL) {
            printf("%s", result);
        }

        // Close the command pipe
        pclose(fp);
    }

    return 0;
}
