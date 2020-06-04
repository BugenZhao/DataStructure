//
// Created by BugenZhao on 2019/3/18.
//
// 以最高处二分

#include <iostream>
#include <vector>

using namespace std;

static const auto _____ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

int trap(vector<int> &height) {
    int max_height = 0, max_index = 0, ans = 0;
    for (int i = 0; i != height.size(); ++i)
        if (height[i] > max_height)
            max_height = height[i], max_index = i;
    max_height = 0;
    for (int i = 0; i < max_index; ++i)
        if (max_height > height[i])
            ans += max_height - height[i];
        else
            max_height = height[i];
    max_height = 0;
    for (int i = height.size() - 1; i > max_index; --i)
        if (max_height > height[i])
            ans += max_height - height[i];
        else
            max_height = height[i];
    return ans;
}

int main() {
    int N;
    cin >> N;
    vector<int> height(N);
    char tmp;
    cin >> tmp;
    for (int i = 0; i < N; ++i) {
        cin >> height[i];
        cin >> tmp;
    }
    cout << trap(height) << endl;
    return 0;
}