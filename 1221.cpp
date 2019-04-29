//
// Created by BugenZhao on 2019/4/25.
//

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
    int find_ith_curCount;
    Node *find_ith_ans;

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

    void removeMin(Node *&node) {
        if (node == nullptr) return;
        if (node->left == nullptr) {
            auto oldNode = node;
            node = node->right;
            delete node;
        } else {
            removeMin(node->left);
        }
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

    void delete_less_than(Node *&node, const Key &key) {
        if (node == nullptr) return;
        delete_less_than(node->left, key);
        delete_less_than(node->right, key);
        if (node->data.key < key) remove(node, node->data.key);
    }

    void delete_greater_than(Node *&node, const Key &key) {
        if (node == nullptr) return;
        delete_greater_than(node->left, key);
        delete_greater_than(node->right, key);
        if (node->data.key > key) remove(node, node->data.key);
    }

    void delete_interval(Node *&node, const Key &a, const Key &b) {
        if (node == nullptr) return;
        delete_interval(node->left, a, b);
        delete_interval(node->right, a, b);
        if (node->data.key > a && node->data.key < b) remove(node, node->data.key);
    }

    void find_ith(Node *node, int i) {
        if (find_ith_ans) return;
        if (node == nullptr) return;
        find_ith(node->left, i);
        if (find_ith_ans) return; // awesome
        if ((find_ith_curCount -= node->data.val) <= 0) {
            find_ith_ans = node;
            return;
        }
        find_ith(node->right, i);
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

    void delete_less_than(const Key &key) {
        delete_less_than(root, key);
    }

    void delete_greater_than(const Key &key) {
        delete_greater_than(root, key);
    }

    void delete_interval(const Key &a, const Key &b) {
        delete_interval(root, a, b);
    }

    BPair<Key, Val> *find_ith(int i) {
        if (i <= 0) return nullptr;
        find_ith_curCount = i;
        find_ith_ans = nullptr;
        find_ith(root, i);
        if (find_ith_ans) return &find_ith_ans->data;
        else return nullptr;
    }
};

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BBinarySearchTree<int, int> bst;

    int n;
    string cmd;
    int a, b;

    cin >> n;
    while (n--) {
        cin >> cmd;
        if (cmd == "insert") {
            cin >> a;
            auto p = bst.get(a);
            if (p) ++(p->val);
            else bst.put(a, 1);
        } else if (cmd == "delete") {
            cin >> a;
            auto p = bst.get(a);
            if (p) --(p->val);
        } else if (cmd == "find") {
            cin >> a;
            auto p = bst.get(a);
            if (p && p->val) cout << "Y\n";
            else cout << "N\n";
        } else if (cmd == "delete_less_than") {
            cin >> a;
            bst.delete_less_than(a);
        } else if (cmd == "delete_greater_than") {
            cin >> a;
            bst.delete_greater_than(a);
        } else if (cmd == "delete_interval") {
            cin >> a >> b;
            bst.delete_interval(a, b);
        } else if (cmd == "find_ith") {
            cin >> a;
            auto p = bst.find_ith(a);
            if (p) cout << p->key << '\n';
            else cout << "N\n";
        }
    }
}