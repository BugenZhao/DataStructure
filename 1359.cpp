//
// Created by BugenZhao on 2019/3/16.
//

#include <iostream>
#include <cctype>

using namespace std;

int main() {
    string str;
    getline(cin, str);
    long long ans = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') continue;
        if (isupper(str[i]))
            ans += (str[i] - 'A' + 1) * (i + 1);
        else if (islower(str[i]))
            ans += (str[i] - 'a' + 27) * (i + 1);
    }
    cout << ans << endl;
}
