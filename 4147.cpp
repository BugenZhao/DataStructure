//
// Created by BugenZhao on 2019/3/16.
//
// 娱乐

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    int w, h;
    int max;
    int currHeight = 0x7fffffff;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> w >> h;
        if (w > h) {
            swap(w, h);
        }
        if (currHeight < w) {
            cout << "NO" << endl;
            return 0;
        } else if (currHeight < h) {
            currHeight = w;
        } else {
            currHeight = h;
        }
    }
    cout << "YES" << endl;
    return 0;
}