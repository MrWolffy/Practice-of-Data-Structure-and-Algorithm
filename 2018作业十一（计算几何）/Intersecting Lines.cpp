#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <map>
#define CPoint CVector
using namespace std;

const double EPS = 1e-6;

bool isZero(double x) {
    return -EPS < x && x < EPS;
}

struct CVector {
    double x, y;
    CVector() {}
    CVector(double xx, double yy): x(xx), y(yy) {}
};
struct CLine {
    CPoint a, b;
    CLine() {}
    CLine(const CPoint &aa, const CPoint &bb): a(aa), b(bb) {}
};



CVector operator +(CVector p, CVector q) {
    return CVector(p.x + q.x, p.y + q.y);
}
CVector operator -(CVector p, CVector q) {
    return CVector(p.x - q.x, p.y - q.y);
}
CVector operator *(double k, CVector p) {
    return CVector(k * p.x, k * p.y);
}
double operator *(CVector p, CVector q) {
    return p.x * q.x + p.y + q.y;
}
double operator ^(CVector p, CVector q) {
    return p.x * q.y - q.x * p.y;
}


double area(CVector p, CVector q) {
    return (p ^ q) / 2;
}
void intersect(CLine l, CLine m) {
    double x = area(m.a - l.a, l.b - l.a);
    double y = area(l.b - l.a, m.b - l.a);
    if (isZero(x + y)) {
        if (isZero((l.a - m.a) ^ (m.b - m.a))) printf("LINE\n");
        else printf("NONE\n");
        return;
    }
    CPoint ans = m.a + x / (x + y) * (m.b - m.a);
    printf("POINT %.2f %.2f\n", ans.x, ans.y);
}


int main() {
    int n;
    cin >> n;
    printf("INTERSECTING LINES OUTPUT\n");
    while (n--) {
        CPoint points[4];
        for (int i = 0; i < 4; ++i) cin >> points[i].x >> points[i].y;
        intersect(CLine(points[0], points[1]), CLine(points[2], points[3]));
    }
    printf("END OF OUTPUT\n");
    return 0;
}