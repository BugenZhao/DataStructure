//
// Created by BugenZhao on 2019/5/17.
//

#include <cstdio>

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int height[6][6];
bool flag[6][6];
int minCost;
int X0, Y0, X, Y;

void dfs(int x, int y, int status, int curCost) {
    if (curCost >= minCost) return;
    if (x == X && y == Y && minCost > curCost) {
        minCost = curCost;
        return;
    }
    flag[x][y] = true;
    for (int i = 0; i < 4; ++i) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 0 || xx >= 6 || yy < 0 || yy >= 6 || flag[xx][yy]) continue;
        dfs(xx, yy, (height[xx][yy] * status) % 4 + 1, curCost + height[xx][yy] * status);
    }
    flag[x][y] = false;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                scanf("%d", &height[i][j]);
            }
        }
        scanf("%d%d%d%d", &X0, &Y0, &X, &Y);
        flag[X0][Y0] = true;
        minCost = 0x7fffffff;
        dfs(X0, Y0, 1, 0);
        printf("%d\n", minCost);
        flag[X0][Y0] = false;
    }
    return 0;
}
