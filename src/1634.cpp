//
// Created by BugenZhao on 2019/5/16.
//

//
// Created by BugenZhao on 2019/5/12.
//
//
// Created by BugenZhao on 2019/5/12.
//
//
// Created by BugenZhao on 2019/5/12.
//

#ifndef SBL_BQSORT_H
#define SBL_BQSORT_H

int count = 0;

template<typename Item>
class BQSort {
public:
    static int count;

private:
    static bool less(Item v, Item w) {
        ++count;
        return v < w;
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

template<typename Item>
int BQSort<Item>::count = 0;

#endif //SBL_BQSORT_H


//
// Created by BugenZhao on 2019/5/16.
//

#ifndef SBL_BMINHEAPSORT_H
#define SBL_BMINHEAPSORT_H

template<typename Item>
class BMinHeapSort {
public:
    static int count;

private:
    static bool less(Item v, Item w) {
        ++count;
        return v < w;
    }

    static void exch(Item *a, int i, int j) {
        Item t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    static void sink(Item *a, int k, int N) {
        while (2 * k + 1 <= N) {
            int j = 2 * k + 1;
            if (j < N && less(a[j + 1], a[j])) ++j;
            if (less(a[k], a[j])) break;
            exch(a, k, j);
            k = j;
        }
    }

    static void swim(Item *a, int k) {
        int tmp;
        while (k && less(a[k], a[tmp = (k - 1) / 2])) {
            exch(a, k, tmp);
            k = tmp;
        }
    }

public:
    static void sort(Item *a, int n) {
        auto aux = new Item[n];
        for (int i = 0; i < n; ++i) {
            aux[i] = a[i];
        }
        int N = n - 1;
        for (int k = 1; k < n; ++k) {
            swim(aux, k);
        }
        for (int i = 0; i < n; ++i) {
            a[i] = aux[0];
            exch(aux, 0, N--);
            sink(aux, 0, N);
        }
        delete[] aux;
    }

    static void sort(Item *a, int lo, int hi) {
        Item *newa = a + lo;
        sort(newa, hi - lo + 1);
    }
};

template<typename Item>
int BMinHeapSort<Item>::count = 0;

#endif //SBL_BMINHEAPSORT_H
//
// Created by BugenZhao on 2019/5/16.
//

#ifndef SBL_BMERGESORT_H
#define SBL_BMERGESORT_H

template<typename Item>
class BMergeSort {
public:
    static int count;

private:
    static bool less(Item v, Item w) {
        ++count;
        return v < w;
    }

    static void doSort(Item *a, int lo, int hi, Item *aux) {
        if (hi <= lo) return;
        int mid = lo + (hi - lo - 1) / 2;
        doSort(a, lo, mid, aux);
        doSort(a, mid + 1, hi, aux);
        merge(a, lo, mid, hi, aux);
    }

    static void merge(Item *a, int lo, int mid, int hi, Item *aux) {
        for (int i = lo; i <= hi; i++) {
            aux[i] = a[i];
        }
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) a[k] = aux[j++];
            else if (j > hi) a[k] = aux[i++];
            else if (less(aux[i], aux[j])) a[k] = aux[i++];
            else a[k] = aux[j++];
        }
    }

public:
    static void sort(Item *a, int n) {
        sort(a, 0, n - 1);
    }

    static void sort(Item *a, int lo, int hi) {
        Item *aux = new Item[hi - lo + 1];
        doSort(a, lo, hi, aux);
        delete[] aux;
    }
};

template<typename Item>
int BMergeSort<Item>::count = 0;

#endif //SBL_BMERGESORT_H

#include <cstdio>
#include <string>

using std::ios, std::string;
using ll = long long;

int main() {
    int n, sel;
    scanf("%d%d", &n, &sel);
    auto a = new int[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    int count = 0;
    switch (sel) {
        case 1:
            BMinHeapSort<int>::sort(a, n);
            count = BMinHeapSort<int>::count;
            break;
        case 2:
            BMergeSort<int>::sort(a, n);
            count = BMergeSort<int>::count;
            break;
        case 3:
            BQSort<int>::sort(a, n);
            count = BQSort<int>::count;
            break;
    }
    printf("%d\n", count);
    delete[] a;
    return 0;
}