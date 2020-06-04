//
// Created by BugenZhao on 2019/3/16.
//
// 线性探测

#include <iostream>

using namespace std;

int main() {
    int M, T, U, F, D;
    cin >> M >> T >> U >> F >> D;
    int ans = 0;
    int curr = 0;
    for (int i = 0; i < T; ++i) {
        char c;
        cin >> c;
        switch (c) {
            case 'u':
            case 'd':
                curr += U + D;
                break;
            case 'f':
                curr += 2 * F;
                break;
        }
        if (curr > M) {
            cout << ans << endl;
            return 0;
        }
        ++ans;
    }
    cout << T << endl;
}