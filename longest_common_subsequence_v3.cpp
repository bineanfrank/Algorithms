//
// Created by Harlan on 2016/11/18.
// v1 和 v2版本其实没有考虑有多个最长公共子序列的问题
// 从LCSLength中可以看出，我们还有一个情况没有给出单独判断，
// 那就是c[i-1][j] == c[i][j-1]的情况，那就是有多个LCS的情况
// 这里再b[i][j] = 4表示第四种情况

#include <cstdio>

using namespace std;

const int M = 7;
const int N = 6;

typedef int **Matrix;

// 节点元素
typedef struct _element {
    int lcs_len;
    int row;
    int col;
} Element;

template<class T>
class StackNode {
public:
    T data;
    StackNode *next;
};

// Stack类，摘自 http://blog.csdn.net/liufeng_king/article/details/8500084
template<class T>
class Stack {
public:
    Stack(void) : top(NULL) {} // 构造函数，将栈顶指针置空

    bool IsEmpty(void) const { return top == NULL; }

    void push(const T data);

    bool pop(T *data); // 移除栈顶元素，保存至data

    bool peek(T *data) const; // 获取栈顶元素至data，但是不移除元素，若栈为空，则返回false，获取成功放回true

    StackNode<T> *GetStackNode(); //返回栈顶指针，即返回整个栈

private:
    StackNode<T> *top;
};

template<class T>
StackNode<T> *Stack<T>::GetStackNode() {
    return top;
}

template<class T>
void Stack<T>::push(const T data) {
    StackNode<T> *node = new StackNode<T>();
    node->data = data;
    node->next = top;
    top = node;
}

template<class T>
bool Stack<T>::peek(T *data) const {
    if (IsEmpty()) return false;
    *data = top->data;
    return true;
}

template<class T>
bool Stack<T>::pop(T *data) {
    if (IsEmpty()) return false;
    *data = top->data;
    StackNode<T> *node = top;
    top = top->next;
    delete (node);
    return true;
}

void LCS(int row, int col, Matrix c, Matrix b, char *x);

void LCSLength(char *x, char *y, Matrix c, Matrix b);

Element create(int length, int x, int y);

void print_stack(Stack<Element> *s, char x[], int len);

Matrix GenerateMatrix(int row, int col);

void DeleteMatrix(Matrix p, int row);

void search(Matrix b, int cur_pos_x, int cur_pos_y, int &e_pos_x, int &e_pos_y, int ntype);

int main() {
    char x[] = {' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B'}; // length = 7
    char y[] = {' ', 'B', 'D', 'C', 'A', 'B', 'A'}; // length = 6
    Matrix c, b;
    c = GenerateMatrix(M, N);
    b = GenerateMatrix(M, N);
    LCSLength(x, y, c, b);
    LCS(M, N, c, b, x);
    DeleteMatrix(b, M);
    DeleteMatrix(c, M);
    return 0;
}

Matrix GenerateMatrix(int row, int col) {
    Matrix p = new int *[row + 1];
    for (int i = 0; i <= row; i++) {
        p[i] = new int[col + 1];
    }
    return p;
}

void DeleteMatrix(Matrix p, int row) {
    for (int i = 0; i <= row; i++) {
        delete[]p[i];
    }

    delete[]p;
}

/*
 * 求LCS的长度并构造b[][],用于回溯求各个LCS
 * 这里加入b[][] = 4标志，表示有相同长度的LCS
 */
void LCSLength(char *x, char *y, Matrix c, Matrix b) {

    // 初始化第一行和第一列，LCS为0
    for (int i = 1; i <= M; i++)c[i][0] = 0;
    for (int i = 1; i <= N; i++)c[0][i] = 0;

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            } else {
                if (c[i - 1][j] > c[i][j - 1]) {
                    c[i][j] = c[i - 1][j];
                    b[i][j] = 2;
                } else if (c[i - 1][j] < c[i][j - 1]) {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = 3;
                } else {
                    c[i][j] = c[i][j - 1]; // c[i][j - 1] == c[i - 1][j]
                    b[i][j] = 4;
                }
            }
        }
    }
    printf("LCS Length = %d\n", c[M][N]);
}

