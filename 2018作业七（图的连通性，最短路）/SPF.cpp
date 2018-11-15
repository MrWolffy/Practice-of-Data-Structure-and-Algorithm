#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int maxn = 1010;
vector<vector<int> > g;
int low[maxn] = {0}, dfn[maxn] = {0};
int ntime = 1;
int sons[maxn] = {0}, son = 0;

void tarjan(int u) {
    dfn[u] = low[u] = ntime++;
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                if (u >= 2) sons[u]++;
                else son++;
            }
        }
        low[u] = min(low[u], dfn[v]);
    }
}

int main() {
    int t = 1, a, b, n;
    while (cin >> a && a) {
        n = 0; son = 0; ntime = 1;
        g.clear();
        g.resize(maxn);
        memset(low, 0, sizeof(low));
        memset(dfn, 0, sizeof(dfn));
        memset(sons, 0, sizeof(sons));
        while (true) {
            cin >> b;
            g[a].push_back(b); n = max(n, a);
            g[b].push_back(a); n = max(n, b);
            cin >> a;
            if (a == 0) break;
        }
        tarjan(1);
        if (son > 1) sons[1] = son - 1;
        cout << "Network #" << t++ << endl;
        bool flag = false;
        for (int i = 1; i <= n; ++i) {
            if (sons[i]) {
                cout << "  SPF node " << i << " leaves " << sons[i] + 1 << " subnets\n";
                flag = true;
            }
        }
        if (!flag) cout << "  No SPF nodes\n";
        cout << "\n";
    }
}