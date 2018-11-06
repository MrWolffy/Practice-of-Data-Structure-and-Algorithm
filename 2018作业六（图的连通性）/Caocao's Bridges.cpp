#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int maxn = 1010;
const int inf = 0x3f3f3f3f;
vector<multimap<int, int> > g(maxn);
int m, n, t, mintroop;
int dfn[maxn], low[maxn], father[maxn];

void tarjan(int u, int f) {
    father[u] = f;
    low[u] = dfn[u] = t++;
    for (auto i = g[u].begin(); i != g[u].end(); ++i) {
        int v = i -> first;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v] && g[u].count(i -> first) == 1) mintroop = min(mintroop, i -> second);
        }
        else if (f != v) low[u] = min(low[u], dfn[v]);
    }
}

int main() {
    while (1) {
        cin >> n >> m;
        if (n == 0) return 0;
        int u, v, w = 1, i;
        g.clear(); g.resize(maxn);
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(father, 0, sizeof(father));
        t = 1; mintroop = inf;
        for (i = 0; i < m; ++i) {
            cin >> u >> v >> w;
            g[u].insert(make_pair(v, w));
            g[v].insert(make_pair(u, w));
        }
        tarjan(1, 0);
        for (i = 1; i <= n; ++i) if (!dfn[i]) break;
        if (i != n + 1) cout << 0 << endl;
        else if (mintroop == inf) cout << -1 << endl;
        else if (mintroop == 0) cout << 1 << endl;
        else cout << mintroop << endl;
    }
}