#include <iostream>
#include <vector>
#include <numeric>

int main() {
    using ull = unsigned long long;
    int n;
    std::cin >> n;
    std::vector<ull> dp(n);
    dp[0] = 1;
    for (int i = 1; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j + 2 < i; ++j) {
            dp[i] += dp[j];
        }
    }
    std::cout << std::accumulate(dp.begin(), dp.end(), 1ll) << '\n';
}