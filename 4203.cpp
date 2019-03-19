//
// Created by BugenZhao on 2019/3/17.
//
// TLE

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;


using ll=long long;

constexpr int maxN = 100000 + 5;

constexpr ll p = 1e9 + 7;
ll fac[maxN] = {1, 1};
ll f[maxN] = {1, 1};
ll inv[maxN] = {1, 1};

ll pow(ll x, ll y) {
    if (y == 0) return 1;
    ll z = pow(x, y / 2) % p;
    if (y % 2 == 0) return z * z % p;
    else return z * z % p * x % p;
}

ll c(int n, int m) {
    if (n == m || m == 0) return 1;
    return fac[n] * inv[m] % p * inv[n - m] % p;
}

int main() {
    for (int i = 2; i < 100000 + 5; ++i) {
        fac[i] = fac[i - 1] * i % p;
        f[i] = (p - p / i) * f[p % i] % p;
        inv[i] = inv[i - 1] * f[i] % p;
    }

    int T;
    int n, m;

    cin >> T;
    while (T--) {
        scanf("%d%d", &n, &m);
        printf("%d\n", c(n, m));
    }
}