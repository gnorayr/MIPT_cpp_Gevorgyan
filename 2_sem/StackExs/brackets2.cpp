#include <iostream>

struct BracketsCount {
    int parentheses;
    int squareBrackets;
    int curlyBrackets;
};

template<typename Element>
char *copy_array(int oldSize, int newSize, const Element *arr) {
    char *newArr = new char[newSize];
    for (int i = 0; i < oldSize; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    return newArr;
}

BracketsCount *quantity(char *arr, int begin, int end) {
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    for (int i = begin; i < end; ++i) {
        if (arr[i] == '(')
            ++count1;
        if (arr[i] == ')')
            --count1;
        if (arr[i] == '[')
            ++count2;
        if (arr[i] == ']')
            --count2;
        if (arr[i] == '{')
            ++count3;
        if (arr[i] == '}')
            --count3;
        if (count1 < 0 or count2 < 0 or count3 < 0)
            return new BracketsCount{-1, -1, -1};
    }
    return new BracketsCount{count1, count2, count3};
}

bool algorithm(char *arr, int i, int size) {
    while (arr[i] == ')' or arr[i] == ']' or arr[i] == '}') {
        ++i;
        if (i == size) {
            return true;
        }
    }
    int j = i;
    BracketsCount *count = quantity(arr, i, i + 1);
    if (count->parentheses == 1) {
        while (count->parentheses > 0) {
            count = quantity(arr, j, i + 1);
            ++i;
            if (i == size)
                break;
        }
    } else if (count->squareBrackets == 1) {
        while (count->squareBrackets > 0) {
            count = quantity(arr, j, i + 1);
            ++i;
            if (i == size)
                break;
        }
    } else {
        while (count->curlyBrackets > 0) {
            count = quantity(arr, j, i + 1);
            ++i;
            if (i == size)
                break;
        }
    }
    if (quantity(arr, j, i)->parentheses == 0 and quantity(arr, j, i)->curlyBrackets == 0 and quantity(arr, j, i)->squareBrackets == 0)
        return algorithm(arr, j + 1, size);
    else
        return false;
}

int main() {
    int size = 1;
    char *array = new char[size];
    char n;
    while (std::cin >> n) {
        if (n == '^')
            break;
        array[size - 1] = n;
        ++size;
        array = copy_array(size - 1, size, array);
    }
    --size;
    BracketsCount *a = quantity(array, 0, size);
    bool answer;
    if (a->squareBrackets == 0 and a->parentheses == 0 and a->curlyBrackets == 0)
        answer = algorithm(array, 0, size);
    else
        answer =  false;
    std::cout << answer;
}

