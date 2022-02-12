#include <iostream>

int main() {
    int n, j;
    char a;
    std::cin >> n;
    j = n;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < j; ++i) {
            a = 'A' + i;
            std::cout << a;
        }
        if (j <= n - 1) {
            std::cout << ' ' << ' ';
        }
        if (j < n - 1)
            for (int p = 0; p < 4 * (k - 1); ++p)
                std::cout << ' ';
        if (j == n) {
            for (int i = 1; i < j; ++i) {
                --a;
                std::cout << a;
            }
        } else {
            for (int i = 1; i < j + 1; ++i) {
                std::cout << a;
                --a;
            }
        }
        std::cout << '\n';
        j--;
    }
}
