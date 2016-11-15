//
// Created by Harlan on 2016/11/15.
// 循环赛事日程安排问题
//  (1)每个选手必须与其他n-1个选手各赛一次；
//  (2)每个选手一天只能参赛一次；
//  (3)循环赛在n-1天内结束。
//

#include <cstdio>

void schedule_it(int **, int, int);

int main() {
    int k, n = 1;
    scanf("%d", &k);

    for (int i = 1; i <= k; i++)n *= 2;

    int **a = new int *[n + 1];
    for(int i = 0; i <= n; i++){
        a[i] = new int[n+1];
    }

    schedule_it(a, n, k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void schedule_it(int **a, int n, int k) {

    //先对第一行填充
    for (int i = 1; i <= n; i++) {
        a[1][i] = i;
    }

    int m = 1;
    for (int s = 1; s <= k; s++) {
        /*
         * 将表格分成k部分进行填充
         * 然后对每一部分将表格分成 n/2等份，例如n=8时
         * 将表格的第一二三部分分别分成4,2,1等份进行填充
         */
        n /= 2;
        for (int t = 0; t < n; t++) {//分好之后对这几个等份进行填充

            for (int i = m + 1; i <= m * 2; i++) {
                for (int j = m + 1; j <= m * 2; j++) {
                    a[i][j + t * m * 2] = a[i - m][j + t * m * 2 - m]; //填充右下角
                    a[i][j + t * m * 2 - m] = a[i - m][j + t * m * 2];//填充左下角
                }
            }
        }
        m *= 2; //更新起始填充位置
    }
}