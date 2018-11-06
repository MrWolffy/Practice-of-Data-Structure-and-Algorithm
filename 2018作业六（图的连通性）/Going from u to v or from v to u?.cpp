#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <cstring>
using namespace std;

const int maxn = 1010;
vector<vector<int> > g(maxn);
vector<set<int> > g1(maxn);
int m, n, t = 0, idx = 0;
int dfn[maxn] = {0}, low[maxn] = {0};
bool visited[maxn] = {0};
list<int> stk;

void tarjan(int u) {
    visited[u] = true;
    dfn[u] = low[u] = ++t;
    stk.push_back(u);
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (!visited[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (find(stk.begin(), stk.end(), v) != stk.end())
            low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u]) {
        int v = -1;
        while (u != v) {
            v = *stk.rbegin();
            stk.pop_back();
        }
        idx++;
    }
}

int main() {
    int T = 0;
    cin >> T;
    while (T--) {
        g.clear(); g.resize(maxn);
        g1.clear(); g1.resize(maxn);
        t = 0; idx = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(visited, 0, sizeof(visited));
        stk.clear();
        cin >> n >> m;
        int u, v;
        for (int i = 0; i < m; ++i) {
            cin >> u >> v;
            g[u].push_back(v);
        }
        tarjan(1);
        if (idx > 1) cout << "No" << endl;
        else cout << "Yes" << endl;
    }
}