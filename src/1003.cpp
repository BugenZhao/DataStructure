//
// Created by BugenZhao on 2019/3/16.
//
// 广度优先搜索

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int N = 100 + 5;

class Point {
public:
    int X;
    int Y;
};

Point ds[] = {{-1, 0},
              {1,  0},
              {0,  -1},
              {0,  1}};

int main() {
    int L;
    cin >> L;
    int table[N][N];
    queue<Point> q;
    for (int i = 1; i <= L; ++i) {
        for (int j = 1; j <= L; ++j) {
            cin >> table[i][j];
            if (table[i][j] == 1)
                q.push(Point{i, j});
        }
    }

    int count = 0;
    while (true) {
        queue<Point> qNew;
        while (!q.empty()) {
            Point point = q.front();
            q.pop();
            for (const Point &d:ds) {
                int x = point.X + d.X;
                int y = point.Y + d.Y;
                if (1 <= x && x <= L
                    && 1 <= y && y <= L) {
                    switch (table[x][y]) {
                        case 0:
                            table[x][y] = 1;
                            qNew.push(Point{x, y});
                            break;
                        case 1:
                        case 2:
                            break;
                    }
                }
            }
        }
        if (qNew.empty()) {
            cout << count << endl;
            return 0;
        }
        ++count;
        q = qNew;
    }
}