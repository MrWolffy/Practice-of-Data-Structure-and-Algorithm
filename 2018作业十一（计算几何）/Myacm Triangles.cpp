#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>
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
int sideOfLine(CPoint p, CPoint a, CPoint b) {
    double result = (p - a) ^ (b - a);
    if (isZero(result)) return 0;
    else if (result > 0) return 1;
    else return -1;
}


int main() {
    int n;
    CPoint points[20];
    char ch;
    while (cin >> n && n != 0) {
        double maxarea = 0; int maxpoint[3];
        for (int i = 0; i < n; ++i) cin >> ch >> points[i].x >> points[i].y;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (i != j && j != k && k != i) {
                        CPoint a = points[i], b = points[j], c = points[k], t;
                        double sgn = area(b - a, c - b);
                        if (sgn > 0) {t = b; b = c; c = t; }
                        int flag = 0;
                        for (int l = 0; l < n; ++l) {
                            if (l != i && l != j && l != k) {
                                if (sideOfLine(points[l], a, b) >= 0 && sideOfLine(points[l], b, c) >= 0 && sideOfLine(points[l], c, a) >= 0) {
                                    flag = 1;
                                    break;
                                }
                            }
                        }
                        if (flag) continue;
                        if (fabs(sgn) > maxarea) {
                            maxarea = fabs(sgn);
                            maxpoint[0] = i;
                            maxpoint[1] = j;
                            maxpoint[2] = k;
                        }
                    }
                }
            }
        }
        sort(maxpoint, maxpoint + 3);
        printf("%c%c%c\n", maxpoint[0] + 'A', maxpoint[1] + 'A', maxpoint[2] + 'A');
    }
    return 0;
}