#include <iostream>

int const number = 10;
int const L_0 = ;

int navar(int length[number], int price[number], int * optimals, int l_0 = L_0, int max = 1) {
    if (l_0 == 0)
        return max;
    int cost[number];
    int count = 0;
    for (int i = 0; i < number; ++i) {
        if (l_0 - length[i] == 0) {
            cost[i] = price[i];
            ++count;
        } else {
            if (l_0 - length[i] > 0) {
                if (*(optimals + (l_0 - length[i])) != 0) {
                    cost[i] = optimals[l_0 - length[i]] + price[i];
                    ++count;
                } else {
                    optimals[l_0 - length[i]] = navar(length, price, optimals, l_0 - length[i]);
                    cost[i] = optimals[l_0 - length[i]] + price[i];
                    ++count;
                }
            } else
                break;
        }
    }
    max = cost[0];
    for (int i = 0; i < count; ++i) {
        if (cost[i] > max) {
            max = cost[i];
        }
    }
    return max;
}

int main() {
    int length[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int * buffer = new int [L_0] {0};
    std::cout << navar(length, price, buffer);
    delete[] buffer;
}
