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

class Period {
public:
    int a;
    int b;

    bool operator<(const Period &rhs) const {
        if (b < rhs.b)
            return true;
        if (rhs.b < b)
            return false;
        return a < rhs.a;
    }
};

int main() {
    int n;
    cin >> n;
    auto periods = new Period[n];
    for (int i = 0; i < n; ++i) {
        cin >> periods[i].a;
        cin >> periods[i].b;
    }
    sort(periods, periods + n);

    int current = periods[0].b;
    int count = 1;
    for (int j = 1; j < n; ++j) {
        if (periods[j].a >= current) {
            ++count;
            current = periods[j].b;
        }
    }
    cout << count << endl;
    delete[] periods;
    return 0;
}
