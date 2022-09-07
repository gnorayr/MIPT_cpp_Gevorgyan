#include <iostream>

int used[35];

int main()
{
    int n,l;
    std::cin >> n;
    while (n--)
    {
        int a, b;
        std::cin >> a >> b;
        for (int i = 0; i < b; i++)
            used[a + i] = 1;
    }

    std::cin >> l;

    for (int i = 0; i <= 29; i++)
    {
        if (i)
            used[i] += used[i - 1];
    }

    if (used[l - 1] == 0)
    {
        std::cout << 0 << std::endl;
        return 0;
    }

    for (int i = l; i <= 29; i++)
        if(used[i]-used[i-l]==0)
        {
            std::cout << i-l+1 << std::endl;

            return 0;
        }


    std::cout<<-1<<std::endl;
    return 0;
}