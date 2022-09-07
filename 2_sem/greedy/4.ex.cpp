#include <iostream>
#include <exception>

struct denom_array_t {
    int *arr;
    int sz;
};

denom_array_t egyptian_fractions(int num, int den) {
    if (num <=0 || den <= 0)
        throw std::invalid_argument("num and den must be positive");
    int size = 0;
    int *array = new int[size + 1];
    auto *a = new denom_array_t{array, size};
    while (true) {
        int l = 1;
        while (true) {
            if (num * l < den)
                ++l;
            else {
                array[size] = l;
                ++size;
                int* newArr = new int[size + 1];
                for (int i = 0; i < size; ++i) {
                    newArr[i] = array[i];
                }
                delete[] array;
                array = newArr;
                newArr = nullptr;
                num = l * num - den;
                den *= l;
                break;
            }
        }
        if (num == 0) {
            a->sz = size;
            a->arr = array;
            return *a;
        }
    }
}


int main() {
    auto a = egyptian_fractions(5, 121);
    std::cout << "size = " << a.sz << std::endl;
    for (int i = 0 ; i < a.sz; ++i) {
        std::cout << a.arr[i]  << " ";
    }
}


