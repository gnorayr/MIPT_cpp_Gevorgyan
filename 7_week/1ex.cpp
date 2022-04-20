#include <iostream>


void sort(int n, int *list) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (list[j] > list[j + 1])
                std::swap(list[j], list[j + 1]);
        }
    }
}

int main() {
    int n, s;
    std::cin >> s >> n;
    int *array = new int[n];
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        array[i] = a;
    }
    sort(n, array);
    int sum = 0;
    int w = 0;
    for (int i = 0; i < n; ++i) {
        if (sum + array[i] < s) {
            sum += array[i];
            ++w;
        } else
            break;
    }
    delete[] array;
    std::cout << w;
}
