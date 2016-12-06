//
// Created by Harlan on 2016/12/4.
//

int max_m_sum(int m, int n, int *a);

int main() {
    int m, n, *a;
    cin >> m >> n;
    for (int i = 0; i < n; i++)cin >> *(a++);
    int max_sum = max_m_sum(m, n, a);
    cout << "Max m sub sum = " << max_sum << endl;
    return 0;
}

int max_m_sum(int m, int n, int *a) {
    if (n < m || m < 1)return 0;
    int b[m + 1][n + 1];
    for (int i = 0; i < m + 1; i++)b[i][0] = 0;
    for (int i = 0; i < n + 1; i++)b[0][i] = 0;

    // 枚举段数，从1段开始到m段
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= n - m + i; j++) {
            if (j > i) {
                b[i][j] = b[i][j - 1] + a[j];//代表a[j]同a[j-1]一起，都在最后一子段中
                for (int k = i - 1; k < j; k++) {
                    if (b[i][j] < b[i - 1][k] + a[j])
                        b[i][j] = b[i - 1][k] + a[j];//代表最后一子段仅包含a[j]
                }
            } else {
                b[i][j] = b[i - 1][j - 1] + a[j];//当i=j时，每一项为一子段
            }
        }
    }
    int sum = 0;
    for (int j = m; j <= n; j++) {
        if (sum < b[m][j]) {
            sum = b[m][j];
        }
    }
    return sum;
}