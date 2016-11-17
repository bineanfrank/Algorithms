//
// Created by Harlan on 2016/11/16.
//

#include<iostream>
#include<cmath>
#include <cstdio>

using namespace std;

int f(int i) {
    int count = i;
    int result = 1;
    while (count > 0) {
        result *= count;
        count--;
    }
    return result;
}

int k(int x, int y) {
    int result = 1;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return x;
}

int main() {
    int t = 9;
    int q = 0;
    int g = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < q; j++)printf(" ");
        int flag = 1;
        for (int k = 0; k < t - q * 2; k++) {
            if (flag) {
                printf("S");
                flag = 0;
            } else {
                printf("T");
                flag = 1;
            }
        }
        printf("\n");
        q++;
        if (!g)break;
        if (q * 2 + 1 == t) { g = 0; }
    }
    return 0;
}

