//
// Created by BugenZhao on 2019/3/23.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using ll=long long;

bool notPrime[] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0,
                  1, 0, 0, 0, 0, 0, 1, 0, 1};

int nums[20];
bool vis[20];
bool flag;
int N;

void search(int current) {
    if (current == N) {
        if (notPrime[nums[0] + nums[N - 1]]) {
            for (int i = 0; i < N; ++i) {
                printf("%d ", nums[i]);
            }
            printf("\n");
            flag = true;
        }
    } else {
        for (int i = 2; i <= N; ++i) {
            if (!vis[i] && notPrime[i + nums[current - 1]]) {
                nums[current] = i;
                vis[i] = true;
                search(current + 1);
                vis[i] = false;
            }
        }
    }
}

int main() {
    cin >> N;
    if (N % 2 == 1) {
        printf("None\n");
        return 0;
    }

    for (int i = 1; i <= N; ++i) {
        nums[i - 1] = i;
    }

    search(1);
    if (!flag) {
        printf("None\n");
    }

    return 0;
}