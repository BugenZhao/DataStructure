//
// Created by BugenZhao on 2019/4/10.
//

//
// Created by BugenZhao on 2019/4/5.
//

#ifndef SBL_BSTACK_H
#define SBL_BSTACK_H


template<typename Item>
class BStack {
    class Node {
    public:
        Item item;
        Node *next;

        explicit Node(const Item &item, Node *next = nullptr) : item(item), next(next) {}

        explicit Node(Node *next = nullptr) : next(next) {}

        virtual ~Node() = default;
    };

    int N;
    Node *top;

public:
    BStack() {
        top = nullptr;
        N = 0;
    }

    void push(const Item &item) {
        top = new Node{item, top};
        ++N;
    }

    Item peek() {
        return top->item;
    }

    Item pop() {
        Node *tmp = top;
        Item ret = top->item;
        top = top->next;
        delete tmp;
        --N;
        return ret;
    }

    int size() {
        return N;
    }

    void clear() {
        Node *tmp;
        while (top) {
            tmp = top;
            top = top->next;
            delete tmp;
        }
        top = nullptr;
        N = 0;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    virtual ~BStack() {
        Node *tmp;
        while (top) {
            tmp = top;
            top = top->next;
            delete tmp;
        }
    }

private:
    class Iterator {
        Node *it;
        Node *top;
    public:

        Iterator(Node *top) : it(top), top(top) {}

        bool hasNext() const {
            return it != nullptr;
        }

        Item &next() {
            Node *p = it;
            it = it->next;
            return p->item;
        }

        const Item &next() const {
            Node *p = it;
            it = it->next;
            return p->item;
        }
    };

public:
    Iterator iterator() const {
        return Iterator(top);
    }
};


#endif //SBL_BSTACK_H


class S {
public:
    int power;
    bool dir;
};


#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    BStack<S> stack;

    int power;
    bool dir;
    for (int i = 0; i < N; ++i) {
        cin >> power >> dir;

        while (!stack.isEmpty()) {
            if (stack.peek().dir == 0 || stack.peek().dir == dir) {
                stack.push(S{power, dir});
                break;
            } else {
                if (stack.peek().power >= power) {
                    break;
                } else {
                    stack.pop();
                }

            }
        }
        if (stack.isEmpty()) {
            stack.push(S{power, dir});
        }
    }
    cout << stack.size() << endl;
    return 0;
}