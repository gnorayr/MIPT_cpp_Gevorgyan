#include <iostream>

int main() {

    int a, c;
    std::cin >> a;
    c = 1;


    for(int i = 1; i < a + 1; ++i)
    {
        c *= i;
    }



    std::cout << c << std::endl;
    return 0;
}
