//
// Created by BugenZhao on 2019/3/28.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

bool notPrime[1005] = {};
bool table[2005][2005];

int main() {
    for (int i = 2; i < 1005; ++i) {
        if (!notPrime[i]) {
            for (int j = 2; j * i < 1005; ++j) {
                notPrime[i * j] = true;
            }
        }
    }

    int n, m;
    char tmp;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            do {
                scanf("%c", &tmp);
            } while (tmp == '\n');
            table[i][j] = tmp == '1';
        }
    }

    int minAns = 0x7fffffff;

    int s = min(m, n);
    int t = max(m, n);
    int CNT;
    int cnt;
    int max = (n >= 100 || m >= 100) ? 23 : s;
    for (int p = 2; p <= max; ++p) {
        if (notPrime[p]) continue;
        CNT = 0;
        for (int x = 0; x < n; x += p) {
            for (int y = 0; y < m; y += p) {
                cnt = 0;
                for (int i = 0; i < p; ++i) {
                    for (int j = 0; j < p; ++j) {
                        cnt += table[x + i][y + j];
                    }
                }
                CNT += min(cnt, p * p - cnt);
            }
        }
        minAns = min(minAns, CNT);
    }

    cout << minAns << endl;
    return 0;
}