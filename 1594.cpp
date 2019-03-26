//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    auto table = new ll *[N + 1];
    for (int i = 0; i <= N; ++i) {
        table[i] = new ll[M + 1]{};
    }

    int tmp;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            scanf("%d", &tmp);
            table[i][j] = table[i][j - 1] + table[i - 1][j] - table[i - 1][j - 1] + tmp;
        }
    }

    int x1, y1, x2, y2;
    while (Q--) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        ll ans = table[x2][y2] - table[x1 - 1][y2] - table[x2][y1 - 1] + table[x1 - 1][y1 - 1];
        if (ans < 0) ans = -ans;
        printf("%lld\n", ans);
    }

    for (int i = 0; i <= N; ++i) {
        delete[] table[i];
    }
    delete[] table;
    return 0;
}