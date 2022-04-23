#include <iostream>

int main() {
    int x;
    std::cin >> x;
    int a[] = {100, 50, 25, 5, 1};
    int coins = 0;
    for (int i : a) {
        coins += x/i;
        x %= i;
    }
    std::cout << coins;
}
