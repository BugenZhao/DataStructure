//
// Created by BugenZhao on 2019/3/17.
//

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

static const auto _____ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

using ll=long long;

ll getAnswer(int N, int i, int j) {
    ll ans = 0;
    int a[] = {i, j, N - i + 1, N - j + 1};
    sort(begin(a), end(a));
    int level = a[0];
    for (int k = 1; k < level; ++k) {
        ans += (N - (2 * k - 1)) * 4;
    }
    if (a[0] == j) {
        ans += N - i + 1 - level;
    } else if (a[0] == i) {
        ans += (N - (2 * level - 1)) + j - level;
    } else if (a[0] == N - j + 1) {
        ans += (N - (2 * level - 1)) * 2 + i - level;
    } else if (a[0] == N - i + 1) {
        ans += (N - (2 * level - 1)) * 3 + N - j + 1 - level;
    }
    return ans;
}

int main() {
    int N, i, j;
    cin >> N >> i >> j;
    cout << getAnswer(N, i, j) << " " << getAnswer(N, N - i + 1, N - j + 1) << endl;
    return 0;
}