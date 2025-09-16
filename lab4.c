#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    int status;

    printf("=== Начало выполнения родительского процесса ===\n");
    printf("PID родителя: %d\n", getpid());

    // Первый дочерний процесс
    pid1 = fork();

    if (pid1 == 0) {
        // Дочерний процесс 1
        printf("Дочерний процесс 1 (PID: %d, PPID: %d)\n", getpid(), getppid());
        execl("/bin/ls", "ls", "-l", NULL); // Заменяет текущий процесс на ls
        perror("execl failed"); // Если exec не сработал
        exit(1);
    }
    else if (pid1 > 0) {
        // Родитель продолжает работу
        printf("Родитель создал процесс 1 (PID: %d)\n", pid1);

        // Второй дочерний процесс (внук)
        pid2 = fork();

        if (pid2 == 0) {
            // Дочерний процесс 2 (внук)
            printf("Дочерний процесс 2 (PID: %d, PPID: %d)\n", getpid(), getppid());
            execl("/bin/date", "date", NULL);
            perror("execl failed");
            exit(1);
        }
        else if (pid2 > 0) {
            printf("Родитель создал процесс 2 (PID: %d)\n", pid2);

            // Третий дочерний процесс (братья с процессом 2)
            pid3 = fork();

            if (pid3 == 0) {
                // Дочерний процесс 3
                printf("Дочерний процесс 3 (PID: %d, PPID: %d)\n", getpid(), getppid());
                execl("/bin/whoami", "whoami", NULL);
                perror("execl failed");
                exit(1);
            }
            else if (pid3 > 0) {
                printf("Родитель создал процесс 3 (PID: %d)\n", pid3);
            }
            else {
                fprintf(stderr, "Ошибка fork для процесса 3\n");
                exit(1);
            }
        }
        else {
            fprintf(stderr, "Ошибка fork для процесса 2\n");
            exit(1);
        }
    }
    else {
        fprintf(stderr, "Ошибка fork для процесса 1\n");
        exit(1);
    }

    // Ожидание завершения всех дочерних процессов
    wait(&status);
    wait(&status);
    wait(&status);

    printf("=== Все процессы завершены. Родительcкий завершается. ===\n");

    return 0;
}