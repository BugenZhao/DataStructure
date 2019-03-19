//
// Created by BugenZhao on 2019/3/18.
//

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;
using ll=long long;

constexpr int p = 1000000007;

static const auto _____ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

ll pow(ll x, ll y) {
    if (y == 0) return 1;
    ll z = pow(x, y / 2) % p;
    if (y % 2 == 0) return z * z % p;
    else return z * z % p * x % p;
}

ll answers[1005] = {0, 1, 2, 2};

ll getAnswer(int n) {
    if (answers[n] != 0)
        return answers[n];
    ll ans = 1;
    if (n % 2 == 0) {
        ans += getAnswer(n / 2);
        for (int i = 2; i < n; i += 2) {
            ans += getAnswer((n - i) / 2);
        }
    } else {
        for (int i = 1; i < n; i += 2) {
            ans += getAnswer((n - i) / 2);
        }
    }
    answers[n] = ans % p;
    return ans % p;
}

int main() {
    int tmp;
    cin >> tmp;
    cout << getAnswer(tmp) << endl;
}