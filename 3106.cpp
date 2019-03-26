//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using ll=long long;

int main() {
    int N;
    cin >> N;
    int nums[10005];
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &nums[i]);
        sum += nums[i];
    }
    int avg = sum / N;
    int ans = 0;
    for (int j = 0; j < N; ++j) {
        if (nums[j] != avg) {
            nums[j + 1] = nums[j + 1] + nums[j] - avg;
            ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}
