//
// Created by BugenZhao on 2019/3/18.
//

#include <iostream>
#include <algorithm>

using namespace std;

static const auto _____ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

using ll=long long;

int main() {
    int q;
    cin >> q;
    while (q--) {
        ll v, a, b;
        cin >> v >> a >> b;
        ll ans = 0;
        if (a * 2 <= b) {
            ans = v * a;
        } else {
            if (v % 2 == 0) {
                ans = v / 2 * b;
            } else {
                ans = v / 2 * b + a;
            }
        }
        cout << ans << endl;
    }
    return 0;
}