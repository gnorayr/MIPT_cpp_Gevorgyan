#include <chrono>
#include <iostream>
#include <random>


const int n = 7;
const int m = 7;
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
int num = 10;


void matrix(int a[n][m]) {
    int number = 0;
    while (number != num) {
        std::uniform_int_distribution<int> distn(0, n - 1);
        std::uniform_int_distribution<int> distm(0, m - 1);
        int x = distn(rng);
        int y = distm(rng);
        if (a[x][y] == 0)
            ++number;
        a[x][y] = 1;
    }
}

void move(int a[n][m]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 0) {
                continue;
            }
            if (j == 0 || j == m - 1) {
                continue;
            }
            if (n != 1) {
                if (i == 0 || i == n - 1) {
                    continue;
                }
            }
            if (n != 1) {
                if (a[i + 1][j] == 1 || a[i - 1][j] == 1)
                    continue;
            }
            if (a[i][j + 1] == 1 || a[i][j - 1] == 1)
                continue;
            a[i][j] = 2;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 2) {
                std::uniform_int_distribution<int> dist(0, 3);
                std::uniform_int_distribution<int> dist_1(0, 1);
                if (n != 1) {
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
                } else {
                    int random = dist_1(rng);
                    if (random == 0 && a[i][j + 1] != 1) {
                        a[i][j] = 0;
                        a[i][j + 1] = 1;
                    }
                    if (random == 1 && a[i][j - 1] != 1) {
                        a[i][j] = 0;
                        a[i][j - 1] = 1;
                    }

                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 2)
                a[i][j] = 1;
        }
    }

}


int main() {
    int step = 0;
    int coincidence = 0;
    int a[n][m] = {};
    int b[n][m] = {};
    matrix(a);
    while (true) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                b[i][j] = a[i][j];
                std::cout << a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        move(a);
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (a[i][j] == b[i][j])
                    ++coincidence;
            }
        }
        if (coincidence == m * n)
            break;
        coincidence = 0;
        ++step;
    }
    std::cout << "steps =" << " " << step << " ";
}
