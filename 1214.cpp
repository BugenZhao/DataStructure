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

    bool isEmpty() const {
        return N == 0;
    }

    int size() const {
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

    Item getFirst() const {
        return first->item;
    }

    Item getLast() const {
        return last->item;
    }

    void clear() {
        Node *tmp;
        while (first != nullptr) {
            tmp = first;
            first = first->next;
            delete tmp;
        }
        N = 0;
        first = last = nullptr;
    }

    void print(ostream &os = std::cout) const {
        Node *p = first;
        while (p) {
            os << p->item << ' ';
            p = p->next;
        }
        os << endl;
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

template<typename Item>
class BinaryTree {

    class Node {
    public:
        Node *left = nullptr, *bro = nullptr;
        Node *father = nullptr;
        Item val;
    };

    int size;
    int maxSize;
    Node *root;
    Node **nodes;

    Queue<Item> pre;
    Queue<Item> post;
    Queue<Item> level;

private:
    void dfs(Node *node) {
        pre.enqueue(node->val);
        if (node->left) dfs(node->left);
        post.enqueue(node->val);
        if (node->bro) dfs(node->bro);
    }

    void bfs() {
        Queue<Node *> queue;
        queue.enqueue(root);

        Node *p;
        while (!queue.isEmpty()) {
            p = queue.dequeue();
            while (p) {
                level.enqueue(p->val);
                if (p->left)
                    queue.enqueue(p->left);
                p = p->bro;
            }
        }
    }

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

    void add(int left, int bro, Item item) {
        if (size == maxSize) resize(maxSize * 2);
        ++size;

        nodes[size]->val = item;
        nodes[size]->left = nodes[left];
        nodes[size]->bro = nodes[bro];
        if (left) nodes[left]->father = nodes[size];
        if (bro) nodes[bro]->father = nodes[size];
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

    void traverse() {
        getRoot();
        pre.clear();
        post.clear();
        level.clear();

        dfs(root);
        bfs();
    };

    const Queue<Item> &getPre() {
        return pre;
    }

    const Queue<Item> &getPost() {
        return post;
    }

    const Queue<Item> &getLevel() {
        return level;
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
    BinaryTree<int> binaryTree(N);
    int a, b, c;
    while (N--) {
        cin >> a >> b >> c;
        binaryTree.add(a, b, c);
    }

    binaryTree.traverse();
    binaryTree.getPre().print();
    binaryTree.getPost().print();
    binaryTree.getLevel().print();

    return 0;
}