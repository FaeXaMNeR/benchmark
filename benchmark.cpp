#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

void cpu_task(double& result, long long iterations) {
    double sum = 0.0;
    for (long long i = 1; i <= iterations; ++i) {
        sum += atan(sqrt(log(i) + 1)) * sin(i) / pow(cos(i), 2.0);
    }
    result = sum;
}

int main() {
    const unsigned int num_threads = thread::hardware_concurrency();
    const long long iterations_per_thread = 100000000;
    vector<double> results(num_threads, 0.0);
    vector<thread> threads;

    cout << "Тестирование производительности CPU (" << num_threads << " потоков)..." << endl;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(cpu_task, ref(results[i]), iterations_per_thread);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    double total = 0.0;
    for (const auto& res : results) {
        total += res;
    }
    cout << "Проверочная сумма: " << total << endl;

    // Расчет условных "баллов"
    double score = (iterations_per_thread * num_threads) / (duration / 1000.0);
    cout << "Результат:" << endl;
    cout << "    Время выполнения: " << duration << " мс" << endl;
    cout << "    Производительность: " << score / 1e6 << " млн. операций/сек" << endl;

    return 0;
}