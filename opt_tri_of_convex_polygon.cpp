//
// Created by Harlan on 2016/12/6.
// optimal triangle of convex polygon, 最优三角剖分

#include <iostream>

using namespace std;

const int N = 7;// 凸多边形边数+1
int weight[][N] = {{0, 2, 2, 3, 1, 4},
                   {2, 0, 1, 5, 2, 3},
                   {2, 1, 0, 2, 1, 4},
                   {3, 5, 2, 0, 6, 2},
                   {1, 2, 1, 6, 0, 1},
                   {4, 3, 4, 2, 1, 0}};//凸多边形的权

int opt_tri_of_convex_polygon(int **t, int **s, int n); // 最优三角剖分
int w(int a, int b, int c); // 权值计算

int main() {
    int **s = new int *[N];
    int **t = new int *[N];

    for (int i = 0; i < N; i++) {
        s[i] = new int[N];
        t[i] = new int[N];
    }

    // 返回最优剖分权值，即最小权值
    int best = opt_tri_of_convex_polygon(t, s, N - 1);

    cout << "best = " << best << endl;
    return 0;
}

int opt_tri_of_convex_polygon(int **t, int **s, int n) {

    // i==j时，t[i][j] = 0
    // 即凸子多边形{v(i-1), v(i)}的最优三角剖分所对应的权函数值位0
    for (int i = 1; i <= n; i++) t[i][i] = 0;

    //从规模为2开始，到规模为n，进行划分
    for (int r = 2; r <= n; r++) {
        for (int i = 1; i <= n - r + 1; i++) { //i为子凸多边形第一个顶点，根据规模r，i最大为n-r+1
            //j为根据当前i计算出的规模为r的子凸多边形最后一个顶点
            int j = r + i - 1; // t[i][j]
            // 计算出一个初始权值，即k = i时的最优值，t[i][i]=0故不添加
            t[i][j] = t[i + 1][j] + w(i - 1, i, j);

            s[i][j] = i; // 记录位置i

            //然后开始用k对i->j进行划分，计算出最优的k位置
            for (int k = i + 1; k < j; k++) {
                int u = t[i][k] + t[k + 1][j] + w(i - 1, k, j);
                if (u < t[i][j]) {
                    t[i][j] = u;
                    s[i][j] = k; //更新i->j链的最优划分点k
                }
            }
        }
    }
    return t[1][n - 1];
}

int w(int a, int b, int c) {
    return weight[a][b] + weight[b][c] + weight[a][c];
}