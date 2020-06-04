//
// Created by BugenZhao on 2019/3/18.
//
// 全排列

#include <iostream>
#include <algorithm>

using namespace std;

static const auto _____ = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

template<typename _BidirectionalIterator, typename _Compare>
bool
aVeryStrangeFunction(_BidirectionalIterator __first,
                     _BidirectionalIterator __last, _Compare __comp) {
    if (__first == __last)
        return false;
    _BidirectionalIterator __i = __first;
    ++__i;
    if (__i == __last)
        return false;
    __i = __last;
    --__i;

    for (;;) {
        _BidirectionalIterator __ii = __i;
        --__i;
        if (__comp(__i, __ii)) {
            _BidirectionalIterator __j = __last;
            while (!__comp(__i, --__j)) {}
            std::iter_swap(__i, __j);
            std::__reverse(__ii, __last,
                           std::__iterator_category(__first));
            return true;
        }
        if (__i == __first) {
            std::__reverse(__first, __last,
                           std::__iterator_category(__first));
            return false;
        }
    }
}

int main() {
    int M;
    cin >> M;
    while (M--) {
        int n, k;
        cin >> n >> k;
        auto array = new int[n];
        for (int i = 0; i < n; ++i) {
            cin >> array[i];
        }
        while (k--) {
            aVeryStrangeFunction(array, array + n, __gnu_cxx::__ops::__iter_less_iter());
        }
        for (int j = 0; j < n; ++j) {
            cout << array[j] << ' ';
        }
        cout << endl;
        delete[] array;
    }
    return 0;
}