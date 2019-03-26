//
// Created by BugenZhao on 2019/3/25.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

template<typename Item>
class Stack {
    class Node {
    public:
        Item val;
        Node *next = nullptr;
    };

    int size;
    Node *top;

public:
    Stack() {
        top = nullptr;
        size = 0;
    }

    void push(const Item &item) {
        top = new Node{item, top};
    }

    Item peek() {
        return top->val;
    }

    Item pop() {
        Node *tmp = top;
        Item ret = top->val;
        top = top->next;
        delete tmp;
        return ret;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    virtual ~Stack() {
        Node *tmp;
        while (top) {
            tmp = top;
            top = top->next;
            delete tmp;
        }
    }
};

using Bracket=int;

class BracketsStack {
    Stack<Bracket> s;
    Stack<Bracket> t;

private:
    inline static bool isLeft(const Bracket &bracket) {
        int j = bracket % 6;
        return j == 0 || j == 2 || j == 4;
    }

    void pushT(const Bracket &bracket) {
        Bracket tmp;
        if (t.isEmpty()) {
            t.push(bracket);
        } else {
            tmp = t.peek();
            if (!isLeft(bracket) && (bracket - tmp - 1) % 6 == 0) {
                t.pop();
            } else {
                t.push(bracket);
            }
        }
    }

public:
    void push(const Bracket &bracket) {
        s.push(bracket);
        pushT(bracket);
    }

    void pop() {
        if (s.isEmpty()) return;
        Bracket bracket = s.pop();
        if (isLeft(bracket)) {
            t.pop();
        } else {
            Bracket tmp;
            if (t.isEmpty() || t.peek() != bracket) {
                t.push(bracket - 1);
            } else {
                t.pop();
            }
        }
    }

    Bracket peek() {
        return s.peek();
    }

    bool match() {
        return t.isEmpty();
    }

    bool isEmpty() {
        return s.isEmpty();
    }
};

int main() {
    BracketsStack bracketsStack;
    int n;
    cin >> n;

    int op;
    char c;
    Bracket b;
    int count = 0;

    while (n--) {
        scanf("%d", &op);
        switch (op) {
            case 1:
                scanf(" %c", &c);
                switch (c) {
                    case '(':
                        b = 6 * count;
                        break;
                    case ')':
                        b = 6 * count + 1;
                        break;
                    case '[':
                        b = 6 * count + 2;
                        break;
                    case ']':
                        b = 6 * count + 3;
                        break;
                    case '{':
                        b = 6 * count + 4;
                        break;
                    case '}':
                        b = 6 * count + 5;
                        break;
                }
                bracketsStack.push(b);
                ++count;
                break;
            case 2:
                bracketsStack.pop();
                break;
            case 3:
                if (bracketsStack.isEmpty()) break;
                b = bracketsStack.peek();
                switch (b % 6) {
                    case 0:
                        c = '(';
                        break;
                    case 1:
                        c = ')';
                        break;
                    case 2:
                        c = '[';
                        break;
                    case 3:
                        c = ']';
                        break;
                    case 4:
                        c = '{';
                        break;
                    case 5:
                        c = '}';
                        break;
                }
                printf("%c\n", c);
                break;
            case 4:
                if (bracketsStack.match()) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
                break;
        }
    }
    return 0;
}