#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child_pid;
    
    printf("Parent process PID: %d\n", getpid());
    
    child_pid = fork();
    
    if (child_pid == 0) {
        printf("Child process PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child process is running...\n");
        
        while(1) {
            sleep(2);
            printf("Child %d is still alive, parent PID: %d\n", getpid(), getppid());
        }
    }
    else if (child_pid > 0) {
        printf("Parent process continuing...\n");
        sleep(30); 
        printf("Parent process ending\n");
    }
    else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}