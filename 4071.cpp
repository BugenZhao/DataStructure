//
// Created by BugenZhao on 2019/5/17.
//

#include <iostream>
#include <string>

using std::ios, std::cin, std::cout, std::endl, std::string;
using ll=long long;
using ull=unsigned long long;

const int P = 1e9 + 7;

class Matrix2D {
public:
    ll a, b, c, d;

    Matrix2D(ll a, ll b, ll c, ll d) :
            a(a), b(b), c(c), d(d) {}
};

Matrix2D operator*(const Matrix2D &x, const Matrix2D &y) {
    ll a = x.a * y.a + x.b * y.c;
    ll b = x.a * y.b + x.b * y.d;
    ll c = x.c * y.a + x.d * y.c;
    ll d = x.c * y.b + x.d * y.d;
    return Matrix2D(a % P, b % P, c % P, d % P);
}

Matrix2D pow(const Matrix2D &m, ull p) {
    if (p == 0) return Matrix2D(1, 0, 0, 1);
    if (p == 1) return m;
    Matrix2D tmp = pow(m, p / 2);
    if (p % 2) return tmp * tmp * m;
    else return tmp * tmp;
}

int main() {
    ull n;
    cin >> n;
    Matrix2D ans = pow(Matrix2D(1, 1, 1, 0), n);
    cout << ans.a << endl;
    return 0;
}