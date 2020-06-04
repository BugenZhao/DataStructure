//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using ll=long long;

int main() {
    int tmp;
    bool flag[3][9][9];
    int n;
    cin >> n;
    while (n--) {
        bool wrong = false;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                for (int k = 0; k < 3; ++k) {
                    flag[k][i][j] = false;
                }
            }
        }
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                scanf("%d", &tmp);
                if (wrong) continue;
                int k = i / 3 * 3 + j / 3;
                if (flag[0][i][tmp] || flag[1][j][tmp] || flag[2][k][tmp]) {
                    wrong = true;
                } else {
                    flag[0][i][tmp] = flag[1][j][tmp] = flag[2][k][tmp] = true;
                }
            }
        }
        if (wrong) printf("Wrong\n");
        else printf("Right\n");
    }
    return 0;
}
