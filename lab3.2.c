#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t child_pid;
    double s = 0.0;
    FILE* fp;
    
    fp = fopen("test.dat", "a+");
    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }
    
    child_pid = fork();
    
    if (child_pid == 0) {
        s += 3.14;
        fprintf(fp, "CHILD: %i s=%.2f &s=%p fp=%p\n", 
                (int)getpid(), s, (void*)&s, (void*)fp);
    }
    else if (child_pid > 0) {
        s += 2.72;
        fprintf(fp, "PARENT: %i s=%.2f &s=%p fp=%p\n", 
                (int)getpid(), s, (void*)&s, (void*)fp);
    }
    else {
        perror("fork failed");
        fclose(fp);
        return 1;
    }
    
    fclose(fp);
    return 0;
}