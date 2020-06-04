//
// Created by BugenZhao on 2019/5/12.
//

#ifndef SBL_BQSORT_H
#define SBL_BQSORT_H

template<typename Item>
class BQSort {
private:
    static bool less(Item v, Item w) {
        return v < w;
    }

    static void exch(Item *a, int i, int j) {
        Item t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

public:
    static void sort(Item *a, int n) {
        sort(a, 0, n - 1);
    }

    static void sort(Item *a, int lo, int hi) {
        if (hi <= lo) return;
        int mid = partition(a, lo, hi);
        sort(a, lo, mid - 1);
        sort(a, mid + 1, hi);
    }

    static int partition(Item *a, int lo, int hi) {
        int i = lo, j = hi + 1;
        Item v = a[lo];
        while (true) {
            while (less(a[++i], v))
                if (i == hi) break;
            while (less(v, a[--j]))
                if (j == lo) break;
            if (i >= j) break;
            exch(a, i, j);
        }
        exch(a, lo, j);
        return j;
    }
};

#endif //SBL_BQSORT_H

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    auto a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    BQSort<int>::sort(a, n);

    int index = 1;
    int last = a[0];
    int ans = 1;
    for (; index < n; ++index) {
        if (a[index] != last) {
            ++ans;
            last = a[index];
        }
    }
    cout << ans << endl;
    delete[] a;
    return 0;
}