#include <random>
#include <chrono>

int main() {
    std::random_device dev;
    //std::mt19937 rng(dev()); // for unix-like systems
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count()); // for windows
    int seed = 123456;
    std::mt19937 rng(seed); // hardcoded seed
    std::uniform_int_distribution<int> dist(0, 3);
    std::cout << dist(rng) << '\n';
}
