//
// Created by BugenZhao on 2019/5/18.
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
        Item *newpq = new Item[newMaxN + 1];
        int length = newMaxN > maxN ? maxN : newMaxN;
        for (int i = 1; i <= length; ++i) {
            newpq[i] = pq[i];
        }
        delete[] pq;
        pq = newpq;
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

constexpr int INF = 0x7fffffff;


template<typename Weight>
class Edge {
private:
    int v;
    int w;
    Weight weight;
public:
    Edge(int v = 0, int w = 0, const Weight &weight = Weight()) :
            v(v), w(w), weight(weight) {}

    const Weight &getWeight() const {
        return weight;
    }

    void setWeight(const Weight &weight) {
        Edge::weight = weight;
    }

    int either() const {
        return v;
    }

    int other(int p) const {
        if (p == v) return w;
        if (p == w) return v;
        throw "Edge: other";
    }

    bool operator<(const Edge &rhs) const {
        return weight < rhs.weight;
    }
};

int height[26][26];
int V;


int lazyPrim() {
    BPriorityQueue<Edge<int>, bpq::less<Edge<int>>> pq(V * V);
    bool *marked = new bool[V]{};
    int ans = 0;

    auto visit = [&](int v) {
        marked[v] = true;
        for (int w = 0; w < V; ++w) {
            if (w == v || height[v][w] == INF) continue;
            pq.insert(Edge(v, w, height[v][w]));
        }
    };

    visit(0);
    while (!pq.isEmpty()) {
        Edge e = pq.pop();
        int v = e.either(), w = e.other(v);
        if (marked[v] && marked[w]) continue;
        ans += e.getWeight();
        if (!marked[v]) visit(v);
        if (!marked[w]) visit(w);
    }

    delete[] marked;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> V;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j)
                height[i][j] = height[j][i] = INF;
        }
    }
    for (int v = 0; v < V - 1; ++v) {
        char tc;
        int count, tmp;
        cin >> tc;
        cin >> count;
        for (int i = 0; i < count; ++i) {
            cin >> tc >> tmp;
            height[v][tc - 'A'] = height[tc - 'A'][v] = tmp;
        }
    }

    cout << lazyPrim() << endl;
    return 0;
}