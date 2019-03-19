//
// Created by BugenZhao on 2019/3/17.
//
// 辗转相除

#include <iostream>
#include <algorithm>

using namespace std;

static const auto _____ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

using ll=long long;

ll get(ll a, ll b) {
    if (b == 0)
        return 0;
    ll adb = a / b;
    ll adbmb = adb * b;
    return 4 * adb * b + get(b, a - adbmb);
}

int main() {
    ll a, b;
    cin >> a >> b;
    if (a < b) swap(a, b);
    cout << get(a, b);
    return 0;
}