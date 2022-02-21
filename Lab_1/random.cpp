#include <chrono>
#include <iostream>
#include <random>

const int n = 10;
const int m = 10;
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
int num = 7;

void generateMatrix(int a[n][m]) {
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
    const int di[] = {0, 0, 1, -1};
    const int dj[] = {1, -1, 0, 0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 0 || j == 0 || j == m - 1)
                continue;
            if (n != 1) {
                if (i == 0 || i == n - 1 || a[i + 1][j] == 1 || a[i - 1][j] == 1)
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
                std::uniform_int_distribution<int> gen(0, 3);
                std::uniform_int_distribution<int> gen_1(0, 1);
                int direction = (n == 1 ? gen_1 : gen)(rng);
                int newi = i + di[direction];
                int newj = j + dj[direction];
                if (a[newi][newj] == 0) {
                    a[i][j] = 0;
                    a[newi][newj] = 1;
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
    int steps = 0;
    int a[n][m] = {};
    int b[n][m] = {};
    generateMatrix(a);
    //Breaks when all particles are dead.
    while (true) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                b[i][j] = a[i][j];
                std::cout << a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        move(a);
        bool areDifferent = false;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (a[i][j] != b[i][j])
                    areDifferent = true;
        if (!areDifferent)
            break;
        ++steps;
    }
    std::cout << "steps =" << " " << steps << " ";
}
