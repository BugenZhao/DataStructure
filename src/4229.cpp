//
// Created by BugenZhao on 2019/4/29.
//

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    auto counts = new int[N + 1]{};
    int maxPos = 0;
    int maxCount = 0;

    string cmd;
    int a, b;
    while (true) {
        cin >> cmd;
        if (cmd[0] == 'f') break;
        else if (cmd[0] == 'a') {
            cin >> a >> b;
            ++counts[b];
            if (counts[b] == maxCount) {
                maxPos = maxPos < b ? maxPos : b;
            } else if (counts[b] == maxCount + 1) {
                maxCount += 1;
                maxPos = b;
            }
        } else if (cmd[0] == 'q') {
            cout << maxPos << ' ' << maxCount << '\n';
        }
    }

    delete[] counts;
    return 0;
}