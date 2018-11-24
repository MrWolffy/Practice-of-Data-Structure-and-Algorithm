#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <deque>
#include <cstring>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 110;
int g[maxn][maxn] = {0};
bool visited[maxn] = {0};
int layer[maxn] = {0};
int p, n, S, T;
struct node {
    int part[12];
    node() {}
    node(int *a) {
        for (int i = 0; i < p; ++i) part[i] = a[i];
    }
    bool operator == (const node &a) {
        for (int i = 0; i < p; ++i) {
            if (part[i] != 2 && a.part[i] != 2 && part[i] != a.part[i]) return false;
        }
        return true;
    }
} nodes[maxn];
struct ansnode {
    int c, vs, vd;
    ansnode(int cc, int ss, int dd): c(cc), vs(ss), vd(dd) {}
};
vector<ansnode> ans;

void makegraph() {
    int s[12], e[12];
    for (int i = 0; i < p; ++i) {
        s[i] = 0; e[i] = 1;
    }
    nodes[S] = node(s); nodes[T] = node(e);
    for (int i = 1; i <= n; ++i) {
        if (nodes[S] == nodes[i]) g[S][i] = inf;
    }
    for (int i = n + 1; i <= 2 * n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (nodes[i] == nodes[j]) g[i][j] = inf;
        }
    }
    for (int i = n + 1; i <= 2 * n; ++i) {
        if (nodes[i] == nodes[T]) g[i][T] = inf;
    }
}

bool countlayer() {
    deque<int> q;
    memset(layer, 0xff, sizeof(layer));
    layer[S] = 0; q.push_back(S);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int j = 0; j <= T; ++j) {
            if (g[v][j] > 0 && layer[j] == -1) {
                layer[j] = layer[v] + 1;
                if (j == T) return true;
                else q.push_back(j);
            }
        }
    }
    return false;
}

void dinic() {
    int maxflow = 0;
    deque<int> q;
    while (countlayer()) {
        q.push_back(S);
        memset(visited, 0, sizeof(visited));
        visited[S] = 1;
        while (!q.empty()) {
            int nd = q.back();
            if (nd == T) {
                int minc = inf, minc_vs;
                for (int i = 1; i < q.size(); ++i) {
                    int vs = q[i-1], ve = q[i];
                    if (g[vs][ve] > 0) {
                        if (minc > g[vs][ve]) {
                            minc = g[vs][ve];
                            minc_vs = vs;
                        }
                    }
                }
                maxflow += minc;
                for (int i = 1; i < q.size(); ++i) {
                    int vs = q[i-1], ve = q[i];
                    g[vs][ve] -= minc;
                    g[ve][vs] += minc;
                    if (n < vs && vs <= 2 * n && 0 < ve && ve <= n) {
                        int j;
                        for (j = 0; j < ans.size(); ++j) {
                            if (ans[j].vs == vs && ans[j].vd == ve) {
                                ans[j].c += minc;
                                break;
                            }
                        }
                        if (j == ans.size()) ans.push_back(ansnode(minc, vs, ve));
                    }
                }
                while (!q.empty() && q.back() != minc_vs) {
                    visited[q.back()] = 0;
                    q.pop_back();
                }
            }
            else {
                int i;
                for (i = 0; i <= T; ++i) {
                    if (g[nd][i] > 0 && layer[i] == layer[nd] + 1 && !visited[i]) {
                        visited[i] = 1;
                        q.push_back(i);
                        break;
                    }
                }
                if (i > T) q.pop_back();
            }
        }
    }
    cout << maxflow << " " << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i].c > 0)
            cout << ans[i].vs - n << " " << ans[i].vd << " " << ans[i].c << endl;
        else if (ans[i].c < 0)
            cout << ans[i].vd << " " << ans[i].vs - n << " " << -ans[i].c << endl;
    }
}

void init() {
    S = 0; T = 2 * n + 1;
    memset(g, 0, sizeof(g));
    memset(visited, 0, sizeof(visited));
    memset(layer, 0, sizeof(layer));
    memset(nodes, 0, sizeof(nodes));
    ans.clear();
}

int main(){
    while (cin >> p >> n) {
        init();
        int q, s[12], d[12];
        for (int i = 1; i <= n; ++i) {
            cin >> q;
            for (int j = 0; j < p; ++j) cin >> s[j];
            for (int j = 0; j < p; ++j) cin >> d[j];
            nodes[i] = node(s); nodes[i + n] = node(d);
            g[i][i + n] = q;
        }
        makegraph();
        dinic();
    }
    return 0;
}