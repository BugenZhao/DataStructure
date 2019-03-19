//
// Created by BugenZhao on 2019/3/18.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

static const auto _____ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

using ll=long long;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> mods(m + 1);
        mods[0] = 1;
        int currentMod = 0;
        for (int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            currentMod = (currentMod + tmp) % m;
            ++mods[currentMod];
        }

        int ans = 0;
        for (int mod:mods) {
            if (mod <= 1) continue;
            else ans += mod * (mod - 1) / 2;
        }
        cout << ans << endl;
    }
    return 0;
}