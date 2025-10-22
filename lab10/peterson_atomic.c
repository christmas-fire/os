#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

// Обычные переменные
int sh = 0;

// Атомарные переменные
atomic_int atomic_sh = 0;
atomic_int atomic_counter = 0;
atomic_int turn; 
atomic_int flagReady[2]; 

void EnterCriticalRegion(int threadId) {
    atomic_store(&flagReady[threadId], 1);
    atomic_store(&turn, 1 - threadId); 
    
    while (atomic_load(&turn) == 1 - threadId && atomic_load(&flagReady[1 - threadId])) {
    }
}

void LeaveCriticalRegion(int threadId) {
    atomic_store(&flagReady[threadId], 0);
}

void* peterson_thread0(void* arg) {
    (void)arg;
    int i = 0;
    for (; i < 100; i++) {
        EnterCriticalRegion(0);
        
        sh++;
        atomic_fetch_add(&atomic_sh, 1);
        
        LeaveCriticalRegion(0);
        
        atomic_fetch_add(&atomic_counter, 1);
        usleep(1);
    }
    return NULL;
}

void* peterson_thread1(void* arg) {
    (void)arg;
    int i = 0;
    for (; i < 100; i++) {
        EnterCriticalRegion(1);
        
        sh += 2;
        atomic_fetch_add(&atomic_sh, 2);
        
        LeaveCriticalRegion(1);
        
        atomic_fetch_add(&atomic_counter, 1);
        usleep(100);
    }
    return NULL;
}

int main() {
    pthread_t th_id[2];
    
    printf("Алгоритм Петерсона с атомарными операциями\n");
    
    // Инициализация атомарных переменных
    atomic_store(&turn, 0);
    atomic_store(&flagReady[0], 0);
    atomic_store(&flagReady[1], 0);
    atomic_store(&atomic_sh, 0);
    atomic_store(&atomic_counter, 0);
    sh = 0;
    
    // Создаём потоки
    pthread_create(&th_id[0], NULL, peterson_thread0, NULL);
    pthread_create(&th_id[1], NULL, peterson_thread1, NULL);
    
    // Ждём завершения потоков
    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);
    
    printf("Результат (обычная переменная): %d\n", sh);
    printf("Результат (атомарная переменная): %d\n", atomic_load(&atomic_sh));
    printf("Общее количество операций: %d\n", atomic_load(&atomic_counter));
    
    return 0;
}
