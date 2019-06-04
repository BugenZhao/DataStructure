//
// Created by BugenZhao on 2019/5/17.
//

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;

unsigned N;
int d[15][15];
const int statusCount = 1U << 16U;
int dp[15][statusCount];

int getBit(unsigned num) {
    unsigned k = 1;
    int ans = 0;
    while (k <= 2 * num) {
        ans += (bool) (num & k);
        k <<= 1U;
    }
    return ans;
}

int getAns(int cur, unsigned status) {
    if (dp[cur][status] != -1) return dp[cur][status];
    if (getBit(status) == 2) {
        dp[cur][status] = d[0][cur];
        return dp[cur][status];
    }

    int ret = 0x7fffffff;
    for (unsigned i = 1; i < N; ++i) {
        if (i == cur) continue;
        if (status & (1U << i)) {
            int ans = getAns(i, status - (1U << cur)) + d[i][cur];
            if (ans < ret) ret = ans;
        }
    }
    dp[cur][status] = ret;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> d[i][j];
        }
    }

    if (N == 1) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < statusCount; ++j) {
            dp[i][j] = -1;
        }
    }

    int minAns = 0x7fffffff;
    dp[0][1] = 0;
    for (int i = 1; i < N; ++i) {
        int ans = d[0][i] + getAns(i, (1U << N) - 1);
        if (minAns > ans) minAns = ans;
    }
    cout << minAns << endl;
    return 0;

}