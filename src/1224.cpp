//
// Created by BugenZhao on 2019/5/29.
//

//
// Created by BugenZhao on 2019/5/29.
//

#ifndef SBL_BSEPARATECHAININGHASHST_H
#define SBL_BSEPARATECHAININGHASHST_H


template<typename Key, typename Value, typename Hasher>
class BSeparateChainingHashST {
    static constexpr int INIT_CAPACITY = 4;

    class Pair {
    public:
        Key key;
        Value value;
    };

    class Node {
    public:
        Pair pair;
        Node *next;

        Node(const Pair &pair, Node *next = nullptr) : pair(pair), next(next) {}

        Node() : next(nullptr) {}
    };

    int n;
    int m;
    Hasher hasher;
    Node **st;

private:
    int hash(const Key &key) {
return (hasher(key) & 0x7fffffff) % m;
    }

public:
    BSeparateChainingHashST() : BSeparateChainingHashST(INIT_CAPACITY) {}

    BSeparateChainingHashST(int m) : m(m) {
        n = 0;
        st = new Node *[m]{};
    }

    virtual ~BSeparateChainingHashST() {
        for (int i = 0; i < m; ++i) {
            Node *p = st[i];
            Node *q;
            while (p) {
                q = p->next;
                delete p;
                p = q;
            }
        }
        delete[] st;
    }

    int size() {
        return n;
    }

    bool isEmpty() {
        return size() == 0;
    }

    bool contains(const Key &key) {
        return get(key) != nullptr;
    }

    Pair *get(const Key &key) {
        int i = hash(key);
        Node *p = st[i];
        while (p) {
            if (p->pair.key == key) return &(p->pair);
            p = p->next;
        }
        return nullptr;
    }

    void put(const Key &key, const Value &val) {
//        if (n >= 10 * m) resize(2 * m);

        int i = hash(key);
        Node *p = st[i];
        while (p) {
            if (p->pair.key == key) {
                p->pair.value = val;
                return;
            }
            p = p->next;
        }
        ++n;
        st[i] = new Node(Pair{key, val}, st[i]);
    }

    void increment(const Key &key) {
        int i = hash(key);
        Node *p = st[i];
        while (p) {
            if (p->pair.key == key) {
                ++p->pair.value;
                return;
            }
            p = p->next;
        }
        ++n;
        st[i] = new Node(Pair{key, 1}, st[i]);
    }

    void remove(const Key &key) {
        int i = hash(key);
        Node *p = st[i];

        if (st[i] == nullptr) return;

        if (st[i]->pair.key == key) {
            st[i] = st[i]->next;
            delete p;
            --n;
        } else {
            while (p->next) {
                if (p->next->pair.key == key) {
                    auto q = p->next;
                    p->next = q->next;
                    delete q;
                    --n;
                    break;
                }
                p = p->next;
            }
        }
    }

};

#endif //SBL_BSEPARATECHAININGHASHST_H


#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll = long long;

struct hasher {
    inline int operator()(int i) {
        return i + 2000000;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    auto a = new int[n];
    auto b = new int[n];
    auto c = new int[n];
    auto d = new int[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", a + i, b + i, c + i, d + i);
    }
    BSeparateChainingHashST<int, int, hasher> st(4000001);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            st.increment(a[i] + b[j]);
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            auto p = st.get(-c[i] - d[j]);
            if (p) ans += p->value;
        }
    }

    printf("%ld", ans);
    return 0;
}