//
// Created by BugenZhao on 2019/3/24.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

int table[1005][1005];
int ans[1005][1005];

int main() {
    int R;
    cin >> R;

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j <= i; ++j) {
            scanf("%d", &table[i][j]);
        }
    }

    ans[0][0] = table[0][0];
    for (int i = 1; i < R; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0) ans[i][j] = ans[i - 1][j];
            else if (j == i) ans[i][j] = ans[i - 1][j - 1];
            else ans[i][j] = max(ans[i - 1][j - 1], ans[i - 1][j]);
            ans[i][j] += table[i][j];
        }
    }

    int maxAns = 0;
    for (int i = 0; i < R; ++i) {
        maxAns = max(maxAns, ans[R - 1][i]);
    }
    cout << maxAns << endl;
    return 0;
}