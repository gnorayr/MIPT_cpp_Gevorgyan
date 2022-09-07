#include <iostream>
#include <cmath>

char *simplify_direction(char const *input, int size) {
    int N = 0, S = 0, W = 0, E = 0;
    for (int i = 0; i < size; ++i) {
        if (input[i] == 'N') {
            ++N;
        }
        if (input[i] == 'E') {
            ++E;
        }
        if (input[i] == 'S') {
            ++S;
        }
        if (input[i] == 'W') {
            ++W;
        }
    }
    int sizeY = N - S;
    int sizeX = E - W;
    size = abs(sizeY) + abs(sizeX);
    char *output = new char[size + 1];
    output[size] = '0';
    if (sizeY < 0) {
        for (int i = 0; i < abs(sizeY); ++i) {
            output[i] = 'S';
        }
    } else {
        for (int i = 0; i < sizeY; ++i) {
            output[i] = 'N';
        }
    }
    if (sizeX < 0) {
        for (int i = abs(sizeY); i < abs(sizeY) + abs(sizeX); ++i) {
            output[i] = 'W';
        }
    } else {
        for (int i = abs(sizeY); i < abs(sizeY) + abs(sizeX); ++i) {
            output[i] = 'E';
        }
    }
    return output;
}

int main() {
    int size;
    std::cin >> size;
    char input[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> input[i];
    }
    int i = 0;
    char *output;
    output = simplify_direction(input, size);
    while (output[i] != '0') {
        std::cout << output[i] << " ";
        ++i;
    }
}
