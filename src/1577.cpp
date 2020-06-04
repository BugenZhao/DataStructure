//
// Created by BugenZhao on 2019/3/16.
//
// 环装字符串匹配

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    string src;
    string srcReverse;
    string tmp;
    int size;
    int count = 0;
    cin >> n;
    cin >> src;
    src = src.substr(1, src.size() - 2);
    size = src.size();
    src += src;
    srcReverse = src;
    reverse(srcReverse.begin(), srcReverse.end());

    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        tmp = tmp.substr(1, tmp.size() - 2);
        if (tmp.size() != size) continue;
        if (src.find(tmp) != string::npos || srcReverse.find(tmp) != string::npos)
            ++count;
    }
    cout << count << endl;
}
