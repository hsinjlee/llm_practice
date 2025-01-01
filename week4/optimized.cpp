
#include <iostream>
#include <cstdint>
#include <cmath>
#include <chrono>

using namespace std;

uint32_t lcg(uint32_t seed, uint32_t a = 1664525, uint32_t c = 1013904223, uint32_t m = 4294967296) {
    uint32_t value = seed;
    while (true) {
        value = (a * value + c) % m;
        yield value;
    }
}

int64_t max_subarray_sum(int32_t n, uint32_t seed, int32_t min_val, int32_t max_val) {
    auto lcg_gen = lcg(seed);
    int32_t random_numbers[n];
    for (int i = 0; i < n; i++) {
        random_numbers[i] = lcg_gen() % (max_val - min_val + 1) + min_val;
    }
    int64_t max_sum = LLONG_MIN;
    int64_t current_sum = 0;
    for (int i = 0; i < n; i++) {
        current_sum = 0;
        for (int j = i; j < n; j++) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
}

int64_t total_max_subarray_sum(int32_t n, uint32_t initial_seed, int32_t min_val, int32_t max_val) {
    int64_t total_sum = 0;
    auto lcg_gen = lcg(initial_seed);
    for (int i = 0; i < 20; i++) {
        uint32_t seed = lcg_gen();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    int32_t n = 10000;
    uint32_t initial_seed = 42;
    int32_t min_val = -10;
    int32_t max_val = 10;

    auto start_time = chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = chrono::high_resolution_clock::now();

    cout << "Total Maximum Subarray Sum (20 runs): " << result << endl;
    cout << "Execution Time: " << chrono::duration_cast<chrono::duration<double>>(end_time - start_time).count() << " seconds" << endl;

    return 0;
}
