//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

ll tmpe[20] = {0, 1};
ll *e = tmpe + 1;

int getLength(ll num) {
    int ans = 1;
    while (num /= 10) {
        ++ans;
    }
    return ans;
}

int getFront(ll num) {
    while (true) {
        if (num <= 9) break;
        num /= 10;
    }
    return (int) num;
}

int main() {
    for (int i = 1; i < 19; ++i) {
        e[i] = e[i - 1] * 10;
    }
    ll l, r;
    cin >> l >> r;
    ll ans = 0;

    int lLength = getLength(l), rLength = getLength(r);
    int lFront = getFront(l), rFront = getFront(r);

    if (lLength == rLength) {
        ll N = e[lLength - 1] * lFront + 9 * e[lLength - 2] + lFront;
        ll n = e[lLength - 1] * rFront + rFront;
        if (lFront == rFront) {
            if (l <= n) {
                if (r < n) ans += 0;
                else ans += (r - n) / 10 + 1;
            } else {
                if (r < n) ans += (r - l) / 10;
                else ans += (n - l) / 10;
            }
        } else {
            ans += (N - l > 0) ? (N - l) / 10 : 0;
            ans += (l - n > 0) ? (l - n) / 10 : 0;
            ans += (rFront - lFront - 1) * (lLength == 1 ? 1 : e[lLength - 2]);
        }
        cout << ans << endl;
        return 0;
    }
    for (int i = lLength + 1; i < rLength; ++i) {
        ans += 9 * e[i - 2];
    }


    for (int i = lFront; i < 10; ++i) {
        if (i != lFront) {
            ans += e[lLength - 2];
            continue;
        }
        ll N = e[lLength - 1] * i + 9 * e[lLength - 2] + i;
        ll tmp = N - l;
        ans += (tmp > 0) ? tmp / 10 : 0;
    }

    for (int i = 1; i <= rFront; ++i) {
        if (i != rFront) {
            ans += e[lLength - 2];
            continue;
        }
        ll n = e[lLength - 1] * i + i;
        ll tmp = l - n;
        ans += (tmp > 0) ? tmp / 10 : 0;
    }

    cout << ans << endl;
    return 0;
}