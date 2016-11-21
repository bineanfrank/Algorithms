//
// Created by Harlan on 2016/11/21.
// 最长公共子串问题
// 动态规划求解，在使用动态规划求解2个长度分别为p, q的字符串S,T的最长公共子串问题前
// 先给出求它们任意前缀子串对S[1:i],T[1:j]的最长公共后缀的算法，其中:1 ≤ i ≤ p,1 ≤ j ≤ q。
// 设LCSuffix(S[1:i],T[1:j])表示前缀子串对S[1: i] ,T[1:j] 的最长公共后缀，则该问题的递推关系式
// LCSuffix(s[1, i], t[1, j]) =
// 1、LCSuffix(s[1, i-1], t[1, j-1]) + s[i], s[i] == t[j]
// 2、"", s[i] == t[j]
// 类似于最长公共子序列的问题

#include <iostream>

using namespace std;

typedef string **Matrix;

void LCSLength(const string &s, const string &t);

Matrix generateMatrix(int row, int col);

int main() {
    string s = "abab";
    string t = "baba";
    LCSLength(s, t);
    return 0;
}

void LCSLength(const string &s, const string &t) {

    // 引入一个字符串矩阵
    int p = s.size();
    int q = t.size();
    Matrix strMatrix = generateMatrix(p, q);
    string lcs = "";
    int length = 0;

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            char a = s.at(i);
            char b = t.at(j);

            if (a == b) {
                if (i == 0 || j == 0)strMatrix[i][j] = a;
                else strMatrix[i][j] = strMatrix[i - 1][j - 1] + a;
                //更新长度和LCS
                if (strMatrix[i][j].size() > length) {
                    length = strMatrix[i][j].size();
                    lcs = strMatrix[i][j];
                } else if (strMatrix[i][j].size() == length) {
                    lcs = lcs + "," + strMatrix[i][j];
                }
            } else {
                strMatrix[i][j] = "";
            }
        }
    }

    for (int i = 0; i < p; i++) {
        delete[] strMatrix[i];
    }
    delete[] strMatrix;

    cout << "Max length = " << length << endl;
    cout << "Max substring = " << lcs << endl;
}

Matrix generateMatrix(int row, int col) {
    Matrix m = new string *[row];
    for (int i = 0; i < row; i++) {
        m[i] = new string[col];
    }
    return m;
}