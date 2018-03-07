//
// Created by Harlan on 2016/11/8.
// 分之法思想：合并排序

#include <stdio.h>
#include <malloc.h>

void merge(int *a, int left, int mid, int right) {
    int *b = (int *) malloc(sizeof(int) * (right - left + 1));

   // printf("%d\n", sizeof(int));

    //int b[right - left + 1];
    if (!b) {
        printf("merge failed!\n");
        return;
    }
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)b[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i <= mid)b[k++] = a[i++];
    while (j <= right)b[k++] = a[j++];

    for (int i = left, k = 0; i <= right; k++, i++)a[i] = b[k];
}

void merge_sort(int a[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

int main() {
    int a[15] = {49, 38, 65, 97, 76, 13, 27, 0, 10, 23, 55, 1093, 1, 222, 454};
    merge_sort(a, 0, 14);
    for (int i = 0; i <= 14; i++) {
        printf("%d ", a[i]);             //输出测试
    }
    return 0;
}