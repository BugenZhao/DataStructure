//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <list>

using namespace std;

using ll=long long;
using Pair=pair<int, int>;

int main() {
    priority_queue<Pair> q;
    int N, K;
    cin >> N >> K;
    int values[400005];
    for (int i = 0; i < N; ++i) {
        scanf("%d", values + i);
    }
    for (int l = 0; l < K; ++l) {
        values[N + l] = values[l];
    }
    for (int j = 0; j < K; ++j) {
        q.push(Pair(values[j], j));
    }
    int maxAns = q.top().first;
    Pair tmp;
    for (int k = K; k < N + K; ++k) {
        q.push(Pair(values[k], k));
        tmp = q.top();
        while (tmp.second < k - (K - 1)) {
            q.pop();
            tmp = q.top();
        }
        maxAns = min(maxAns, q.top().first);
    }
    cout << maxAns << endl;
    return 0;
}