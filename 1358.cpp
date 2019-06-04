//
// Created by BugenZhao on 2019/5/8.
//

#ifndef SBL_BLINKEDLIST_H
#define SBL_BLINKEDLIST_H

#include <stdexcept>

template<typename Item>
class BLinkedList {
    class Node {
    public:
        Item item;
        Node *next;

        explicit Node(const Item &item, Node *next = nullptr) : item(item), next(next) {}

        explicit Node(Node *next = nullptr) : next(next) {}

        virtual ~Node() = default;
    };

    int N;
    Node *head;
    Node *tail;

    Node *getNode(int i) {
        Node *ret = head->next;
        while (i--) {
            ret = ret->next;
        }
        return ret;
    }

public:
    BLinkedList() {
        N = 0;
        head = new Node;
        tail = head;
    }

    BLinkedList(const BLinkedList &other) {
        N = 0;
        head = new Node;
        tail = head;
        auto p = other.head->next;
        while (p) {
            addLast(p->item);
            p = p->next;
        }
    }

    void clear() {
        if (tail == head) return;
        Node *p = head->next;
        Node *tmp;
        while (p) {
            tmp = p;
            p = p->next;
            delete tmp;
        }
        tail = head;
        N = 0;
    }

    virtual ~BLinkedList() {
        clear();
        delete head;
    }

    int size() const {
        return N;
    }

    void addLast(const Item &item) {
        auto node = new Node(item);
        tail->next = node;
        tail = node;
        ++N;
    }

    void addFirst(const Item &item) {
        auto tmp = head->next;
        auto node = new Node(item, tmp);
        head->next = node;
        ++N;
    }

    void insert(int i, const Item &item) {
        if (i == 0)
            addFirst(item);
        else if (i == N)
            addLast(item);
        else if (i >= N || i < 0)
            throw std::out_of_range("BLinkedList::insert out_of_range");
        else {
            auto p = getNode(i - 1);
            auto tmp = p->next;
            auto node = new Node(item, tmp);
            p->next = node;
            ++N;
        }
    }

    const Item &get(int i) {
        if (i >= N || i < 0)
            throw std::out_of_range("BLinkedList::get out_of_range");
        return getNode(i)->item;
    }

    void set(int i, const Item &item) {
        if (i >= N || i < 0)
            throw std::out_of_range("BLinkedList::set out_of_range");
        getNode(i)->item = item;
    }

private:
    class Iterator {
        Node *it;
        Node *head;
        Node *tail;
    public:

        Iterator(Node *head, Node *tail) :
                it(head), head(head), tail(tail) {}

        bool hasNext() const {
            return it != tail;
        }

        Item &next() {
            return (it = it->next)->item;
        }

        const Item &next() const {
            return (it = it->next)->item;
        }
    };

public:
    Iterator iterator() const {
        return Iterator(head, tail);
    }

    friend int getWeight(int, int);
};

#endif //SBL_BLINKEDLIST_H

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll = long long;

int n;
BLinkedList<int> *lists;
bool *YES;

int getWeight(int i, int last) {
    int maxWeight = 0;
    auto p = lists[i].head->next;
    int weight = 0;
    while (p) {
        int a = p->item;
        if (a != last) {
            int w = getWeight(a, i);
            weight += w;
            if (w > maxWeight) maxWeight = w;
        }
        p = p->next;
    }
    if (n - 1 - weight > maxWeight)
        maxWeight = n - 1 - weight;
    if (maxWeight <= n / 2) YES[i] = true;
    return weight + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    lists = new BLinkedList<int>[n + 1];
    YES = new bool[n + 1]{};

    int a, b;
    for (int i = 0; i < n - 1; ++i) {
        cin >> a >> b;
        lists[a].addLast(b);
        lists[b].addLast(a);
    }

    getWeight(1, 0);
    for (int j = 1; j <= n; ++j) {
        if (YES[j]) cout << j << '\n';
    }
    delete[] lists;
    delete[] YES;
    return 0;
}