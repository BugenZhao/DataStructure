//
// Created by BugenZhao on 2019/4/29.
//

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll = long long;


#ifndef SBL_BBINARYSEARCHTREE_H
#define SBL_BBINARYSEARCHTREE_H

template<typename Key, typename Val>
class BPair {
public:
    Key key;
    Val val;

    BPair(Key key, Val val) : key(key), val(val) {}

    BPair() = delete;
};

template<typename Key, typename Val>
class BBinarySearchTree {
    class Node {
    public:
        BPair<Key, Val> data;
        Node *left;
        Node *right;

        explicit Node(const BPair<Key, Val> &data, Node *left = nullptr, Node *right = nullptr) :
                data(data), left(left), right(right) {}
    };

    Node *root;
    int size;

private:
    BPair<Key, Val> *get(Node *node, const Key &key) {
        if (node == nullptr || node->data.key == key)
            return &node->data;
        if (key < node->data.key)
            return get(node->left, key);
        else
            return get(node->right, key);
    }

    void put(Node *&node, const Key &key, const Val &val) {
        if (node == nullptr)
            node = new Node({key, val});
        else if (key < node->data.key)
            put(node->left, key, val);
        else if (key > node->data.key)
            put(node->right, key, val);
        else
            node->data.val = val;
    }

    void remove(Node *&node, const Key &key) {
        if (node == nullptr)
            return;
        if (key < node->data.key)
            remove(node->left, key);
        else if (key > node->data.key)
            remove(node->right, key);
        else if (node->right == nullptr) {
            auto oldNode = node;
            node = node->left;
            delete oldNode;
        } else if (node->left == nullptr) {
            auto oldNode = node;
            node = node->right;
            delete oldNode;
        } else {
            auto p = node->right;
            while (p->left != nullptr) p = p->left;
            node->data = p->data;
            remove(node->right, node->data.key);
        }
    }

    void clear(Node *&node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
        --size;
    }

public:
    BBinarySearchTree() : root(nullptr), size(0) {}

    BPair<Key, Val> *get(const Key &key) {
        return get(root, key);
    }

    void put(const Key &key, const Val &val) {
        put(root, key, val);
    }

    void remove(const Key &key) {
        remove(root, key);
    }

    void clear() {
        clear(root);
    }

    virtual ~BBinarySearchTree() {
        clear();
    }
};


#endif //SBL_BBINARYSEARCHTREE_H

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
        while (head) {
            addLast(head->item);
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

    friend int main();
};

#endif //SBL_BLINKEDLIST_H

BLinkedList<string> *lists[100000] = {};
int count = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    string name, email;
    BBinarySearchTree<string, BLinkedList<string> *> bst;
    BLinkedList<string> emails;

    while (N--) {
        cin >> name >> email;
        auto p = bst.get(email);
        if (p) p->val->addLast(name);
        else {
            emails.addLast(email);
            auto list = lists[count++];
            list = new BLinkedList<string>();
            list->addLast(name);
            bst.put(email, list);
        }
    }

    auto it = emails.iterator();
    while (it.hasNext()) {
        auto itt = bst.get(it.next())->val->iterator();
        while (itt.hasNext()) {
            cout << itt.next() << ' ';
        }
        cout << '\n';
    }

    auto p = lists;
    while (*p) {
        delete p;
        p += 1;
    }
    return 0;
}