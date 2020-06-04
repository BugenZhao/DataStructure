//
// Created by BugenZhao on 2019/3/17.
//
// 排序

#include <iostream>
#include <algorithm>

using namespace std;

using ll=long long;

int currentID = 0;

class Mouse {
public:
    int id;
    int power = 0;
    int score = 0;

    bool operator<(const Mouse &rhs) const {
        if (score > rhs.score)
            return true;
        if (rhs.score > score)
            return false;
        return id < rhs.id;
    }

    Mouse() { id = ++currentID; }
};

int main() {
    int N, R;
    cin >> N >> R;
    auto mice = new Mouse[2 * N]{};
    int tmp;
    for (int i = 0; i < 2 * N; ++i) {
        scanf("%d", &mice[i].score);
    }
    for (int i = 0; i < 2 * N; ++i) {
        scanf("%d", &mice[i].power);
    }
    while (R--) {
        sort(mice, mice + 2 * N);
        for (int i = 0; i < N; ++i) {
            Mouse *a = mice + 2 * i;
            Mouse *b = mice + 2 * i + 1;
            if (a->power < b->power) {
                b->score += 2;
            } else if (a->power > b->power) {
                a->score += 2;
            } else {
                a->score += 1;
                b->score += 1;
            }
        }
    }
    sort(mice, mice + 2 * N);
    for (int j = 0; j < 2 * N; ++j) {
        printf("%d ", mice[j].id);
    }
    return 0;
}
