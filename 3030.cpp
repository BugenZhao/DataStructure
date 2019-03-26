//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

class MushRoom {
public:
    int t;
    int v;
};

int main() {
    MushRoom ms[105];
    int T, M;
    cin >> T >> M;
    int a, b;
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d", &ms[i].t, &ms[i].v);
    }
    int values[1005]{};
    for (int i = 1; i <= M; ++i) {
        for (int j = T; j >= ms[i].t; --j) {
            values[j] = max(values[j], values[j - ms[i].t] + ms[i].v);
        }
    }

    cout << values[T] << endl;
    return 0;
}