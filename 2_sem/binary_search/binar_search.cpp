#include <iostream>

int lin(int const a[], int n, int target, int &steps) {
    int place = 0;
    for (int i = 0; i < n; ++i) {
        ++steps;
        if (a[i] == target)
            break;
        else
            ++place;
    }
    return place;
}

int binary(int const a[], int n, int target, int &steps) {
    int l = 0, r = n - 1, m;
    while (l <= r) {
        ++steps;
        m = (l + r) / 2;
        if (a[m] == target)
            break;
        if (a[m] < target)
            l = m + 1;
        else
            r = m - 1;
    }
    return m;
}

int main() {
    const int n = 10;
    int x, steps_lin, steps_bin;
    std::cin >> x;
    int array[n] = {0, 1, 2, 3, 4, 5, 9, 13, 17, 99};
    steps_lin = 0;
    steps_bin = 0;
    std::cout << "place = " << lin(array, n, x, steps_lin) << '\n';
    std::cout << "linear search steps =" << " " << steps_lin << '\n';
    std::cout << "place = " << binary(array, n, x, steps_bin) << '\n';
    std::cout << "binary search steps =" << " " << steps_bin << '\n';
}
