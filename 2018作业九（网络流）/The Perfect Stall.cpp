#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int inf = 0x3f3f3f3f, maxn = 450;
int m, n, s, e;
int g[maxn][maxn] = {0};
bool visited[maxn] = {0};
int layers[maxn] = {0};

void buildmap() {
    for (int i = 1; i <= n; ++i) g[0][i] = 1;
    for (int j = n + 1; j < e; ++j) g[j][e] = 1;
}

bool countlayer() {
    deque<int> q;
    memset(layers, 0xff, sizeof(layers));
    layers[s] = 0; q.push_back(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int j = s; j <= e; ++j) {
            if (g[v][j] > 0 && layers[j] == -1) {
                layers[j] = layers[v] + 1;
                if (j == e) return true;
                else q.push_back(j);
            }
        }
    }
    return false;
}

int dinic() {
    int maxflow = 0, i;
    deque<int> q;
    while (countlayer()) {
        q.push_back(s);
        memset(visited, 0, sizeof(visited));
        visited[s] = 1;
        while (!q.empty()) {
            int nd = q.back();
            if (nd == e) {
                int minc = inf, minc_vs;
                for (i = 1; i < q.size(); ++i) {
                    int vs = q[i-1], ve = q[i];
                    if (g[vs][ve] > 0) {
                        if (minc > g[vs][ve]) {
                            minc = g[vs][ve];
                            minc_vs = vs;
                        }
                    }
                }
                maxflow += minc;
                for (i = 1; i < q.size(); ++i) {
                    int vs = q[i-1], ve = q[i];
                    g[vs][ve] -= minc;
                    g[ve][vs] += minc;
                }
                while (!q.empty() && q.back() != minc_vs) {
                    visited[q.back()] = 0;
                    q.pop_back();
                }
            }
            else {
                for (i = s; i <= e; ++i) {
                    if (g[nd][i] > 0 && layers[i] == layers[nd] + 1 && !visited[i]) {
                        visited[i] = 1;
                        q.push_back(i);
                        break;
                    }
                }
                if (i > e) q.pop_back();
            }
        }
    }
    return maxflow;
}

int main() {
    while (cin >> n >> m) {
        s = 0; e = n + m + 1;
        memset(g, 0, sizeof(g));
        int si, t;
        for (int i = 1; i <= n; ++i) {
            cin >> si;
            for (int j = 0; j < si; ++j) {
                cin >> t;
                g[i][n+t] = 1;
            }
        }
        buildmap();
        cout << dinic() << endl;
    }
    return 0;
}