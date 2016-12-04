//
// Created by Harlan on 2016/11/22.
//

#include <iostream>
#include <cstring>

using namespace std;

const int N = 3;
const int M = 4;

int max_sub_sum(int *a, int n);

int max_sub_matrix_sum(int a[][N], int m, int n);

int main() {
    int a[][N] = {{4,  -2, 9},
                  {-1, 3,  8},
                  {-6, 7,  6},
                  {0,  9,  -5}};

    int sum = max_sub_matrix_sum(a, M, N);
    cout << "sum = " << sum;
    return 0;
}

int max_sub_matrix_sum(int a[][N], int m, int n) {
    int sum = 0;
    int b[n + 1];
    for (int i = 0; i < m; i++) {// 起始行
        memset(b, 0, sizeof(b)); // 置0
        for (int j = i; j < m; j++) { // 结束行
            for (int k = 0; k < n; k++) { // 继续枚举i,j以内的矩阵，记录最大值
                b[k] += a[j][k];
                int max = max_sub_sum(b, n);
                if (max > sum) {
                    sum = max;
                }
            }
        }
    }
    return sum;
}

// 动态规划 b[i] = max(b[i-1] + a[i], a[i])
int max_sub_sum(int *a, int n) {
    int sum = 0, b = 0;
    for (int i = 0; i < n; i++) {
        if (b > 0) {
            b = b + a[i];
        } else {
            b = a[i];
        }

        if (b > sum) {
            sum = b;
        }
    }
    return sum;
}