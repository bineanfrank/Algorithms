//
// Created by Harlan on 2016/11/18.
// 最长公共子序列问题
// 用c[i][j]记录Xi和Yj序列的最长公共子序列的长度。
// 用B[i][j]记录c[i][j]是由哪个子问题的解得到的，
// 即，记录c[i][j]是由c[i-1][j-1] c[i-1][j] c[i][j-1]中的哪个决定的
//

#include <cstdio>

char x[] = {' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B'}; // length = 7
char y[] = {' ', 'B', 'D', 'C', 'A', 'B', 'A'}; // length = 6

const int M = 7;
const int N = 6;

void LCS(int m, int n, char x[], int b[][N + 1]);

void LCSLength(int c[][N + 1], int b[][N + 1]);

int main() {
    int c[M + 1][N + 1];
    int b[M + 1][N + 1];

    LCSLength(c, b);
    LCS(M, N, x, b);

    return 0;
}

void LCSLength(int c[][N + 1], int b[][N + 1]) {

    // 初始化第一行和第一列，LCS为0
    for (int i = 1; i <= M; i++)c[i][0] = 0;
    for (int i = 1; i <= N; i++)c[0][i] = 0;

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 2;
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 3;
            }
        }
    }
}

void LCS(int i, int j, char x[], int b[][N + 1]) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == 1) {
        LCS(i - 1, j - 1, x, b);
        printf("%c ", x[i]);
    } else if (b[i][j] == 2) {
        LCS(i - 1, j, x, b);
    } else {
        LCS(i, j - 1, x, b);
    }
}
