#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Общая переменная, к которой обращаются потоки
int sh = 0;

// Для первого примера (без синхронизации)
void* my_thread0_no_sync(void* arg) {
    int i = 0;
    for (; i < 100; i++) {
        int temp = sh; // Читаем
        usleep(1); // Добавим задержку, чтобы увеличить шанс переключения контекста
        temp++;     // Модифицируем
        sh = temp;  // Записываем
    }
    return NULL;
}

void* my_thread1_no_sync(void* arg) {
    int i = 0;
    for (; i < 100; i++) {
        int temp = sh; // Читаем
        usleep(100); // Добавим бОльшую задержку
        temp += 2;   // Модифицируем
        sh = temp;   // Записываем
    }
    return NULL;
}

// Для второго примера (спин-блокировка с turn)
int turn = 0; // Переменная для управления очередью

void* my_thread0_turn(void* arg) {
    int i = 0;
    for (; i < 100; i++) {
        while (turn != 0); // Спин-ожидание
        sh++; // Критическая область
        turn = 1; // Передаем очередь
        usleep(1); // Некритическая область
    }
    return NULL;
}

void* my_thread1_turn(void* arg) {
    int i = 0;
    for (; i < 100; i++) {
        while (turn != 1); // Спин-ожидание
        sh += 2; // Критическая область
        turn = 0; // Передаем очередь
        usleep(100); // Некритическая область
    }
    return NULL;
}

// Для третьего примера (POSIX spinlock)
pthread_spinlock_t lock;

void* my_thread0_posix(void* arg) {
    int i = 0;
    for (; i < 100; i++) {
        pthread_spin_lock(&lock);
        sh++;
        pthread_spin_unlock(&lock);
        usleep(1);
    }
    return NULL;
}

void* my_thread1_posix(void* arg) {
    int i = 0;
    for (; i < 100; i++) {
        pthread_spin_lock(&lock);
        sh += 2;
        pthread_spin_unlock(&lock);
        usleep(100);
    }
    return NULL;
}

int main() {
    pthread_t th_id[2];

    printf("Тест 1: Без синхронизации\n");
    sh = 0;
    pthread_create(&th_id[0], NULL, my_thread0_no_sync, NULL);
    pthread_create(&th_id[1], NULL, my_thread1_no_sync, NULL);
    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);
    printf("Результат: %d\n", sh);

    printf("\nТест 2: Спин-блокировка с переменной turn\n");
    sh = 0;
    turn = 0;
    pthread_create(&th_id[0], NULL, my_thread0_turn, NULL);
    pthread_create(&th_id[1], NULL, my_thread1_turn, NULL);
    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);
    printf("Результат: %d\n", sh);

    printf("\nТест 3: Спин-блокировка с POSIX pthread_spinlock_t\n");
    sh = 0;
    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE); // Инициализация спинлока
    pthread_create(&th_id[0], NULL, my_thread0_posix, NULL);
    pthread_create(&th_id[1], NULL, my_thread1_posix, NULL);
    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);
    pthread_spin_destroy(&lock); // Уничтожение спинлока
    printf("Результат: %d\n", sh);

    return 0;
}