#include <iostream>
#include <cmath>

int number(long a) {
    long quotient = a / 10;
    int b = 1;
    while (quotient != 0) {
        quotient /= 10;
        ++b;

    }
    return b;
}


void reverse(int &a)
{
    int num, b = 0;
    num = number(a);
    for (int i = 0; i < num; ++i)
    {
       b += a % 10 * pow(10, num - i - 1);
       a /= 10;
    }
    a = b;
}
int main()
{
    int a;
    std::cin >> a;
    reverse(a);
    std::cout << a << std::endl;
}
