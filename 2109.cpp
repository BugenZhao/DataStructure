//
// Created by BugenZhao on 2019/3/17.
//

#include <iostream>

using namespace std;

static const auto _____ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

int main() {
    int N;
    cin >> N;
    auto a = new int[N];
    int tmp;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        a[i] = (-4) * tmp;
    }
    int K;
    cin >> K;
    int b, c;
    for (int j = 0; j < K; ++j) {
        cin >> b >> c;
        int count = 0;
        int b2 = b * b;
        for (int i = 0; i < N; ++i) {
            if (b2 + a[i] * c >= 0) {
                ++count;
            } else {
                break;
            }
        }
        cout << count << endl;
    }
    delete[] a;
    return 0;
}
