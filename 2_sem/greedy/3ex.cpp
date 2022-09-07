#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int *start = new int[n];
    int *finish = new int[n];
    for (int i = 0; i < n; ++i) {
        int s, f;
        std::cin >> s;
        std::cin >> f;
        start[i] = s;
        finish[i] = f;
    }
    int visit = 0;
    bool will_visit = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (finish[j] > start[i]) {
                will_visit = false;
            }
        }
        if (will_visit) {
            ++visit;
        }
        will_visit = true;
    }
    std::cout << visit;
}
