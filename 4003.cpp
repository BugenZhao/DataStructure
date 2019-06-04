//
// Created by BugenZhao on 2019/5/16.
//

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned n, k;
    cin >> n >> k;

    if (n <= k) {
        cout << k - n << endl;
        return 0;
    }

    unsigned count = 0;
    for (unsigned j = 0; j < 32; ++j) {
        if (n & (1U << j)) ++count;
    }

    unsigned ori = n;

    for (unsigned i = 0; i < 32 && count > k; ++i) {
        if (n & (1U << i)) n += 1U << i;
        count = 0;
        for (unsigned j = 0; j < 32; ++j) {
            if (n & (1U << j)) ++count;
        }
    }

    cout << n - ori << endl;
    return 0;
}