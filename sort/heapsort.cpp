#include <chrono>
#include <iostream>
#include <random>

const int n = 300;
int array[n] = {};

std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

void generate_massive(int (&a)[n]) {
    std::uniform_int_distribution<int> dist(0, 1000);
    for (int i = 0; i < n; ++i) {
        int x = dist(rng);
        a[i] = x;
    }
}

void heap_swap(int list[n], int i, int k) {
    if (i * 2 + 1 >= k)
        return;
    int max = 2 * i + 1;
    if (2 * i + 2 < k && list[2 * i + 1] < list[2 * i + 2])
        max = 2 * i + 2;
    if (list[i] < list[max]) {
        std::swap(list[i], list[max]);
        heap_swap(list, max, k);
    }
}

void heap(int (&list)[n]) {
    for (int j = n / 2 - 1; j >= 0; --j)
        heap_swap(list, j, n);
    for (int i = n - 1; i >= 0; --i) {
        std::swap(list[i], list[0]);
        heap_swap(list, 0, i);
    }
}

auto nanoseconds_since_epoch() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();
}

int main() {
    generate_massive(array);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    auto start_time = nanoseconds_since_epoch();
    heap(array);
    //std::cout << (nanoseconds_since_epoch() - start_time) / 1000000 << " milliseconds elapced." << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
