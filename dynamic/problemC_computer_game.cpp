#include <iostream>
#include <cmath>

int minimum(int size, int const *list) {
    int min = list[0];
    for (int i = 0; i < size; ++i) {
        if (list[i] < min) {
            min = list[i];
        }
    }
    return min;
}

int energy(int n, int *coordinate, int *memoization) {
    if (n < 2) {
        return 0;
    }
    if (n == 2) {
        return abs(coordinate[1] - coordinate[0]);
    }
    if (memoization[n] != 0) {
        return memoization[n];
    }
    int cases[2];
    cases[0] = energy(n - 1, coordinate, memoization) + abs(coordinate[n - 2] - coordinate[n - 1]);
    cases[1] = energy(n - 2, coordinate, memoization) + 3 * abs(coordinate[n - 3] - coordinate[n - 1]);
    int min = minimum(2, cases);
    memoization[n] = min;
    return min;
}


int main() {
    int n;
    std::cin >> n;
    int coordinate[n];
    int y;
    for (int i = 0; i < n; ++i) {
        std::cin >> y;
        coordinate[i] = y;
    }
    int *memoization = new int[n+1]{0};
    std::cout << energy(n, coordinate, memoization);
    delete []memoization;
}
