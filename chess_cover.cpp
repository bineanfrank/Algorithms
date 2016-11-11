//
// Created by Harlan on 2016/10/28.
//

/**
 * tr --> row index of this chess table.
 * tc --> col. index of this chess table.
 * dr --> row index of the initial dest. special cell.
 * dc --> col. index of the initial dest. special cell.
 * size --> chess size(size * size)
 *
 * divide the whole chess panel into 4 parts, and resolve them recursively.
 */
#include <stdio.h>

int chess_board[8][8];
const int SIZE = 8;
int cell_num = 1;

void chess_cover(int tr, int tc, int dr, int dc, int size) {

    if (size == 1) {
        return;
    }

    int s = size / 2;
    int t = cell_num++;

    //左上角
    if (dr < tr + s && dc < tc + s)chess_cover(tr, tc, dr, dc, s);
    else {
        chess_board[tr + s - 1][tc + s - 1] = t;
        chess_cover(tr, tc, tr + s - 1, tc + s - 1, s);
    }

    //右上角
    if (dr < tr + s && dc >= tc + s) chess_cover(tr, tc + s, dr, dc, s);
    else {
        chess_board[tr + s - 1][tc + s] = t;
        chess_cover(tr, tc + s, tr + s - 1, tc + s, s);
    }

    //左下角
    if (dr >= tr + s && dc < tc + s) chess_cover(tr + s, tc, dr, dc, s);
    else {
        chess_board[tr + s][tc + s - 1] = t;
        chess_cover(tr + s, tc, tr + s, tc + s - 1, s);
    }

    //右下角
    if (dr >= tr + s && dc >= tc + s)chess_cover(tr + s, tc + s, dr, dc, s);
    else {
        chess_board[tr + s][tc + s] = t;
        chess_cover(tr + s, tc + s, tr + s, tc + s, s);
    }
}

void print() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%02d ", chess_board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    chess_cover(0, 0, 1, 2, SIZE);
    print();
    return 0;
}