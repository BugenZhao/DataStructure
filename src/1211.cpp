//
// Created by BugenZhao on 2019/3/31.
//

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

template<typename Item>
class Queue {
    class Node {
    public:
        Item item;
        Node *next = nullptr;
    };

    int N;
    Node *first;
    Node *last;

public:
    Queue() {
        N = 0;
        first = last = nullptr;
    }

    bool isEmpty() {
        return N == 0;
    }

    int size() {
        return N;
    }

    void enqueue(Item item) {
        if (N == 0) {
            first = new Node{item};
            last = first;
        } else {
            Node *tmp = last;
            last = new Node{item};
            tmp->next = last;
        }
        ++N;
    }

    Item dequeue() {
        Item item = first->item;
        Node *tmp = first;
        first = first->next;
        if (N == 1) last = nullptr;
        delete tmp;
        --N;
        return item;
    }

    Item getFirst() {
        return first->item;
    }

    Item getLast() {
        return last->item;
    }

    virtual ~Queue() {
        Node *tmp;
        while (first != nullptr) {
            tmp = first;
            first = first->next;
            delete tmp;
        }
    }
};


// template<typename Item>
class BinaryTree {

    class Node {
    public:
        Node *left = nullptr, *right = nullptr;
        Node *father = nullptr;
        // Item val;
    };

    int size;
    int maxSize;
    Node *root;
    Node **nodes;

public:
    BinaryTree() {
        BinaryTree(5);
    }

    explicit BinaryTree(int maxSize) {
        root = nullptr;
        this->maxSize = maxSize;
        nodes = new Node *[maxSize + 1]{};
        for (int i = 1; i <= maxSize; ++i) {
            nodes[i] = new Node();
        }
        size = 0;
    }

    void add(int left, int right) {
        if (size == maxSize) resize(maxSize * 2);
        ++size;

        nodes[size]->left = nodes[left];
        nodes[size]->right = nodes[right];
        if (left) nodes[left]->father = nodes[size];
        if (right) nodes[right]->father = nodes[size];
    }

    void resize(int newSize) {
        auto oldNodes = nodes;
        nodes = new Node *[newSize + 1]{};
        for (int i = 1; i <= maxSize; ++i) {
            nodes[i] = oldNodes[i];
        }
        for (int i = maxSize + 1; i <= newSize; ++i) {
            nodes[i] = new Node;
        }
        maxSize = newSize;
    }

    void getRoot() {
        Node *p = nodes[1];
        while (p->father) {
            p = p->father;
        }
        root = p;
    }

    bool isCBT() {
        getRoot();

        Queue<Node *> queue;
        queue.enqueue(root);
        Node *p;

        while (p = queue.dequeue()) {
            queue.enqueue(p->left);
            queue.enqueue(p->right);
        }

        while (!queue.isEmpty()) {
            if (p = queue.dequeue()) {
                return false;
            }
        }
        return true;
    }

    virtual ~BinaryTree() {
        for (int i = 1; i <= maxSize; ++i) {
            delete nodes[i];
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    BinaryTree binaryTree(N);
    int a, b;
    for (int i = 0; i < N; ++i) {
        cin >> a >> b;
        binaryTree.add(a, b);
    }

    cout << (binaryTree.isCBT() ? 'Y' : 'N') << endl;
    return 0;
}
