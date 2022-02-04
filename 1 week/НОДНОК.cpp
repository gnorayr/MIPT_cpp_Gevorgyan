#include <iostream>

int main() {

    int a, b, c, d, x;
    std::cin >>a >>b;
    c = b;
    d = a;
    x = 1;

    while (x != 0)
    {
        x = d%c;
        if (x != 0) {
            d = c;
            c = x;

        }
    }

    d = a * b / c;

    std::cout << c << ' ' << d << std::endl;
    return 0;
}
