#include <cstdio>

/**
 * 全排列问题
 * 描述：给定一个字符串，假定里面的元素都不相同，求这个字符串的所有排列。
 * 解释：其实这是数学上的排列组合问题，n个不同元素排列组合，共有A（n, n）中排列方式，即n！种。
 * 思路：以{1, 2, 3, 4, 5}为例
 * 全部的排列可以分为以1,2,3,4,5分别为开头的排列，而这五种排列中，后面四个的排列又有不同排列。
 * 这就需要用到递归了。我们从第一个开始，将第一个元素与后面每一个元素都做一次交换，然后求得交换后的排列，
 * 假设到了最后一个元素5，那么5后面没有元素，所以不存在交换，直接输出即可。
 */

unsigned int count = 0;

void swap(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

/**
 * array数组从第k个元素到第n个元素的全排列
 * @param array
 * @param k
 * @param n
 */
void perm(char *array, int k, int n) {

    //如果排到了最后一个元素，那就不需要交换，直接输出即可
    if (k == n) {
        printf("%s\n", array);
        count++;
    } else { //否则从第一个元素开始，到最后一个元素进行交换，并得到全排列
        for (int i = k; i <= n; i++) {
            swap(*(array + k), *(array + i));
            perm(array, k + 1, n);
            swap(*(array + k), *(array + i));
        }
    }
}

void perm(char *array, int length) {
    perm(array, 0, length - 1);
}

int main() {
    char array[20] = {'1', '2', '3', '4'};
    perm(array, 4);
    printf("总共有%d种！\n", count);
    return 0;
}