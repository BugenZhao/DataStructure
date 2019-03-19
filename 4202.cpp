//
// Created by BugenZhao on 2019/3/18.
//
// 环拆链 动态规划

#include <cstdio>
#include <algorithm>

using namespace std;

int value[100005][3];
int ans[100005][4];

int main() {
    int n;

    scanf("%d", &n);
    for (int k = 1; k <= n; ++k) {
        scanf("%d%d%d", &value[k][0], &value[k][1], &value[k][2]);
    }

    int maxAns = -0x7fffffff;

    for (int i = 0; i < 4; ++i) {
        ans[1][i] = -0x7fffffff;
    }
    ans[1][0] = value[1][0];
    for (int j = 2; j <= n; ++j) {
        ans[j][0] = max(ans[j - 1][2], ans[j - 1][3]) + value[j][0];
        ans[j][1] = ans[j - 1][3] + value[j][1];
        ans[j][2] = ans[j - 1][0] + value[j][1];
        ans[j][3] = max(ans[j - 1][0], ans[j - 1][1]) + value[j][2];
    }
    maxAns = max(maxAns, max(ans[n][2], ans[n][3]));

    for (int i = 0; i < 4; ++i) {
        ans[1][i] = -0x7fffffff;
    }
    ans[1][1] = value[1][1];
    for (int j = 2; j <= n; ++j) {
        ans[j][0] = max(ans[j - 1][2], ans[j - 1][3]) + value[j][0];
        ans[j][1] = ans[j - 1][3] + value[j][1];
        ans[j][2] = ans[j - 1][0] + value[j][1];
        ans[j][3] = max(ans[j - 1][0], ans[j - 1][1]) + value[j][2];
    }
    maxAns = max(maxAns, ans[n][3]);

    for (int i = 0; i < 4; ++i) {
        ans[1][i] = -0x7fffffff;
    }
    ans[1][2] = value[1][1];
    for (int j = 2; j <= n; ++j) {
        ans[j][0] = max(ans[j - 1][2], ans[j - 1][3]) + value[j][0];
        ans[j][1] = ans[j - 1][3] + value[j][1];
        ans[j][2] = ans[j - 1][0] + value[j][1];
        ans[j][3] = max(ans[j - 1][0], ans[j - 1][1]) + value[j][2];
    }
    maxAns = max(maxAns, ans[n][0]);

    for (int i = 0; i < 4; ++i) {
        ans[1][i] = -0x7fffffff;
    }
    ans[1][3] = value[1][2];
    for (int j = 2; j <= n; ++j) {
        ans[j][0] = max(ans[j - 1][2], ans[j - 1][3]) + value[j][0];
        ans[j][1] = ans[j - 1][3] + value[j][1];
        ans[j][2] = ans[j - 1][0] + value[j][1];
        ans[j][3] = max(ans[j - 1][0], ans[j - 1][1]) + value[j][2];
    }
    maxAns = max(maxAns, max(ans[n][0], ans[n][1]));

    printf("%d", maxAns);
    return 0;
}