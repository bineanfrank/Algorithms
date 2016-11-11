//
// Created by Harlan on 2016/11/11.
// 一维最接近点对问题 ---》 分治法思想
// 给定平面上n个点，找其中的一对点，
// 使得在n个点的所有点对中，该点对的距离最小。
// 严格地说，最接近点对可能多于1对。为了简单起见
// 这里只限于找其中的一对。
//

#include <stdio.h>

struct Pair {
    float distance;
    float x1, x2;
};

/**
 * return the min element from array p
 * @param p
 * @param l
 * @param r
 * @return
 */
float min(float p[], int l, int r) {
    float p_min = p[l];
    for (int i = l + 1; i <= r; i++) {
        if (p_min > p[i]) {
            p_min = p[i];
        }
    }
    return p_min;
}

/**
 * find the max element from array p
 * @param p
 * @param l
 * @param r
 * @return
 */
float max(float p[], int l, int r) {
    float p_max = p[l];
    for (int i = l + 1; i <= r; i++) {
        if (p_max < p[i]) {
            p_max = p[i];
        }
    }
    return p_max;
}

void swap(float &a, float &b) {
    float temp = a;
    a = b;
    b = temp;
}

int partition(float s[], float x, int l, int r) {
    int i = l - 1, j = r + 1;
    while (true) {
        while (s[++i] < x && i < r);
        while (s[--j] > x);
        if (i >= j) {
            break;
        }
        swap(s[i], s[j]);
    }
    return j;
}

Pair closest_point_pair(float p[], int l, int h) {
    Pair min_pair = {99999, 0, 0}; //最小点对，初始化距离为最大值99999
    if (h - l < 1)return min_pair;

    //找出中位数
    float p_min = min(p, l, h);
    float p_max = max(p, l, h);
    float p_mid = (p_max + p_min) / 2;

    //分成两部分
    int j = partition(p, p_mid, l, h); // partition it

    //递归求左右两部分的最近点对
    Pair pair_left = closest_point_pair(p, l, j);
    Pair pair_right = closest_point_pair(p, j + 1, h);

    //左右两部分的最近点对求完后，开始合并结果，根据分析
    //求出左部分的最大点，右部分的最小点即可
    float p_left = max(p, l, j);
    float q_right = min(p, j + 1, h);

    if (pair_left.distance < pair_right.distance) {
        if (q_right - p_left < pair_left.distance) {
            min_pair.distance = q_right - p_left;
            min_pair.x1 = q_right;
            min_pair.x2 = p_left;
            return min_pair;
        } else return pair_left;
    } else {
        if (q_right - p_left < pair_right.distance) {
            min_pair.distance = q_right - p_left;
            min_pair.x1 = q_right;
            min_pair.x2 = p_left;
            return min_pair;
        } else return pair_right;
    }
}

int main() {
    float points[25] = {20.14, 3.04, 8.85, 31.72, 40.97, 81.27, 41.15, 45.13, 25.5, 81.84, 3.96, 5.18, 30.82, 72.23,
                        21.13, 57.59, 76.39, 60.28, 87.88, 13.67, 1.22, 7.82, 9.23, 29.09, 30.15};
    Pair pair = closest_point_pair(points, 0, 24);
    printf("Closest point pair : <%.2f, %.2f>\n", pair.x1, pair.x2);
    printf("distance = %.2f\n", pair.distance);
    return 0;
}