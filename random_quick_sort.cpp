//
// Created by Harlan on 2016/11/10.
// quick sort, partioned by random position

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

void sort(int array[], int low, int high) {
    if (low >= high)return;
    int p = partion(array, low, high);
    sort(array, low, p);
    sort(array, p + 1, high);
}

void quicksort(int array[], int length) {
    sort(array, 0, length - 1);
}

int main() {
    int a[15] = {49, 38, 65, 97, 76, 13, 27, 0, 10, 23, 55, 1093, 1, 222, 454};
    quicksort(a, 15);
    for (int i = 0; i <= 14; i++) {
        printf("%d ", a[i]);             //输出测试
    }
    return 0;
}

