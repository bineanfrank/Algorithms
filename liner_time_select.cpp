//
// Created by Harlan on 2016/11/10.
// 中文：线性时间选择，分治法思想
// description: choose the k'th smallest element from a array that is not sorted.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

/**
 * partion it with random position
 * @param array
 * @param low
 * @param high
 * @return
 */
int partion(int array[], int low, int high) {
    srand((unsigned) time(NULL));
    int randomIndex = rand() % (high - low) + low;
    swap(array[low], array[randomIndex]);
    int pivotkey = array[low];
    int l = low, h = high;
    while (l < h) {
        while (l < h && array[h] >= pivotkey)h--;
        array[l] = array[h];
        while (l < h && array[l] <= pivotkey)l++;
        array[h] = array[l];
        array[l] = pivotkey;
    }
    return l;
}

/**
 * find the k'th smallest elemnt from array who's contains 'length' elements.
 * @param array
 * @param length
 * @param k
 */
int liner_time_select(int array[], int low, int high, int k) {

    if (low == high)return array[low];
    int i = partion(array, low, high);
    int j = i - low + 1;
    if (k <= j) { // the k'th smallest element is here.
        return liner_time_select(array, low, i, k);
    } else {
        return liner_time_select(array, i + 1, high, k - j);
    }
}

int liner_time_select(int array[], int length, int k) {
    if (k > length) {
        printf("Wrong parameter!\n");
        return -1;
    }
    return liner_time_select(array, 0, length - 1, k);
}

int main() {
    int a[15] = {49, 38, 65, 97, 76, 13, 27, 0, 10, 23, 55, 1093, 1, 222, 454};
    printf("%d\n", liner_time_select(a, 15, 3));
    return 0;
}

