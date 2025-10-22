#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

const long long N = 100000000;
const int NUM_THREADS = 4;

struct ThreadData {
    long long start;
    long long end;
    long long sum;
};

void calculate_sum(ThreadData& data) {
    data.sum = 0;
    for (long long i = data.start; i <= data.end; ++i) {
        data.sum += i;
    }
}

int main() {
    std::vector<ThreadData> thread_data(NUM_THREADS);
    std::vector<std::thread> threads;

    // Вычисляем размер блока для каждого потока
    long long block_size = N / NUM_THREADS;
    long long remainder = N % NUM_THREADS;

    // Создаем потоки
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].start = i * block_size + 1;
        if (i == NUM_THREADS - 1) {
            thread_data[i].end = N; // Последний поток получает остаток
        } else {
            thread_data[i].end = (i + 1) * block_size;
        }
        threads.emplace_back(calculate_sum, std::ref(thread_data[i]));
    }

    // Измеряем время
    auto start = std::chrono::high_resolution_clock::now();

    // Ждем завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    long long total_sum = 0;
    for (const auto& data : thread_data) {
        total_sum += data.sum;
    }

    std::cout << "C++11 <thread>" << std::endl;
    std::cout << "Сумма: " << total_sum << std::endl;
    std::cout << "Время выполнения: " << duration.count() << " мс" << std::endl;

    return 0;
}