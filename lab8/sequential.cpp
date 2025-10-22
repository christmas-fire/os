#include <iostream>
#include <chrono>

int main() {
    const long long N = 100000000;
    long long sum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (long long i = 1; i <= N; ++i) {
        sum += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Последовательный код" << std::endl;
    std::cout << "Сумма: " << sum << std::endl;
    std::cout << "Время выполнения: " << duration.count() << " мс" << std::endl;

    return 0;
}