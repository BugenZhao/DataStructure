//
// Created by BugenZhao on 2019/3/28.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

bool table[2600][1300];
int dp[2600][1300];

int main() {
    int n, m;
    char tmp;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            do {
                scanf("%c", &tmp);
            } while (tmp == '\n');
            table[2 * i - 1][j] = tmp == '-';
            table[2 * i][j] = tmp == '-';
        }
    }

    int maxAns = 0;

    for (int i = 1; i <= 2 * n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (table[i][j]) {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                maxAns = max(dp[i][j], maxAns);
            }
        }
    }

    maxAns = maxAns / 2 * 2;
    cout << maxAns * maxAns / 2 << endl;
    return 0;
}
