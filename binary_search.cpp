//
// Created by Harlan on 2016/10/28.
//
#include <stdio.h>

int binary_search(int *array, int e, int len) {
    int start = 0, end = len - 1;
    int middle;
    while (start <= end) {
        middle = (start + end) / 2;
        if (array[middle] == e)
            return middle;
        else if (e > array[middle])start = middle + 1;
        else end = middle - 1;
    }
    return -1;
}

int main() {
    int array[100];
    bool flag = false;
    for (int i = 0; i < 100; i++) {
        array[i] = i + 1;
    }
    for (int i = 0; i < 100; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    int result1 = binary_search(array, 10, 100);
    printf("pos = %d\n", result1);
    int result2 = binary_search(array, 0, 100);
    printf("pos = %d\n", result2);
    int result3 = binary_search(array, 34, 100);
    printf("pos = %d\n", result3);
    return 0;
}