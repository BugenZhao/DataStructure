//
// Created by BugenZhao on 2019/5/19.
//

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    int *id = new int[n];
    int *sz = new int[n];
    int count = n;
    for (int i = 0; i < n; ++i) {
        id[i] = i, sz[i] = 1;
    }

    auto find = [&](int p) {
        while (p != id[p]) p = id[p];
        return p;
    };

    auto uni = [&](int p, int q) {
        int pr = find(p);
        int qr = find(q);
        if (pr == qr) return;
        if (sz[pr] < sz[qr]) {
            id[pr] = qr;
            sz[qr] += sz[pr];
        } else {
            id[qr] = pr;
            sz[pr] += sz[qr];
        }
        --count;
    };

    while (m--) {
        int k, root, tmp;
        cin >> k >> root;
        for (int i = 0; i < k - 1; ++i) {
            cin >> tmp;
            uni(tmp, root);
        }
    }

    int id0 = find(0);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (find(i) == id0) ++ans;
    }

    cout << ans << endl;
    delete[] id;
    delete[] sz;
    return 0;
}