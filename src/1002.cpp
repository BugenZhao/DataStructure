//
// Created by BugenZhao on 2019/3/19.
//
// 多重滑动窗口

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

constexpr int N = 1000 + 5;
int height[N][N];

int main() {
    int l, w;
    cin >> l >> w;
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < w; ++j) {
            scanf("%d", &height[i][j]);
        }
    }
    int a, b;
    cin >> a >> b;
    int X = l - a + 1, Y = w - b + 1;

    int chunk[N]{};
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            chunk[0] += height[i][j];
        }
    }

    int currentAns = chunk[0];

    for (int y = 1; y < Y; ++y) {
        chunk[y] = chunk[y - 1];
        for (int i = 0; i < a; ++i) {
            chunk[y] += height[i][y + b - 1];
            chunk[y] -= height[i][y - 1];
        }
        currentAns = max(currentAns, chunk[y]);
    }

    for (int x = 1; x < X; ++x) {
        for (int y = 0; y < Y; ++y) {
            for (int j = 0; j < b; ++j) {
                chunk[y] += height[x + a - 1][j + y];
                chunk[y] -= height[x - 1][j + y];
            }
            currentAns = max(currentAns, chunk[y]);
        }
    }

    cout << currentAns << endl;
    return 0;
}