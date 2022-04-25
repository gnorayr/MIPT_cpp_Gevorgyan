#include <iostream>

void sort(int n, int *list) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (list[j] > list[j + 1])
                std::swap(list[j], list[j + 1]);
        }
    }
}

int minimum(int size, int *list) {
    int min = list[0];
    for (int i = 0; i < size; ++i) {
        if (list[i] < min) {
            min = list[i];
        }
    }
    return min;
}

int *copy_array(int oldSize, int newSize, int *arr) {
    int *newArr = new int[newSize];
    for (int i = 0; i < oldSize; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    return newArr;
}

int length(int size, int *list, int *optional) {
    if (size < 2)
        return 0;
    if (size == 2) {
        return (list[1] - list[0]);
    }
    if (size == 3)
        return (list[2] - list[0]);
    if (optional[size - 1] != 0)
        return optional[size - 1];
    int distance[2];
    for (int i = 1; i < 3; ++i) {
        if (i == 1)
            distance[i - 1] = length(size - i, list, optional) + (list[size - 1] - list[size - 2]);
        else {
            distance[i - 1] = length(size - i, list, optional) + (list[size - 1] - list[size - 2]);
        }
    }
    int min = minimum(2, distance);
    optional[size - 1] = min;
    return min;
}

int main() {
    int size = 1;
    int *array = new int[size];
    int n;
    while (std::cin >> n) {
        array[size - 1] = n;
        ++size;
        array = copy_array(size - 1, size, array);
    }
    --size;
    int *optional = new int[size]{0};
    sort(size, array);
    std::cout << length(size, array, optional);
    delete []optional;
    delete []array;
}
