#include <iostream>

int main() {
    int n;
    std::cin >> n;
    for (int k = n; k >= 1; --k) {
        for (char x = 'a'; x < 'a' + n; ++x) {
            if (x < 'a' + k)
                std::cout << x;
            else
                std::cout << ' ' << ' ';
        }
        for (char x = 'a' + n - 2; x >= 'a'; --x) {
            if (x < 'a' + k)
                std::cout << x;
            else
                std::cout << ' ' << ' ';
        }
        std::cout << '\n';
    }
}