/**
 * 建立一个虚拟节virtual node点作为起始节点，压入栈中
 * 以此节点开始，搜索其左上角的节点，判断其位置b[i][j]的值
 * 1. 则返回
 * 2. 搜索上方
 * 3. 搜索左边
 * 4. 判断ntype：0上方，1左方
 *
 * 搜索得到的结果，若为同一个点，直接压入栈，否则矩形搜索值为1的点（代码中有注释）
 *
 *
 * @param row
 * @param col
 * @param c
 * @param b
 * @param x
 */
void LCS(int row, int col, Matrix c, Matrix b, char *x) {
    if (x == NULL || c == NULL || b == NULL)return;
    Element store_top; //store栈顶节点
    Element virtual_node; //虚拟节点
    Element temp_node;
    int top_lcs_len;
    Stack<Element> store, print; //保存栈和打印栈
    int i, j;
    int x1, y1, x2, y2;

    //创建虚拟节点压入栈中
    virtual_node = create(c[row][col] + 1, row + 1, col + 1);
    store.push(virtual_node);
    while (!store.IsEmpty()) {
        store.pop(&store_top);
        print.push(store_top);

        if (store_top.row == 1 || store_top.col == 1) { //到了临界点
            //打印栈中除虚拟节点以外的节点，因为虚拟节点在矩阵右下角添加，所以可以由row判断
            print_stack(&print, x, row);
            printf("\n");

            //获取store栈中的栈顶元素
            store.peek(&temp_node);
            top_lcs_len = temp_node.lcs_len;

            // print栈退栈至上一个分支点，上一个分支点即为store栈的栈顶节点
            while (print.peek(&temp_node) && temp_node.lcs_len <= top_lcs_len) {
                print.pop(&temp_node);
            }
        } else {
            //分别以两种模式搜索左上角节点
            search(b, store_top.row - 1, store_top.col - 1, x1, y1, 0);
            search(b, store_top.row - 1, store_top.col - 1, x2, y2, 1);

            //两种模式搜索出的第一个为1的节点后
            if (x1 == x2 && y1 == y2) { // 说明是同一个点，压入栈即可
                temp_node = create(c[x1][y1], x1, y1);
                store.push(temp_node);
            } else { // 说明有多个点，搜索以x1, x2, y1, y2为对角线的矩形，符合条件的压入栈
                for (i = x1; i <= x2; i++) {
                    for (j = y2; j <= y1; j++) {
                        if (b[i][j] == 1) {
                            temp_node = create(c[i][j], i, j);
                            store.push(temp_node);
                        }
                    }
                }
            }
        }
    }
}

void print_stack(Stack<Element> *s, char *x, int len) {
    if (s == NULL || x == NULL)return;
    StackNode<Element> *sn = s->GetStackNode();
    while (sn != NULL && sn->data.row <= len) {
        printf("%c ", x[sn->data.row]);
        sn = sn->next;
    }
}

void search(Matrix b, int cur_pos_x, int cur_pos_y, int &e_pos_x, int &e_pos_y, int ntype) {
    //printf("cur_pos_x = %d ,cur_pos_y = %d\n", cur_pos_x, cur_pos_y);
    switch (b[cur_pos_x][cur_pos_y]) {
        case 1:
            e_pos_x = cur_pos_x;
            e_pos_y = cur_pos_y;
            //return;
            break;
        case 2:
            search(b, cur_pos_x - 1, cur_pos_y, e_pos_x, e_pos_y, ntype);
            break;
        case 3:
            search(b, cur_pos_x, cur_pos_y - 1, e_pos_x, e_pos_y, ntype);
            break;
        case 4:
            if (ntype == 0) {
                search(b, cur_pos_x - 1, cur_pos_y, e_pos_x, e_pos_y, ntype);
            } else {
                search(b, cur_pos_x, cur_pos_y - 1, e_pos_x, e_pos_y, ntype);
            }
            break;
        default:
            break;
    }
}

Element create(int length, int x, int y) {
    Element element;
    element.lcs_len = length;
    element.row = x;
    element.col = y;
    return element;
}
