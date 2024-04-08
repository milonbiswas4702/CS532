#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_JOBS 100

typedef struct {
    int jobid;
    char command[256];
    pid_t pid;
    int status; // 0 for waiting, 1 for running, 2 for completed
    time_t startTime;
    time_t endTime;
} Job;

Job jobs[MAX_JOBS];
int jobCount = 0;
int runningJobs = 0;
int maxRunningJobs;

bool startJobIfPossible(int jobIndex) {
    if (runningJobs < maxRunningJobs) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            return false;
        } 
        else if (pid == 0) {
            // In child process
            execlp("/bin/sh", "sh", "-c", jobs[jobIndex].command, (char *) NULL);
            perror("execlp failed");
            exit(EXIT_FAILURE);
        } 
        else {
            // In parent process
            jobs[jobIndex].pid = pid;
            jobs[jobIndex].status = 1; // Job is running
            jobs[jobIndex].startTime = time(NULL); // Record start time
            runningJobs++;
            return true;
        }
    }
    return false;
}

void submitJob(char *command) {
    if (jobCount >= MAX_JOBS) {
        printf("Job limit reached.\n");
        return;
    }

    int jobid = jobCount + 1;
    Job newJob;
    newJob.jobid = jobid;
    strcpy(newJob.command, command);
    newJob.status = 0; // Job is initially waiting
    newJob.startTime = 0;
    newJob.endTime = 0;
    jobs[jobCount++] = newJob;

    if (!startJobIfPossible(jobCount - 1)) {
        printf("job %d added to the queue\n", jobid);
    } else {
        printf("job %d added and started\n", jobid);
    }
}

void showJobs() {
    printf("jobid command status\n");
    for (int i = 0; i < jobCount; i++) {
        if (jobs[i].status != 2) { // Exclude completed jobs
            printf("%d %s %s\n", jobs[i].jobid, jobs[i].command,
                   jobs[i].status == 0 ? "Waiting" : "Running");
        }
    }
}

void updateJobStatuses() {
    for (int i = 0; i < jobCount; i++) {
        if (jobs[i].status == 1) {
            int status;
            pid_t result = waitpid(jobs[i].pid, &status, WNOHANG);
            if (result == 0) {
                // Child still running
            } else if (result == -1) {
                perror("waitpid failed");
            } else {
                // Child ended
                jobs[i].status = 2;
                jobs[i].endTime = time(NULL); // Set end time
                runningJobs--;
                for (int j = 0; j < jobCount; j++) {
                    if (jobs[j].status == 0) {
                        if (startJobIfPossible(j)) {
                            printf("job %d started\n", jobs[j].jobid);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void submitHistory() {
    printf("jobid command starttime endtime status\n");
    for (int i = 0; i < jobCount; i++) {
        char start_buf[256] = "N/A";
        char end_buf[256] = "N/A";
        
        if (jobs[i].startTime != 0) {
            strftime(start_buf, sizeof(start_buf), "%Y-%m-%d %H:%M:%S", localtime(&jobs[i].startTime));
        }
        if (jobs[i].endTime != 0) {
            strftime(end_buf, sizeof(end_buf), "%Y-%m-%d %H:%M:%S", localtime(&jobs[i].endTime));
        }

        printf("%d %s %s %s %s\n", jobs[i].jobid, jobs[i].command, start_buf, end_buf,
               jobs[i].status == 2 ? "Completed" : (jobs[i].status == 1 ? "Running" : "Waiting"));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <max_running_jobs>\n", argv[0]);
        return 1;
    }

    maxRunningJobs = atoi(argv[1]);

    char command[256];
    while (1) {
        printf("Enter command> ");
        fgets(command, 256, stdin);
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "submit ", 7) == 0) {
            submitJob(command + 7);
        } else if (strcmp(command, "showjobs") == 0) {
            showJobs();
        } else if (strcmp(command, "submithistory") == 0) {
            submitHistory();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Unknown command.\n");
        }

        updateJobStatuses();
    }

    return 0;
}
