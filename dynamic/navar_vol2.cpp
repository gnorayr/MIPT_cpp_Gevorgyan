#include <iostream>

int const number = 10;
int const L_0 = 17;

int navar(int length[number], int price[number], int *optimals, int **subsequence, int l_0 = L_0, int max = 0) {

    subsequence[1][0] = 1;
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
                    optimals[l_0 - length[i]] = navar(length, price, optimals, subsequence, l_0 - length[i]);
                    cost[i] = optimals[l_0 - length[i]] + price[i];
                    ++count;
                }
            } else
                break;
        }
    }
    for (int i = 0; i < count; ++i) {
        if (cost[i] > max) {
            max = cost[i];
            optimals[l_0] = max;
            int j = 0;
            if (l_0 - length[i] == 0) {
                for (j = 0; j < subsequence[l_0 - length[i]][0] ; ++ j) {
                    subsequence[l_0][j] = subsequence[l_0 - length[i]][j];
                }
            } else {
                for (j = 0; j < subsequence[l_0 - length[i]][0] + 1; ++ j) {
                    subsequence[l_0][j] = subsequence[l_0 - length[i]][j];
                }
            }
            if (l_0 - length[i] == 0) {
                subsequence[l_0][j + 1] = length[i];
                subsequence[l_0][0] = j + 1;
            }
            else {
                subsequence[l_0][j] = length[i];
                subsequence[l_0][0] = j ;
            }
        }

    }
    return max;
}

int main() {
    int length[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int *optional = new int[L_0 + 1]{0};
    int **subsequence = new int *[L_0 + 2];
    for (int i = 0; i < L_0 + 2; i++) {
        subsequence[i] = new int[L_0 + 2];
    }
    for (int i = 0; i < L_0 + 2; i++) {
        for (int j = 0; j < L_0 + 2; j++) {
            subsequence[i][j] = 0;
        }
    }
    std::cout << navar(length, price, optional, subsequence) << std::endl;

    for (int j = 1; j < subsequence[L_0][0] + 1; ++j) {
        std::cout << subsequence[L_0][j] << " ";
    }
    delete[] optional;
    for (int i = 0; i < L_0 + 1; i++) {
        delete[] subsequence[i];
    }
    delete[] subsequence;
}
