#include <chrono>
#include <iostream>
#include <random>

const int n = 17;
int array[n] = {};
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

void generate_massive(int (&arr)[n]) {
    std::uniform_int_distribution<int> dist(0, 100);
    for (int & i : arr) {
        int x = dist(rng);
        i = x;
    }
}

void generic_swap(void *lha, void *rha, std::size_t element_byte_size) {
    void *tmp = malloc(element_byte_size);
    memcpy(tmp, lha, element_byte_size);
    memcpy(lha, rha, element_byte_size);
    memcpy(rha, tmp, element_byte_size);
    free(tmp);
}

int list_size(void *begin, void *end, std::size_t element_byte_size) {
    int num = 1;
    auto curr = begin;
    while (curr != end) {
        curr = (void*)((std::size_t)curr + element_byte_size);
        ++num;
    }
    return num;
}

bool less(void *a, void *b) {
    return *((int*)a) < *((int*)b);
}

void* list_element(void *begin, std::size_t element_byte_size, int num) {
    auto curr = begin;
    for (int i = 0; i < num; ++i){
        curr = (void*)((std::size_t)curr + element_byte_size);
    }
    return curr;
}

void generic_qsort(void *begin, std::size_t elem_byte_size, int l, int r, bool (*predicate) (void *, void *)) {
    if (l >= r)
        return;
    auto p = list_element(begin, elem_byte_size, r);
    int l_1 = l;
    int r_1 = r;
    --l;
    ++r;
    while (l + 1 < r) {
        while (l + 1 < r && predicate(list_element(begin, elem_byte_size, l + 1), p)) {
            ++l;
        }
        while (l < r - 1 && !predicate(list_element(begin, elem_byte_size, r - 1), p)) {
            --r;
        }
        if (l + 1 != r)
            generic_swap(list_element(begin, elem_byte_size, l + 1), list_element(begin, elem_byte_size, r - 1), elem_byte_size);
    }
    generic_swap(list_element(begin, elem_byte_size, r_1), list_element(begin, elem_byte_size, r), elem_byte_size);

    generic_qsort(begin, elem_byte_size, l_1, l, predicate);
    generic_qsort(begin, elem_byte_size, r + 1, r_1, predicate);
}

int main() {
    generate_massive(array);
    for (int i : array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    generic_qsort(array, 4, 0, list_size(array, &array[n - 1], 4) - 1, less);
    for (int i : array) {
        std::cout << i << " ";
    }
}
