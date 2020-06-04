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

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int height[50][50];
int r, c;
BQueue<Point> q;
Point *toFill;
int toFillCount;
bool *status;
int landCount = 0;

int ansCount = 0;
int ans[50][50];

void doDfs(int x, int y, int &curCount, bool flag[50][50]) {
    flag[x][y] = true;
    ++curCount;
    for (int i = 0; i < 4; ++i) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 0 || xx >= r || yy < 0 || yy >= c
            || !height[xx][yy] || flag[xx][yy])
            continue;
        doDfs(xx, yy, curCount, flag);
    }
}

int dfs(int x0, int y0) {
    bool flag[50][50]{};
    int curCount = 0;
    doDfs(x0, y0, curCount, flag);
    return curCount;
}

void DFS(int cur) {
    if (ansCount >= 2) return;
    if (cur == toFillCount) {
        if (landCount == 0)
            return;
        int x0 = -1, y0 = -1;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (x0 != -1) goto interesting;
                else if (height[i][j]) x0 = i, y0 = j;
            }
        }
        interesting:
        if (dfs(x0, y0) == landCount) {
            if (ansCount == 0) {
                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < c; ++j) {
                        ans[i][j] = height[i][j];
                    }
                }
            }
            ++ansCount;
        }
    } else {
        status[cur] = true;
        height[toFill[cur].x][toFill[cur].y] = 1;
        ++landCount;
        DFS(cur + 1);
        status[cur] = false;
        height[toFill[cur].x][toFill[cur].y] = 0;
        --landCount;
        DFS(cur + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> r >> c;
    int x0 = -1, y0 = -1;

    if (r * c <= 150) {
        char tmp;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> tmp;
                switch (tmp) {
                    case '#':
                        height[i][j] = 0;
                        break;
                    case '?':
                        height[i][j] = 1;
                        q.enqueue(Point(i, j));
                        break;
                    case '.':
                        height[i][j] = 1;
                        ++landCount;
                        if (x0 == -1) x0 = i, y0 = j;
                        break;
                }
            }
        }

        toFillCount = q.size();
        toFill = new Point[toFillCount];
        status = new bool[toFillCount]{};
        int ii = 0;
        while (!q.isEmpty()) toFill[ii++] = q.dequeue();

        DFS(0);

        if (ansCount == 0)
            cout << "Impossible" << endl;
        else if (ansCount == 1) {
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    cout << (ans[i][j] ? '.' : '#');
                }
                cout << '\n';
            }
        } else
            cout << "Ambiguous" << endl;

        return 0;
    } else {
        char tmp;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> tmp;
                switch (tmp) {
                    case '#':
                        height[i][j] = 0;
                        break;
                    case '?':
                        height[i][j] = 1;
                        ++landCount;
                        q.enqueue(Point(i, j));
                        break;
                    case '.':
                        height[i][j] = 1;
                        ++landCount;
                        if (x0 == -1) x0 = i, y0 = j;
                        break;
                }
            }
        }
        if (landCount == 0) {
            cout << "Impossible" << endl;
            return 0;
        }
        if (x0 == -1)
            x0 = q.getFirst().x, y0 = q.getLast().y;

        if (dfs(x0, y0) != landCount) {
            cout << "Impossible" << endl;
            return 0;
        } else {
            bool ambiguous = false;
            --landCount;
            while (!ambiguous && !q.isEmpty()) {
                Point point = q.dequeue();
                height[point.x][point.y] = 0;
                if (dfs(x0, y0) == landCount) ambiguous = true;
                height[point.x][point.y] = 1;
            }
            if (ambiguous) {
                cout << "Ambiguous" << endl;
            } else {
                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < c; ++j) {
                        cout << (height[i][j] ? '.' : '#');
                    }
                    cout << '\n';
                }
            }
        }
        return 0;
    }
}