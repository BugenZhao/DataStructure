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

class Scholar {
public:
    char name[35];
    int h;
    int kickedBy;

    Scholar(const char *name, int h) {
        strcpy(this->name, name);
        this->h = h;
        kickedBy = -1;
    }
};

int main() {
    int N;
    cin >> N;
    Scholar **scholars = new Scholar *[N];
    Stack<Scholar *> stack;

    char *name = new char[35];
    int h;
    Scholar *tmp;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &h);
        fgets(name, 35, stdin);
        scholars[i] = new Scholar(name + 1, h);

        if (stack.isEmpty()) {
            stack.push(scholars[i]);
        } else {
            while (!stack.isEmpty()) {
                if (stack.peek()->h < h) {
                    stack.pop()->kickedBy = i;
                } else {
                    break;
                }
            }
            stack.push(scholars[i]);
        }
    }

    for (int i = 0; i < N; ++i) {
        if (scholars[i]->kickedBy == -1) {
            printf("-1");
        } else {
            printf(scholars[scholars[i]->kickedBy]->name);
        }
        printf("\n");
    }
    return 0;
}