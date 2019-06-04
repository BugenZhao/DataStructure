//
// Created by BugenZhao on 2019/5/16.
//

//
// Created by BugenZhao on 2019/4/5.
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
    int minN;

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
        if (newMaxN < minN) {
            if (maxN == minN) return;
            else newMaxN = minN;
        }
        Item *old = pq;
        pq = new Item[newMaxN + 1];
        int length = newMaxN > maxN ? maxN : newMaxN;
        for (int i = 1; i <= length; ++i) {
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
            if (cmp(j, k)) {
                exch(k, j);
                k = j;
            } else break;
        }
    }


public:
    BPriorityQueue() {
        this->maxN = 5;
        this->minN = 5;
        pq = new Item[5 + 1];
    }

    BPriorityQueue(int maxN) {
        this->maxN = maxN;
        this->minN = maxN;
        pq = new Item[maxN + 1];
    }

    BPriorityQueue(const Item *pq, int size) {
        maxN = N = size;
        minN = N;
        this->pq = new Item[size + 1];
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
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;

class Point {
public:
    int x, y, h;

    Point(int x = 0, int y = 0, int h = 0) : x(x), y(y), h(h) {}
};

struct cmp {
    bool operator()(const Point &a, const Point &b) {
        return a.h < b.h;
    }
};

int height[100][100];
bool flag[100][100];
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c;
    cin >> r >> c;
    if (r < 3 || c < 3) {
        cout << 0 << endl;
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> height[i][j];
        }
    }

    BPriorityQueue<Point, cmp> pq(r * c);
    for (int i = 0; i < r; ++i) {
        pq.insert(Point(i, 0, height[i][0]));
        flag[i][0] = true;
        pq.insert(Point(i, c - 1, height[i][c - 1]));
        flag[i][c - 1] = true;
    }
    for (int j = 1; j < c - 1; ++j) {
        pq.insert(Point(0, j, height[0][j]));
        flag[0][j] = true;
        pq.insert(Point(r - 1, j, height[r - 1][j]));
        flag[r - 1][j] = true;
    }

    while (!pq.isEmpty()) {
        Point point = pq.pop();
        for (int i = 0; i < 4; ++i) {
            int xx = point.x + dx[i];
            int yy = point.y + dy[i];
            if (xx < 0 || xx >= r || yy < 0 || yy >= c || flag[xx][yy]) continue;
            if (point.h > height[xx][yy]) {
                ans += point.h - height[xx][yy];
                height[xx][yy] = point.h;
            }
            pq.insert(Point(xx, yy, height[xx][yy]));
            flag[xx][yy] = true;
        }
    }

    cout << ans << endl;
    return 0;
}