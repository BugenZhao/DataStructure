//
// Created by BugenZhao on 2019/3/24.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>

using namespace std;

enum Bracket {
    L1, R1, L2, R2, L3, R3
};

class Stack {
    class Node {
    public:
        Bracket val;
        Node *next = nullptr;
    };

    Node *top;

public:
    Stack() {
        top = nullptr;
    }

    void push(const Bracket &bracket) {
        top = new Node{bracket, top};
    }

    Bracket peek() {
        return top->val;
    }

    Bracket pop() {
        Node *tmp = top;
        Bracket ret = top->val;
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

class BracketsStack {
    Stack s;
    Stack t;
    Stack u;

private:
    inline static bool isLeft(const Bracket &bracket) {
        return bracket == L1 || bracket == L2 || bracket == L3;
    }

    void pushT(const Bracket &bracket) {
        Bracket tmp;
        if (t.isEmpty()) {
            t.push(bracket);
        } else {
            tmp = t.peek();
            if (!isLeft(bracket) && bracket == 1 + tmp) {
                t.pop();
            } else {
                t.push(bracket);
            }
        }
    }

    void pushU(const Bracket &bracket) {
        Bracket tmp;
        if (u.isEmpty()) {
            u.push(bracket);
        } else {
            tmp = u.peek();
            if (isLeft(bracket) && bracket == tmp - 1) {
                u.pop();
            } else {
                u.push(bracket);
            }
        }
    }

    void pushTU(const Bracket &bracket) {
        Bracket tmp;
        if (isLeft(bracket)) {
            t.push(bracket);
        } else {
            if (u.isEmpty()) {
                pushT(bracket);
            } else {
                tmp = u.peek();
                if (bracket == tmp) {
                    u.pop();
                } else {
                    pushT(bracket);
                }
            }
        }
    }

public:
    void push(const Bracket &bracket) {
        s.push(bracket);
        pushTU(bracket);
    }

    void pop() {
        if (s.isEmpty()) return;
        Bracket bracket = s.pop();
        Bracket tmp;
        if (t.isEmpty() || t.peek() != bracket) {
            pushU(bracket);
        } else {
            t.pop();
        }
    }

    Bracket peek() {
        return s.peek();
    }

    bool match() {
        return t.isEmpty() && u.isEmpty();
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
    while (n--) {
        scanf("%d", &op);
        switch (op) {
            case 1:
                scanf(" %c", &c);
                switch (c) {
                    case '(':
                        b = L1;
                        break;
                    case ')':
                        b = R1;
                        break;
                    case '[':
                        b = L2;
                        break;
                    case ']':
                        b = R2;
                        break;
                    case '{':
                        b = L3;
                        break;
                    case '}':
                        b = R3;
                        break;
                }
                bracketsStack.push(b);
                break;
            case 2:
                bracketsStack.pop();
                break;
            case 3:
                if (bracketsStack.isEmpty()) break;
                b = bracketsStack.peek();
                switch (b) {
                    case L1:
                        c = '(';
                        break;
                    case R1:
                        c = ')';
                        break;
                    case L2:
                        c = '[';
                        break;
                    case R2:
                        c = ']';
                        break;
                    case L3:
                        c = '{';
                        break;
                    case R3:
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
        if (bracketsStack.match()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}