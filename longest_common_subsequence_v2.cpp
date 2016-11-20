//
// Created by Harlan on 2016/11/18.
// 最长公共子序列问题
// 因为b[][]的作用只是用于判断c[i][j] c[i-1][j] c[i][j-1]三者之间的关系
// 但是这并不需要，因为可以直接用c本身判断，所以可以去掉b
// 经过空间优化之后，去掉了b[][]
//

#include <cstdio>

char x[] = {' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B'}; // length = 7
char y[] = {' ', 'B', 'D', 'C', 'A', 'B', 'A'}; // length = 6

const int M = 7;
const int N = 6;

void LCS(int m, int n, char x[], int c[][N + 1]);

void LCSLength(int c[][N + 1]);

int main() {
    int c[M + 1][N + 1];
    LCSLength(c);
    LCS(M, N, x, c);
    return 0;
}

void LCSLength(int c[][N + 1]) {

    // 初始化第一行和第一列，LCS为0
    for (int i = 1; i <= M; i++)c[i][0] = 0;
    for (int i = 1; i <= N; i++)c[0][i] = 0;

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
            } else {
                c[i][j] = c[i][j - 1];
            }
        }
    }
}

void LCS(int i, int j, char x[], int c[][N + 1]) {
    if (i == 0 || j == 0) {
        return;
    }
    if (c[i][j] == c[i - 1][j - 1] + 1) {
        LCS(i - 1, j - 1, x, c);
        printf("%c ", x[i]);
    } else if (c[i - 1][j] >= c[i][j - 1]) {
        LCS(i - 1, j, x, c);
    } else {
        LCS(i, j - 1, x, c);
    }
}
