//
// Created by BugenZhao on 2019/4/29.
//

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

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BBinarySearchTree<string, int> counts;
    string maxTitle;
    int maxCount = 0;

    string cmd;
    string title;
    int count;
    while (true) {
        cin >> cmd;
        if (cmd[0] == 'f') break;
        else if (cmd[0] == 'c') {
            getline(cin, title);
            auto p = counts.get(title);
            if (p) count = (++p->val);
            else counts.put(title, count = 1);
            if (count == maxCount) {
                maxTitle = maxTitle < title ? maxTitle : title;
            } else if (count == maxCount + 1) {
                maxCount += 1;
                maxTitle = title;
            }
        } else if (cmd[0] == 'q') {
            cout << maxCount << ' ' << maxTitle << '\n';
        }
    }

    return 0;
}
