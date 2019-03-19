//
// Created by BugenZhao on 2019/3/16.
//

#include <iostream>
#include <string>

using namespace std;

template<typename Item>
class Table {
    int size;
    int i;
    Item *items;

public:
    explicit Table(int size) {
        this->size = size;
        i = 0;
        items = new Item[size]{};
    }

    void add(const Item &item) {
        items[i++] = item;
    }

    virtual ~Table() {
        delete[] items;
    }

    friend ostream &operator<<(ostream &os, const Table &table) {
        for (int i = 0; i < table.size; i++) {
            os << table.items[i] << ' ';
        }
        return os;
    }

    friend Table operator+(const Table &lhs, const Table &rhs) {
        Table ret(lhs.size + rhs.size);
        for (int i = 0; i < lhs.size; i++) {
            ret.add(lhs.items[i]);
        }
        for (int i = 0; i < rhs.size; i++) {
            ret.add(rhs.items[i]);
        }
        return ret;
    }
};

int main() {
    string typeName;
    int n, m;
    cin >> typeName >> n >> m;
    if (typeName == "int") {
        Table<int> tableA(n), tableB(m);
        int tmp;
        for (int i = 0; i < n; ++i) {
            cin >> tmp;
            tableA.add(tmp);
        }
        for (int i = 0; i < m; ++i) {
            cin >> tmp;
            tableB.add(tmp);
        }
        cout << (tableA + tableB) << endl;
    } else if (typeName == "char") {
        Table<char> tableA(n), tableB(m);
        char tmp;
        for (int i = 0; i < n; ++i) {
            cin >> tmp;
            tableA.add(tmp);
        }
        for (int i = 0; i < m; ++i) {
            cin >> tmp;
            tableB.add(tmp);
        }
        cout << (tableA + tableB) << endl;
    } else if (typeName == "double") {
        Table<double> tableA(n), tableB(m);
        double tmp;
        for (int i = 0; i < n; ++i) {
            cin >> tmp;
            tableA.add(tmp);
        }
        for (int i = 0; i < m; ++i) {
            cin >> tmp;
            tableB.add(tmp);
        }
        cout << (tableA + tableB) << endl;
    }
    return 0;
}
