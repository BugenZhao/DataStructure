//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

/*class Interval {
public :
    int l;
    int r;

    bool operator<(const Interval &rhs) const {
        if (l < rhs.l)
            return true;
        if (rhs.l < l)
            return false;
        return r < rhs.r;
    }
};*/

int main() {
    int starts[10005], ends[10005];
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &starts[i], &ends[i]);
    }

    sort(starts, starts + n);
    sort(ends, ends + n);

    int length = 0;
    int i = 0, j = 0;
    for (; i < n; ++i) {
        if (i == n - 1 || starts[i + 1] > ends[i]) {
            length += ends[i] - starts[j];
            j = i + 1;
        }
    }
    cout << length << endl;
    return 0;
}