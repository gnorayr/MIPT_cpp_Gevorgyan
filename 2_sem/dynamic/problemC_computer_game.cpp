#include <iostream>
#include <cmath>

int energy(int n, int *coordinate, int *cache) {
    if (n < 2) {
        return 0;
    }
    if (n == 2) {
        return abs(coordinate[1] - coordinate[0]);
    }
    if (cache[n] != 0) {
        return cache[n];
    }
    int cases[2];
    cases[0] = energy(n - 1, coordinate, cache) + abs(coordinate[n - 2] - coordinate[n - 1]);
    cases[1] = energy(n - 2, coordinate, cache) + 3 * abs(coordinate[n - 3] - coordinate[n - 1]);
    return cache[n] = std::min(cases[0], cases[1]);
}

int main() {
    int n;
    std::cin >> n;
    int coordinate[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> coordinate[i];
    }
    int *cache = new int[n+1]{0};
    std::cout << energy(n, coordinate, cache);
    delete[] cache;
}
