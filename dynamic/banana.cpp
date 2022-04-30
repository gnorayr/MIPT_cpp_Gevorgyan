#include <iostream>


int *banana(int *s1, int size1, int *s2, int size2, int *s3) {
    if (size1 == 0 || size2 == 0)
        return s3;
    if (s1[size1 - 1] == s2[size2 - 1]) {
        ++s3[0];
        s3[s3[0]] = s1[size1 - 1];
        banana(s1, size1 - 1, s2, size2 - 1, s3);
        return s3;
    }
    if (banana(s1, size1 - 1, s2, size2, s3)[0] > banana(s1, size1, s2, size2 - 1, s3)[0]) {
        ++s3[0];
        s3[s3[0]] = s1[size2 - 1];
        return s3;
    } else {
        if (banana(s1, size1 - 1, s2, size2, s3)[0] < banana(s1, size1, s2, size2 - 1, s3)[0]) {
            ++s3[0];
            s3[s3[0]] = s1[size1 - 1];
            return s3;
        } else {
            return s3;
        }
    }
}

int main() {
    int size1 = 3;
    int *s1 = new int [size1] { 3, 2, 4, };
    int size2 = 2;
    int *s2 = new int [size2] {3, 4,  };
    int *s3 = new int [size2] {0};

    banana(s1, size1, s2, size2, s3);
    for (int i = 1; i < s3[0] + 1; ++ i) {
        std::cout << s3[i] << " ";
    }
}
