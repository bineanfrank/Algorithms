//
// Created by Harlan on 2016/11/17.
//
// 6个矩阵:A1 30*35 A2 35*15 A3 15*5 A4 5*10 A5 10*20 A6 20*25
// 可以表示为第一个矩阵的行数和全部矩阵的列数，因为矩阵链中，第i个矩阵的行数等于第i+1个矩阵的列数
// 因为两个矩阵相乘的计算次数：A(x,y)*B(m,n) --> x * y * n
// 多个矩阵连乘的计算次数的计算只需要第一个矩阵的行数和全部矩阵的列数即可
//

#include <cstdio>

const int MAX_LEN = 7;
int p[MAX_LEN] = {30, 35, 15, 5, 10, 20, 25};
int s[MAX_LEN][MAX_LEN];
int m[MAX_LEN][MAX_LEN];

/**
 * 备忘录法 递归实现
 * @param i
 * @param j
 * @return
 */
int matrix_multiply_chain(int i, int j) {

    //若已有结果，直接返回
    if (m[i][j] > 0) m[i][j];
    if (i == j)return 0;

    //计算一个以第一个矩阵为分界点的计算量
    int count = matrix_multiply_chain(i, i) + matrix_multiply_chain(i + 1, j) + p[i - 1] * p[i] * p[j];
    s[i][j] = i;

    //然后从第二个矩阵开始，分别以当前矩阵为分界点，求计算量，若更小，则更新
    for (int k = i + 1; k < j; k++) {
        int t = matrix_multiply_chain(i, k) + matrix_multiply_chain(k + 1, j) + p[i - 1] * p[k] * p[j];
        if (t < count) {
            count = t;
            s[i][j] = k;
        }
    }

    //保存结果
    m[i][j] = count;
    return count;
}

/**
 * 动态规划迭代实现
 * @return
 */
int matrix_chain(int n) {
    for (int i = 0; i < n; i++) {
        m[i][i] = 0; // 一个矩阵计算量为0
    }

    //从规模为2开始，到规模为n，进行划分
    for (int r = 2; r <= n; r++) {
        for (int i = 1; i <= n - r + 1; i++) { //i为矩阵链第一个，根据规模r，i最大为n-r+1
            //j为根据当前i计算出的规模为r的矩阵链的最后一个
            int j = r + i - 1;
            //计算出A[i:j]的初始最小计算量
            m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j]; //其实应该加上m[i][i],但是为0，可以省略

            s[i][j] = i;

            //然后开始用k对i->j进行划分，计算出最优的k位置
            for (int k = i + 1; k < j; k++) {
                int u = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (u < m[i][j]) {
                    m[i][j] = u;
                    s[i][j] = k; //更新i->j链的最优划分点k
                }
            }
        }
    }

    return m[1][n];
}

int main() {
    for (int i = 0; i < MAX_LEN; i++) {
        for (int j = 0; j < MAX_LEN; j++) {
            m[i][j] = 0;
        }
    }
    //int count = matrix_multiply_chain(1, MAX_LEN - 1);
    int count = matrix_chain(MAX_LEN - 1);
    printf("%d\n", count);
    return 0;
}

