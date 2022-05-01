#include <iostream>

int main() {
    int size;
    std::cin >> size;
    int sequence[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> sequence[i];
    }
    int d[size];

    for (int i=0; i<size; ++i) {
        d[i] = 1;
        for (int j=0; j<i; ++j)
            if (sequence[j] < sequence[i])
                d[i] = std::max(d[i], 1 + d[j]);
    }
    int ans = d[0];
    for (int i=0; i<size; ++i)
        ans = std::max(ans, d[i]);
    std::cout << ans << std::endl;
}
