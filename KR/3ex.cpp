#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int* compress(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++)
    {
        int c = 0;
        for (int j = 0; j < m; j++)
            if (matrix[i][j])
                c++;
        if (c != 3)
        {
            for (int i = 0; i < n; i++)
                delete[] matrix[i];
            delete[] matrix;
            return nullptr;
        }
    }
    int* arr = new int[n * 3];
    int cnt = 0;
    cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j])
                arr[cnt++] = matrix[i][j];

    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    return arr;
}

int main()
{
    int n, m;
    cin >> n >> m;
    int** a = new int*[n];
    for (int i = 0; i < n; i++)
        a[i] = new int[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    int* compressed = compress(a, n, m);

    if (!compressed) return 0;

    for (int i = 0; i < n * 3; i++)
        cout << compressed[i] << " ";
    cout << endl;

    delete[] compressed;
    return 0;
}