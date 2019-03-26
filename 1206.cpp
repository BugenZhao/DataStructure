//
// Created by BugenZhao on 2019/3/24.
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

const char *tokens[] = {"begin", "end", "if", "then", "else"};

int main() {
    Stack<int> s;
    char token[100];
    bool flag = true;
    int tmp;
    while (cin >> token) {
        if (strcmp(token, "BZ") == 0) break;
        if (!flag) break;
        int i;
        for (i = 0; i < 5; ++i) {
            if (strcmp(token, tokens[i]) == 0) break;
        }
        switch (i) {
            case 0:
                s.push(0);
                break;
            case 1:
                if (s.isEmpty()) {
                    flag = false;
                    break;
                }
                while (true) {
                    tmp = s.pop();
                    if (tmp == 3) continue;
                    else if (tmp == 0) break;
                    else flag = false;
                }
                break;
            case 2:
                s.push(2);
                break;
            case 3:
                if (s.isEmpty()) {
                    flag = false;
                    break;
                }
                tmp = s.peek();
                if (tmp != 2) {
                    flag = false;
                } else {
                    s.pop();
                    s.push(3);
                }
                break;
            case 4:
                if (s.isEmpty()) {
                    flag = false;
                    break;
                }
                tmp = s.peek();
                if (tmp != 3) {
                    flag = false;
                } else {
                    s.pop();
                }
                break;
        }
    }

    if (flag && s.isEmpty()) {
        cout << "Match!" << endl;
    } else {
        cout << "Error!" << endl;
    }
    return 0;
}