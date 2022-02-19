#include <chrono>
#include <iostream>
#include <random>


const int n = 10;
const int m = 10;
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
int num = 15;


void matrix(int a[n][m]) {
    int number = 0;
    while (number != num) {
        std::uniform_int_distribution<int> dist(0, n);
        int x = dist(rng);
        int y = dist(rng);
        a[x][y] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] == 1)
                    ++number;
            }
        }
        if (number != num)
            number = 0;
    }
}

void move(int a[n][m]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 0) {
                continue;
            }
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                continue;
            }
            if (a[i + 1][j] == 1 || a[i - 1][j] == 1 || a[i][j + 1] == 1 || a[i][j - 1] == 1)
                continue;
            a[i][j] = 2;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 2) {
                std::uniform_int_distribution<int> dist(0, 3);
                int random = dist(rng);
                if (random == 0 && a[i + 1][j] != 1) {
                    a[i][j] = 0;
                    a[i + 1][j] = 1;
                }
                if (random == 1 && a[i - 1][j] != 1) {
                    a[i][j] = 0;
                    a[i - 1][j] = 1;
                }
                if (random == 2 && a[i][j + 1] != 1) {
                    a[i][j] = 0;
                    a[i][j + 1] = 1;
                }
                if (random == 3 && a[i][j - 1] != 1) {
                    a[i][j] = 0;
                    a[i][j - 1] = 1;
                }
            }
        }
    }
}


int main() {
    int step;
    int a[n][m] = {};
    matrix(a);
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                std::cout << a[i][j] << " ";
            std::cout << std::endl;
        }
        move(a);
        std::cout << std::endl;
    }
}

