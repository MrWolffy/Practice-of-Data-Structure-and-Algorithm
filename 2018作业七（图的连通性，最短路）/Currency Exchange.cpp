#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 110;
struct edge {
    int s, e;
    double r, c;
    edge(int ss, int ee, double rr, double cc): s(ss), e(ee), r(rr), c(cc) {}
    edge() {}
};
vector<edge> g(maxn);
double dist[maxn] = {0};
int n, m, s;
double v;

bool bellman_ford() {
    dist[s] = v;
    for (int k = 1; k < n; ++k) {
        for (int j = 0; j < g.size(); ++j) {
            int ss = g[j].s;
            int e = g[j].e;
            double t = (dist[ss] - g[j].c) * g[j].r;
            dist[e] = max(dist[e], t);
        }
    }
    for (int j = 0; j < g.size(); ++j) {
        int ss = g[j].s;
        int e = g[j].e;
        if (dist[e] < (dist[ss] - g[j].c) * g[j].r) return true;
    }
    return false;
}

int main() {
    cin >> n >> m >> s >> v;
    for (int i = 0; i < m; ++i) {
        int a, b;
        double r1, c1, r2, c2;
        cin >> a >> b >> r1 >> c1 >> r2 >> c2;
        g.push_back(edge(a, b, r1, c1));
        g.push_back(edge(b, a, r2, c2));
    }
    if (bellman_ford()) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}