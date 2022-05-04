#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    bool black[8][8] = {};
    std::string position;
    for (int i = 0; i < n; ++i) {
        std::cin >> position;
        int x = position[1] - '1';
        int y = position[0] - 'a';
        black[x][y] = true;
    }
    int whiteX, whiteY;
    {
        std::cin >> position;
        whiteY = position[0] - 'a';
        whiteX = position[1] - '1';
    }
    int endingAt[8][8] = {};
    endingAt[whiteX][whiteY] = 1;
    for (int i = 1; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            endingAt[i][j] += (black[i][j] ? (j ? endingAt[i - 1][j - 1] : 0) + (j + 1 < 8 ? endingAt[i - 1][j + 1] : 0) : endingAt[i - 1][j]);
    int answer = 0;
    for (int j = 0; j < 8; ++j) {
        answer += endingAt[7][j];
    }
    std::cout << answer << std::endl;
    return 0;
}
