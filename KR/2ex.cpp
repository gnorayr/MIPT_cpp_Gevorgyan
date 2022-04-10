#include <iostream>


int main()
{
    unsigned long long n, ans = 0;
    std::cin >> n;

    for (int i = 0; i < 70; i++)
    {
        n /= 2;
        ans += n;
    }

    std::cout << ans << std::endl;

    return 0;
}

