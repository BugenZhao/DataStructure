//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

int main() {
    char s[105], t[105];
    cin.getline(s, 103);
    cin.getline(t, 103);
    int l = strlen(s);
    int a;
    for (a = 2; a <= l; ++a) {
        if (l % a != 0) continue;
        char tmp[105];
        int count = 0;
        bool flag = true;
        for (int i = 0; i < a; ++i) {
            for (int j = i; j < l; j += a) {
                tmp[count++] = s[j];
                if (tmp[count - 1] != t[count - 1])
                    flag = false;
                if (!flag) break;
            }
            if (!flag) break;
        }
        if (flag) {
            cout << a << endl;
            return 0;
        }
    }
    if (a == l + 1) {
        cout << "No Solution" << endl;
    }
    return 0;
}