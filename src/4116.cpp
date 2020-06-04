//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

int n, s;
int *x;

bool check(int d) {
    int count = 1, lastPos = 0;
    for (int i = 1; i < n; ++i) {
        if (x[i] - lastPos >= d) {
            ++count;
            lastPos = x[i];
        }
    }
    return count >= s;
}

int main() {
    cin >> n >> s;
    x = new int[n]{};
    for (int i = 0; i < n; ++i) {
        scanf("%d", x + i);
    }
    sort(x, x + n);
    int tmp = x[0];
    for (int i = 0; i < n; ++i) {
        x[i] -= tmp;
    }
    int min = 0, mid, max = x[n - 1];
    while (min <= max) {
        mid = (min + max) / 2;
        if (check(mid)) min = mid + 1;
        else max = mid - 1;
    }
    cout << max << endl;
}