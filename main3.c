#include <stdlib.h>  // For srand() and rand()
#include <time.h>    // For time()
#include <unistd.h>  // For getpid(), sleep()
#include <sys/wait.h> // For wait()
#include <sys/types.h> // For pid_t
#include <stdio.h>   // For printf()

#define MAX_ITER 30
#define MAX_SLEEP 10

void child_process() {
    // Seed random number generator with the child's PID
    srand(time(NULL) ^ (getpid() << 16));  
    int iterations = rand() % MAX_ITER + 1;  // Random number of iterations

    for (int i = 0; i < iterations; ++i) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        int sleep_time = rand() % MAX_SLEEP + 1;  // Random sleep time
        sleep(sleep_time);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }

    exit(0);  // Child process exits
}

int main() {
    pid_t pid1, pid2;

    // Create first child process
    pid1 = fork();
    if (pid1 == 0) {
        child_process();  // First child process
    }

    // Create second child process
    pid2 = fork();
    if (pid2 == 0) {
        child_process();  // Second child process
    }

    // Parent waits for both children to finish
    int status;
    pid_t finished_pid;

    finished_pid = wait(&status);
    printf("Child Pid: %d has completed\n", finished_pid);

    finished_pid = wait(&status);
    printf("Child Pid: %d has completed\n", finished_pid);

    return 0;
}
