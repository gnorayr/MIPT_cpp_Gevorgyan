#include <chrono>
#include <iostream>
#include <random>

const int n = 17;
int array[n] = {};
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

void generate_massive(int (&a)[n]) {
    std::uniform_int_distribution<int> dist(0, 100);
    for (int i = 0; i < n; ++i) {
        int x = dist(rng);
        a[i] = x;
    }
}

template<typename T>
struct Comparator {
    virtual bool operator( )(T const &, T const &) const = 0;
};

template<typename T>
struct SimpleComparator : Comparator<T> {
    bool operator( )(T const &lha, T const &rha) const override {
        return lha < rha;
    }
};

template<typename T>
void qsort(T (&list)[n], int l, int r, Comparator<T> const &comp) {
    if (!comp(l, r))
        return;
    T p = list[r];
    int l_1 = l;
    int r_1 = r;
    --l;
    ++r;
    while (comp(l + 1, r)) {
        while (comp(l + 1, r) && comp(list[l + 1], p)) {
            ++l;
        }
        while (comp(l, r - 1) && !comp(list[r - 1], p)) {
            --r;
        }
        if (l + 1 != r)
            std::swap(list[l + 1], list[r - 1]);
    }
    std::swap(list[r_1], list[r]);
    qsort(list, l_1, l, comp);
    qsort(list, r + 1, r_1, comp);
}

int main() {
    generate_massive(array);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    //double array[n] = {1.2, 4.4, 5.6, 2.1, 2.0};
    std::cout << std::endl;
    SimpleComparator<int> comp;
    qsort(array, 0, n - 1, comp);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
