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
    int table[500 * 500 + 5];
    int M, N;
    cin >> M >> N;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", table + i * N + j);
        }
    }
    sort(table, table + M * N);
    int n = 0;
    while (n != M * N - 1 && table[n] == table[n + 1]) ++n;

    ll water;
    cin >> water;

    double height;
    double area;
    while (n != M * N - 1) {
        ll tmp = (table[n + 1] - table[n]) * (n + 1);
        if (water <= tmp) {
            height = table[n] + water / (n + 1.0);
            area = (n + 1.0) / (M * N) * 100.0;
            break;
        } else {
            water -= tmp;
            ++n;
            while (n != M * N - 1 && table[n] == table[n + 1]) ++n;
        }
    }
    if (n == M * N - 1) {
        height = table[n] + water / (n + 1.0);
        area = 100.0;
    }
    printf("%.2lf\n%.2lf\n", height, area);
    return 0;
}