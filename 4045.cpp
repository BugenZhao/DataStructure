//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

/*
int lessCount[10005][10005];
int p[10005];

int main() {
    int n, m;
    cin >> n >> m;
    int tmp;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &tmp);
        p[i] = tmp;
        for (int j = 1; j <= n; ++j) {
            lessCount[j][i] = lessCount[j][i - 1] + (j > tmp);
        }
    }

    int l, r, x;
    while (m--) {
        scanf("%d%d%d", &l, &r, &x);
        tmp = p[x];
        if (lessCount[tmp][r] - lessCount[tmp][l] == x - l) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}

*/

int main() {
    int table[10005];
    int n, m;
    cin >> n >> m;
    int tmp;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &table[i]);
    }

    int l, r, x, count;
    while (m--) {
        scanf("%d%d%d", &l, &r, &x);
        if (x < l || x > r) {
            printf("Yes\n");
            continue;
        }
        count = 0;
        tmp = table[x];
        for (int i = l; i <= r; ++i) {
            if (table[i] < tmp) ++count;
        }
        if (count == x - l) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}