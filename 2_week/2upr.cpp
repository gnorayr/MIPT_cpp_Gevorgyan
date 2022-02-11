#include <iostream>

int main() {
    int n, a = 0, b = 0;
    bool is_correct = true;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        char x;
        std::cin >> x;
        if (x == ')')
            ++a;
        if (x == '(')
            ++b;
        if (a > b) {
            is_correct = false;
            break;
        }
    }
    if (a != b) {
        is_correct = false;
    }
    if (is_correct)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
}
