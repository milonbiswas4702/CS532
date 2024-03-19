#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>  // Needed for signal handling

// Function declarations for signal handling
void sigint_handler(int signum);
void sigtstp_handler(int signum);
void sigquit_handler(int signum);

// Global variable to store the child's PID so signal handlers can access it
pid_t child_pid = -1;

int main(int argc, char **argv) {
    int status;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    // Set up signal handlers
    signal(SIGINT, sigint_handler);   // Handle Control-C
    signal(SIGTSTP, sigtstp_handler); // Handle Control-Z
    signal(SIGQUIT, sigquit_handler); // Handle Control-\ (quit)

    child_pid = fork();
    if (child_pid == 0) {
        // Child process: execute the command specified in argv[1]
        execvp(argv[1], &argv[1]);
        // If execvp returns, it must have failed
        printf("If you see this statement then execvp failed ;-(\n");
        perror("execvp");
        exit(-1);
    } else if (child_pid > 0) {
        // Parent process: wait for the child to terminate
        printf("Wait for the child process to terminate\n");
        wait(&status); // wait for the child process to terminate

        if (WIFEXITED(status)) {
            // The child process terminated normally
            printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } else {
            // The child process did not terminate normally
            printf("Child process did not terminate normally!\n");
        }
    } else {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    printf("[%ld]: Exiting program .....\n", (long)getpid());

    return 0;
}

// Signal handler for SIGINT (Control-C)
void sigint_handler(int signum) {
    // If we have a valid child PID, send the SIGINT signal to the child
    if (child_pid > 0) {
        kill(child_pid, SIGINT);
    }
}

// Signal handler for SIGTSTP (Control-Z)
void sigtstp_handler(int signum) {
    // If we have a valid child PID, send the SIGTSTP signal to the child to suspend it
    if (child_pid > 0) {
        kill(child_pid, SIGTSTP);
    }
}

// Signal handler for SIGQUIT (Control-\)
void sigquit_handler(int signum) {
    // If we have a valid child PID, send the SIGQUIT signal to the child to make it terminate
    if (child_pid > 0) {
        kill(child_pid, SIGQUIT);
    }
    // Parent process should continue its normal execution path (i.e., it will proceed to wait for the child to terminate)
}
