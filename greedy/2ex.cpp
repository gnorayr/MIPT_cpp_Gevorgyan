#include <iostream>

int main() {
    int n, k;

    std::cin >> n >> k;
    int s;
    std::cin >> s;
    int *petrol = new int[s + 2];
    int petrol_location;
    for (int i = 0; i < s; ++i) {
        std::cin >> petrol_location;
        petrol[i] = petrol_location;
    }
    petrol[s] = n;
    petrol[s+1] = n;
    int location = 0;
    int stop = 0;
    bool has_enough_fuel = false;
    for (int i = 0; i < s + 2; ++i) {
        if (location >= n) {
            --stop;
            has_enough_fuel = true;
            break;
        }
        if (petrol[i] - location > k) {
            if (!has_enough_fuel)
                break;
            else {
                location = petrol[i - 1];
                ++stop;
                if (petrol[i] - location > k)
                    break;
                --i;
                has_enough_fuel = false;
            }
        } else {
            has_enough_fuel = true;
        };
    }
    delete[] petrol;
    if (!has_enough_fuel) {
        std::cout << -1;
    } else {
        std::cout << stop;
    }
}


