//
// Created by BugenZhao on 2019/5/17.
//
//
// Created by BugenZhao on 2019/4/5.
//

#ifndef SBL_BQUEUE_H
#define SBL_BQUEUE_H


#include <iostream>

template<typename Item>
class BQueue {
    class Node {
    public:
        Item item;
        Node *next;

        explicit Node(const Item &item, Node *next = nullptr) : item(item), next(next) {}

        explicit Node(Node *next = nullptr) : next(next) {}

        virtual ~Node() = default;
    };

    int N;
    Node *first;
    Node *last;

public:
    BQueue() {
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

    virtual ~BQueue() {
        Node *tmp;
        while (first != nullptr) {
            tmp = first;
            first = first->next;
            delete tmp;
        }
    }

private:
    class Iterator {
        Node *it;
        Node *first;
        Node *last;
    public:

        Iterator(Node *first, Node *last) :
                it(first), first(first), last(last) {}

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
        return Iterator(first, last);
    }
};


#endif //SBL_BQUEUE_H


#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;

class Point {
public:
    int x, y;

    Point(int x = 0, int y = 0) :
            x(x), y(y) {}
};


int height[30][30];
Point from[30][30];
bool flag[30][30];
int X0, Y0, X, Y;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, m1, m2;
    cin >> m >> n >> m1 >> m2;
    int dx[] = {m1, m1, m2, m2, -m1, -m1, -m2, -m2};
    int dy[] = {m2, -m2, m1, -m1, m2, -m2, m1, -m1};

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> height[i][j];
            if (height[i][j] == 3) X0 = i, Y0 = j;
            else if (height[i][j] == 4) X = i, Y = j;
        }
    }

    BQueue<Point> q;
    q.enqueue(Point(X0, Y0));
    from[X0][Y0] = {-1, -1};
    flag[X0][Y0] = true;

    while (!q.isEmpty()) {
        Point point = q.dequeue();
        for (int i = 0; i < 8; ++i) {
            int xx = point.x + dx[i];
            int yy = point.y + dy[i];
            if (xx < 0 || xx >= m || yy < 0 || yy >= n || flag[xx][yy]) continue;
            if (height[xx][yy] == 0 || height[xx][yy] == 2) continue;
            if (height[xx][yy] == 4) {
                int ans = 1;
                int x = point.x, y = point.y;
                while (true) {
                    if (x == X0 && y == Y0) break;
                    ++ans;
                    Point tmp = from[x][y];
                    x = tmp.x, y = tmp.y;
                }
                cout << ans << endl;
                return 0;
            }
            if (height[xx][yy] == 1) {
                flag[xx][yy] = true;
                q.enqueue(Point(xx, yy));
                from[xx][yy] = Point(point.x, point.y);
            }
        }
    }
}