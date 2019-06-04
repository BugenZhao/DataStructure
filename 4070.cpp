//
// Created by BugenZhao on 2019/5/29.
//

//
// Created by BugenZhao on 2019/5/12.
//

#ifndef SBL_BQSORT_H
#define SBL_BQSORT_H

#ifndef SBL_BSORT_H
#define SBL_BSORT_H

namespace bsort {
    template<typename Item>
    struct greater {
        bool operator()(const Item &a, const Item &b) {
            return a > b;
        }
    };

    template<typename Item>
    struct less {
        bool operator()(const Item &a, const Item &b) {
            return a < b;
        }
    };
}

#endif //SBL_BSORT_H


template<typename Item, typename Comparator=bsort::less<Item>>
class BQSort {
    static Comparator comparator;

private:
    static bool less(Item v, Item w) {
        return comparator(v, w);
    }

    static void exch(Item *a, int i, int j) {
        Item t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

public:
    static inline void sort(Item *a, int n) {
        sort(a, 0, n - 1);
    }

    static inline void sort(Item *a, int lo, int hi) {
        if (hi <= lo) return;
        int mid = partition(a, lo, hi);
        sort(a, lo, mid - 1);
        sort(a, mid + 1, hi);
    }

    static int partition(Item *a, int lo, int hi) {
        Item v = a[lo];
        while (true) {
            while (lo < hi && less(v, a[hi])) --hi;
            if (lo < hi) a[lo] = a[hi], ++lo;
            while (lo < hi && less(a[lo], v)) ++lo;
            if (lo < hi) a[hi] = a[lo], --hi;
            if (lo >= hi) break;
        }
        a[lo] = v;
        return lo;
    }
};

template<typename Item, typename Comparator>
Comparator BQSort<Item, Comparator>::comparator = Comparator();

#endif //SBL_BQSORT_H


#include <iostream>
#include <cstring>

using std::ios, std::cin, std::cout, std::endl;
using ll = long long;

struct cmp {
    bool operator()(char *a, char *b) {
        return strcmp(a, b) > 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char **strs = new char *[35];
    for (int i = 0; i < 35; ++i) {
        strs[i] = new char[35];
    }
    char tmp[35];
    char ch;
    cin >> ch;
    int i = 0;
    for (i = 0; i < 35; ++i) {
        cin >> tmp;
        if (tmp[0] == '@') break;
        int len = strlen(tmp);
        int q = 0;
        for (int p = 0; p <= len; ++p) {
            if (tmp[p] == ch) continue;
            strs[i][q++] = tmp[p];
        }
    }
    BQSort<char *, cmp>::sort(strs, i);
    for (int j = 0; j < i; ++j) {
        cout << strs[j];
        if (j != i - 1) cout << '\n';
    }
    return 0;
}