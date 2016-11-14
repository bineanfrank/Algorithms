/**
 * Created by Harlan on 2016/11/13.
 *
 * 二维最接近点对问题 ---》 分治法思想
 * 给定平面上n个点，找其中的一对点，使得在n个点的所有点对中，该点对的距离最小。
 * 严格地说，最接近点对可能多于1对。
 * 为了简单起见 这里只限于找其中的一对。
 */

#include <math.h>
#include <stdlib.h>
#include <cstdio>

struct Point {
    float x;
    float y;
};

struct Pair {
    Point a, b;
    float dis;
};

float distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Pair min(Pair p1, Pair p2) {
    return p1.dis < p2.dis ? p1 : p2;
}

int compareX(const void *a, const void *b) {
    Point *p1 = (Point *) a, *p2 = (Point *) b;
    return (p1->x - p2->x);
}

int compareY(const void *a, const void *b) {
    Point *p1 = (Point *) a, *p2 = (Point *) b;
    return (p1->y - p2->y);
}

/**
 * 暴力解决规模小的情况
 * @param points
 * @param n
 * @return
 */
Pair bruceForce(Point points[], int n) {
    Pair pair;
    float dist = 99999.0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            //if (j == i)continue;
            float tempDist = distance(points[i], points[j]);
            if (dist > tempDist) {
                dist = tempDist;
                pair.a = points[i];
                pair.b = points[j];
                pair.dis = dist;
            }
        }
    }
    return pair;
}

/**
 * d块条内的最短距离对
 * @param strip
 * @param n
 * @param d
 * @return
 */
Pair stripClosest(Point strip[], int n, Pair d) {
    Pair min_pair = d;
    qsort(strip, n, sizeof(Point), compareY);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && (strip[j].y - strip[i].y) < min_pair.dis; j++) {
            if (distance(strip[i], strip[j]) < min_pair.dis) {
                min_pair.a = strip[i];
                min_pair.b = strip[j];
                min_pair.dis = distance(strip[i], strip[j]);
            }
        }
    }
    return min_pair;
}

/**
 * 求最近点对
 * @param points
 * @param n
 * @return
 */
Pair closest_point_pair(Point points[], int n) {
    Pair pair = {points[0], points[1], distance(points[0], points[1])};
    if (n < 2)return pair;

    qsort(points, n, sizeof(Point), compareX);

    //小于或等于3个点的，暴力解决
    if (n <= 3)return bruceForce(points, n);

    //找到中间点
    int mid = n / 2;
    Point midPoint = points[mid];

    //找到最有两部分的最近点对
    Pair dl = closest_point_pair(points, mid);
    Pair dr = closest_point_pair(points + mid, n - mid);

    //获取两者之间较小的
    Pair d = min(dl, dr);

    //计算整个集合中较小的
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        //收集左右两个集合中距离小于d这对的距离的点对
        if (fabs(points[i].x - midPoint.x) < fabs(d.a.x - d.b.x)) {
            strip[j++] = points[i];
        }
    }

    return min(d, stripClosest(strip, j, d));
}

int main() {
    Point points[] = {{2.0,  3.0},
                      {12.0, 30.0},
                      {40.0, 50.0},
                      {5.0,  1.0},
                      {12.0, 10.0},
                      {3.0,  4.0}};
    int n = sizeof(points) / sizeof(points[0]);
    Pair pair = closest_point_pair(points, n);
    printf("The smallest point pair is <%.2f, %.2f> <%.2f, %.2f>.\n", pair.a.x, pair.a.y, pair.b.x, pair.b.y);
    printf("The smallest distance is %.2f.\n", pair.dis);
    return 0;
}