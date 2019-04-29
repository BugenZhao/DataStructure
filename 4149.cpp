//
// Created by BugenZhao on 2019/4/10.
//

#include <iostream>

using namespace std;

using ll=long long;

int main() {
    ll n, m, k;
    cin >> n >> m >> k;
    auto out = new bool[n]{};
    ll cur = -1;
    while (k--) {
        ll mm = m;
        while (mm) {
            cur = (cur + 1) % n;
            while (out[cur]) {
                cur = (cur + 1) % n;
            }
            --mm;
        }
        out[cur] = true;
    }
    cout << cur + 1 << endl;
    return 0;
}
