#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 100000000
#define NUM_THREADS 4
#define _POSIX_C_SOURCE 200809L

typedef struct {
    long long start;
    long long end;
    long long sum;
} thread_data_t;

void* calculate_sum(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    data->sum = 0;
    for (long long i = data->start; i <= data->end; ++i) {
        data->sum += i;
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    long long total_sum = 0;

    // Вычисляем размер блока для каждого потока
    long long block_size = N / NUM_THREADS;
    long long remainder = N % NUM_THREADS;

    // Запускаем потоки
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = i * block_size + 1;
        if (i == NUM_THREADS - 1) {
            thread_data[i].end = N; // Последний поток получает остаток
        } else {
            thread_data[i].end = (i + 1) * block_size;
        }
        pthread_create(&threads[i], NULL, calculate_sum, &thread_data[i]);
    }

    // Измеряем время
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Ждем завершения всех потоков
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].sum;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    long long elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;

    printf("Pthreads\n");
    printf("Сумма: %lld\n", total_sum);
    printf("Время выполнения: %lld мс\n", elapsed_ms);

    return 0;
}