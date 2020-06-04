//
// Created by BugenZhao on 2019/5/16.
//

#ifndef SBL_BMERGESORT_H
#define SBL_BMERGESORT_H

template<typename Item>
class BMergeSort {
public:
    static long long ans;

private:
    static bool less(Item v, Item w) {
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
                // caution: <=
            else if (!less(aux[j], aux[i])) a[k] = aux[i++];
            else a[k] = aux[j++], ans += mid - i + 1;
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
long long BMergeSort<Item>::ans = 0;

#endif //SBL_BMERGESORT_H

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    cin >> k;
    auto a = new int[k];
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    BMergeSort<int>::sort(a, k);
    cout << BMergeSort<int>::ans << endl;
    delete[] a;
    return 0;
}