//
// Created by Harlan on 2016/11/15.
//

#include <cstdio>

void fib(int *, int);

int main() {
    int n;
    scanf("%d", &n);
    int *fibonacci = new int[n];
    fib(fibonacci, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci[i]);
    }
    return 0;
}

void fib(int *f, int n) {
    if (n < 1)return;
    if (n == 1) {
        f[0] = 1;
        return;
    }
    if (n == 2) {
        f[0] = f[1] = 1;
        return;
    }
    f[0] = f[1] = 1;
    for (int i = 2; i < n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
}