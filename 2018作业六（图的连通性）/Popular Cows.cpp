#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
using namespace std;

const int maxn = 10010;
vector<vector<int> > g(maxn);
vector<set<int> > g1;
int n, m, t = 0, idx = 0;
int dfn[maxn] = {0}, low[maxn] = {0};
int dict[maxn] = {0}, nodecount[maxn] = {0};
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
            dict[v] = idx;
            nodecount[idx]++;
        }
        idx++;
    }
}

void buildmap() {
    g1.resize(idx);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
            int u = dict[i], v = dict[g[i][j]];
            if (u != v) g1[u].insert(v);
        }
    }
}

int main() {
    int u, v;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) tarjan(i);
    }
    buildmap();
    int flag = 0, node = 0;
    for (int i = 0; i < g1.size(); ++i) {
        if (g1[i].empty()) {
            flag++; node = i;
        }
    }
    if (flag > 1) cout << 0 << endl;
    else cout << nodecount[node] << endl;
    return 0;
}