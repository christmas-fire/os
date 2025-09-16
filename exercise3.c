#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    
    printf("Root process PID: %d\n", getpid());
    
    pid1 = fork();
    
    if (pid1 == 0) {
        printf("Child 1 PID: %d, Parent PID: %d\n", getpid(), getppid());
        
        pid2 = fork();
        if (pid2 == 0) {
            printf("Grandchild 1 PID: %d, Parent PID: %d\n", getpid(), getppid());
            sleep(60);
        }
        else if (pid2 > 0) {
            pid3 = fork();
            if (pid3 == 0) {
                printf("Grandchild 2 PID: %d, Parent PID: %d\n", getpid(), getppid());
                sleep(60);
            }
            else if (pid3 > 0) {
                wait(NULL);
                wait(NULL);
                sleep(60);
            }
        }
        return 0;
    }
    else if (pid1 > 0) {
        pid2 = fork();
        if (pid2 == 0) {
            printf("Child 2 PID: %d, Parent PID: %d\n", getpid(), getppid());
            sleep(60);
        }
        else if (pid2 > 0) {
            wait(NULL);
            wait(NULL);
            sleep(60);
        }
    }
    
    return 0;
}