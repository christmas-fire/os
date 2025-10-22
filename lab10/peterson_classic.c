#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sh = 0;
int operation_counter = 0;

// Переменные для алгоритма Петерсона
int turn; 
int flagReady[2];

void EnterCriticalRegion(int threadId) {
    flagReady[threadId] = 1; 
    turn = 1 - threadId; 
    while (turn == 1 - threadId && flagReady[1 - threadId]);
}

void LeaveCriticalRegion(int threadId) {
    flagReady[threadId] = 0; 
}

void* my_thread0(void* arg) {
    (void)arg;
    int i = 0;
    for (; i < 100; i++) {
        EnterCriticalRegion(0);
        sh++;
        LeaveCriticalRegion(0);
        operation_counter++;
        usleep(1);
    }
    return NULL;
}

void* my_thread1(void* arg) {
    (void)arg; 
    int i = 0;
    for (; i < 100; i++) {
        EnterCriticalRegion(1);
        sh += 2;
        LeaveCriticalRegion(1);
        operation_counter++;
        usleep(100);
    }
    return NULL;
}

int main() {
    pthread_t th_id[2];

    turn = 0;
    flagReady[0] = 0;
    flagReady[1] = 0;
    sh = 0;
    operation_counter = 0;

    printf("Алгоритм Петерсона (классический)\n");
    
    pthread_create(&th_id[0], NULL, my_thread0, NULL);
    pthread_create(&th_id[1], NULL, my_thread1, NULL);
    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);
    
    printf("Результат: %d\n", sh);
    printf("Общее количество операций: %d\n", operation_counter);

    return 0;
}
