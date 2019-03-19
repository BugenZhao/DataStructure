//
// Created by BugenZhao on 2019/3/16.
//

#include <iostream>
#include <string>

using namespace std;

class TuringAwardWinnerLinkedList {
    class Node {
    public:
        int year = 0;
        string name;
        Node *next = nullptr;
    };

    static inline bool less(const Node &a, const Node &b) {
        return a.year == b.year ? a.name < b.name : a.year < b.year;
    }

    Node *head;
    int size;

public:
    TuringAwardWinnerLinkedList() {
        size = 0;
        head = new Node{0, "666", nullptr};
    }

    void insert(int year, const string &name) {
        Node *toInsert = new Node{year, name, nullptr};
        Node *p = head;
        while (p != nullptr) {
            if (p->next == nullptr) {
                p->next = toInsert;
                break;
            }
            if (less(*toInsert, *p->next)) {
                Node *tmp = p->next;
                p->next = toInsert;
                toInsert->next = tmp;
                break;
            }
            p = p->next;
        }
        ++size;
    }

    void del(int i) {
        i -= 1;
        Node *p = head;
        while (i--) {
            p = p->next;
        }
        Node *tmp = p->next;
        p->next = tmp->next;
        delete tmp;
        --size;
    }

    void list(int i) {
        Node *p = head;
        while (i--) {
            p = p->next;
        }
        cout << p->year << " " << p->name << endl;
    }

    virtual ~TuringAwardWinnerLinkedList() {
        Node *p = head->next;
        while (p != nullptr) {
            Node *tmp = p->next;
            delete p;
            p = tmp;
        }
        delete head;
    }
};

int main() {
    TuringAwardWinnerLinkedList linkedList;
    int N;
    string op;
    cin >> N;
    while (N--) {
        cin >> op;
        if (op == "insert") {
            int year;
            string name;
            cin >> year;
            getline(cin, name);
            linkedList.insert(year, name.substr(1, name.size() - 1));
        } else if (op == "delete") {
            int i;
            cin >> i;
            linkedList.del(i);
        } else if (op == "list") {
            int i;
            cin >> i;
            linkedList.list(i);
        }
    }
    return 0;
}
