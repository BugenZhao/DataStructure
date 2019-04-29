//
// Created by BugenZhao on 2019/4/14.
//


#ifndef SBL_BPRIORITYQUEUE_H
#define SBL_BPRIORITYQUEUE_H

namespace bpq {
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


template<typename Item, typename Comparator = bpq::greater<Item>>
class BPriorityQueue {
    Comparator comparator;
    Item *pq;
    int N = 0;
    int maxN;

private:
    bool cmp(int i, int j) {
        return comparator(pq[i], pq[j]);
    }

    void exch(int i, int j) {
        Item item = pq[i];
        pq[i] = pq[j];
        pq[j] = item;
    }

    void resize(int newMaxN) {
        Item *old = pq;
        pq = new Item[newMaxN + 1];
        int length = newMaxN > maxN ? maxN : newMaxN;
        for (int i = 0; i < length; ++i) {
            pq[i] = old[i];
        }
        delete[] old;
    }

    void swim(int k) {
        while (k > 1 && cmp(k, k / 2)) {
            exch(k / 2, k);
            k /= 2;
        }
    }

    void sink(int k) {
        int j;
        while (2 * k <= N) {
            j = 2 * k;
            j += (j < N && cmp(j + 1, j));
            if (cmp(k, j)) break;
            else {
                exch(k, j);
                k = j;
            }
        }
    }


public:
    BPriorityQueue() {
        BPriorityQueue(1);
    }

    BPriorityQueue(int maxN) : maxN(maxN) {
        pq = new Item[maxN + 1];
    }

    BPriorityQueue(const Item *pq, int size) {
        maxN = N = size;
        this->pq = new Item[size];
        for (int i = 1; i <= N; ++i) {
            this->pq[i] = pq[i - 1];
        }
        for (int k = N / 2; k >= 1; --k) {
            sink(k);
        }
    }

    bool isEmpty() {
        return N == 0;
    }

    int size() {
        return N;
    }

    void insert(const Item &item) {
        if (N == maxN)
            resize(2 * N);
        pq[++N] = item;
        swim(N);
    }

    Item pop() {
        if (N <= maxN / 4)
            resize(maxN / 2);
        Item item = pq[1];
        exch(1, N);
        --N;
        sink(1);
        return item;
    }

    const Item &peek() {
        return pq[1];
    }

    virtual ~BPriorityQueue() {
        delete[] pq;
    }
};


#endif //SBL_BPRIORITYQUEUE_H

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N;
    cin >> N;
    BPriorityQueue<int, bpq::less<int>> pq(N);
    char cmd[10];
    int tmp;
    while (N--) {
        cin >> cmd;
        switch (cmd[0]) {
            case 'i':
                cin >> tmp;
                pq.insert(tmp);
                break;
            case 'd':
                pq.pop();
                break;
            case 'm':
                cout << pq.peek() << '\n';
                break;
        }
    }
    cout << endl;
    return 0;
}