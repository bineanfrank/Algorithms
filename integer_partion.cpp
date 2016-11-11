//
// Created by Harlan on 2016/10/25.
//
#include <stdio.h>

/**
 * 整数的划分个数问题：给定一个整数，求它能由小于或者等于它自身的整数相加的划分个数
 * 例如：4的划分为{4}，{1,1,1,1},{1,1,2},{2, 2},{1,3}总共5种
 *
 * 分析：求一个数的划分，我们设p(n, m)为整数n的不大于m的划分个数
 * 那么会有如下递推式：
 * n < 1 || m < 1   ---> 0,即不存在，因为假设划分的整数最小为1
 * n == 1 || m == 1 ---> 1, 即整数1的划分或者整数n的不大于1的划分,只有一种
 * n < m            ---> p(n, n), 当n < m时,整数n不可能存在这样的划分：划分中有大于n的数
 * n == m           ---> 1+p(n, n-1)当n == m的时候，即为n的所有划分,而n的划分个数可以为n的等于n的划分和小于n的划分。
 * n > m            ---> p(n, m-1)+p(n-m, m),当n > m的时候,n的划分即为n的小于m的划分加上n-m的不小于m的划分，也即存在m的划分和不存在m的划分，
 *                                            p(n-m,m)就是要先减去一个m，因为是一定存在m的，然后在剩余的当中找出不小于m的划分。
 *
 *
 * @param n
 * @param m
 * @return
 */
int partion(int n, int m) {
    if (n < 1 || m < 1)return 0;
    else if (n == 1 || m == 1)return 1;
    else if (n < m)return partion(n, n);
    else if (n == m)return 1 + partion(n, m - 1);
    else return partion(n, m - 1) + partion(n - m, m);
}

int main() {
    for (int i = 0; i < 8; i++) {
        printf("%d的划分个数为：%d\n", i, partion(i, i));
    }
    return 0;
}