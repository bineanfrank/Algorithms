//
// Created by Harlan on 2016/11/21.
//

#include <cstdio>

// 枚举法
void max_sub_sum(int *array, int n, int &best_i, int &best_j, int &best_sum);

//分治法
int max_sub_sum(int *array, int left, int right);

//动态规划
int max_sub_sum(int *a, int n);

int main() {
    int best_i, best_j, best_sum = 0;
    int *array = new int[13]{1, -1, 0, 45, 23, 56, -45, 34, 67, 12, -98, 0, 12};
    int n = 13;

    //分治法
    printf("best_sum = %d.\n", max_sub_sum(array, 0, n - 1));

    //枚举法
    //max_sub_sum(array, n, best_i, best_j, best_sum);
    //printf("best_i = %d, best_j = %d, best_sum = %d.\n", best_i, best_j, best_sum);

    //动态规划
    printf("best_sum = %d.\n", max_sub_sum(array, n);
    return 0;
}

// 枚举法
void max_sub_sum(int *array, int n, int &best_i, int &best_j, int &best_sum) {

    int temp_sum = 0;
    for (int i = 0; i < n; i++) {
        temp_sum = 0;
        for (int j = i; j < n; j++) {
            temp_sum += array[j];
            if (temp_sum > best_sum) {
                best_sum = temp_sum;
                best_i = i;
                best_j = j;
            }
        }
    }
}

/**
 * 分治法
 * @param array
 * @param left
 * @param right
 * @return
 */
int max_sub_sum(int *array, int left, int right) {

    int max_sum = 0;

    //分治需要递归，首先需要知道递归出口
    if (left == right) {
        max_sum = array[left] > 0 ? array[left] : 0;
    } else {

        //计算左右两边
        int center = (left + right) / 2;
        int left_best_sum = max_sub_sum(array, left, center);
        int right_best_sum = max_sub_sum(array, center + 1, right);

        //合并
        //计算s1
        int s1 = 0, temp_s1 = 0;
        for (int i = center; i >= left; i--) {
            temp_s1 += array[i];
            if (temp_s1 > s1) {
                s1 = temp_s1;
            }
        }

        //计算s2
        int s2 = 0, temp_s2 = 0;
        for (int i = center + 1; i <= right; i++) {
            temp_s2 += array[i];
            if (temp_s2 > s2) {
                s2 = temp_s2;
            }
        }

        //三者中取较大者返回
        max_sum = s1 + s2;
        if (left_best_sum > max_sum) {
            max_sum = left_best_sum;
        }

        if (right_best_sum > max_sum) {
            max_sum = right_best_sum;
        }
    }
    return max_sum;
}

// 动态规划 b[i] = max(b[i-1] + a[i], a[i])
int max_sub_sum(int *a, int n) {
    int sum = 0, b = 0;
    for (int i = 1; i <= n; i++) {
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