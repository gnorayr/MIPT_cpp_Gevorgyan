#include <chrono>
#include <iostream>
#include <random>

const int n = 17;
int array[n] = {};
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

void generate_massive(int (&a)[n]) {
    std::uniform_int_distribution<int> dist(0, 100);
    for (int i = 0; i < n; ++i) {
        int x = dist(rng);
        a[i] = x;
    }
}

void qsort(int (&list)[n], int l, int r) {
    if (l >= r)
        return;
    int p = list[r];
    int l_1 = l;
    int r_1 = r;
    --l;
    ++r;
    while (l + 1 < r) {
        while (l + 1 < r && list[l + 1] < p) {
            ++l;
        }
        while (l < r - 1 && list[r - 1] >= p) {
            --r;
        }
        if (l + 1 != r)
            std::swap(list[l + 1], list[r - 1]);
    }
    std::swap(list[r_1], list[r]);
    qsort(list, l_1, l);
    qsort(list, r + 1, r_1);
}

int main() {
    generate_massive(array);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    qsort(array, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
