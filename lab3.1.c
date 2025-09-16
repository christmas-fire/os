#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    double s = 0.0;
    
    child_pid = fork();
    
    if (child_pid == 0) {
        s += 3.14;
        fprintf(stdout, "CHILD: %i s=%g &s=%p\n", (int)getpid(), s, (void*)&s);
    } else if (child_pid > 0) {
        s += 2.72;
        fprintf(stdout, "PARENT: %i s=%g &s=%p\n", (int)getpid(), s, (void*)&s);
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}