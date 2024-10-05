#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Function for the child processes
void child_process() {
    int iterations = random() % 30 + 1; // Random number of iterations (1 to 30)

    for (int i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());

        int sleep_time = random() % 10 + 1; // Sleep for random time (1 to 10 seconds)
        sleep(sleep_time);

        printf("Child Pid: %d is awake! Where is my Parent: %d?\n", getpid(), getppid());
    }

    exit(0); // Terminate the child process
}

int main() {
    srandom(time(NULL)); // Seed the random number generator with current time

    // Create the first child process
    pid_t pid1 = fork();

    if (pid1 == 0) {
        // First child process
        child_process();
    } else {
        // Parent process creates second child process
        pid_t pid2 = fork();

        if (pid2 == 0) {
            // Second child process
            child_process();
        } else {
            // Parent process waits for both children to complete
            int status;
            pid_t completed_pid;

            completed_pid = wait(&status);
            printf("Child Pid: %d has completed\n", completed_pid);

            completed_pid = wait(&status);
            printf("Child Pid: %d has completed\n", completed_pid);
        }
    }

    return 0;
}
