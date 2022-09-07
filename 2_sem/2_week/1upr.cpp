#include <iostream>
#include <cmath>

bool prime(int a) {
    bool prime = true;
    if (a >= 1) {
        for (int k = 2; k < a; ++k) {
            if (a % k == 0) {
                prime = false;
            }
        }
    } else
        prime = false;
    return prime;
}

int number(long a) {
    long quotient = a / 10;
    int b = 1;
    while (quotient != 0) {
        quotient /= 10;
        ++b;

    }
    return b;
}

bool palindrome(long a) {
    int num;
    bool pol = true;
    num = number(a);
    int a_1 = a, a_2, a_3, a_4;
    if (num != 1) {
        for (int i = 1; i <= num / 2; ++i) {
            a_2 = a_1 % 10;
            a_4 = a / pow(10, (num - (i - 1)));
            a_3 = a / pow(10, (num - i)) - a_4 * 10;
            if (a_2 != a_3)
                pol = false;
            a_1 /= 10;
        }
    }
    return pol;
}

int main() {
    int n, a;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a;

        std::cout << "prime = " << prime(a) << " " << "palindrome = " << palindrome(a) << std::endl;

    }
}
