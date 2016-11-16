//
// Created by Harlan on 2016/11/15.
// 贪心算法实现最短路径
//

#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

#define MAX_LEN 20

int matrix[MAX_LEN][MAX_LEN];//matrix[v1][v2]表示从v1到v2的距离
int trace[MAX_LEN];
int min_path[MAX_LEN];//min_path[v]表示从v点到最后一个点的最小距离
int vertex_num;
string node[MAX_LEN] = {"A", "B1", "B2", "C1", "C2", "C3", "C4", "D1", "D2", "D3", "E"};

ifstream fin("E:\\CLion\\Algorithms\\in.txt");

int min_distance(int);

int main() {

    //初始化点的个数
    fin >> vertex_num;

    printf("%d\n", vertex_num);

    //初始化邻接矩阵
    for (int i = 0; i < vertex_num; i++) {
        for (int j = 0; j < vertex_num; j++) {
            fin >> matrix[i][j];
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    //初始化路径和最短路径
    memset(trace, 0, sizeof(int) * MAX_LEN);
    memset(min_path, 0, sizeof(int) * MAX_LEN);

    //求第一个点到最后一个点的最小路径
    int min_d = min_distance(0);

    printf("Shortest path is min_distance = %d\n", min_d);
    printf("The path is :\n");
    int k = 0;
    cout << node[0] << "->";
    while (min_d > 0) {
        cout << node[trace[k]];
        min_d -= matrix[k][trace[k]];
        if (min_d > 0) {
            cout << "->";
        }
        k = trace[k];
    }
    return 0;
}

/**
 * 表示编号为v的节点到最后节点的最短距离
 * @param v
 * @return
 */
int min_distance(int v) {
    if (min_path[v] > 0)return min_path[v];
    if (v == vertex_num - 1)return 0; //临界值，v点和自身的距离自然为0
    int min_dis = 99999, dis, j;

    //从下一个节点开始
    for (int i = v + 1; i < vertex_num; i++) {
        if (matrix[v][i] > 0) { //存在路径，则计算最短路径
            dis = matrix[v][i] + min_distance(i);
            if (min_dis > dis) {
                min_dis = dis;
                j = i;
            }
        }
    }
    min_path[v] = min_dis;
    trace[v] = j;

    return min_path[v];
}