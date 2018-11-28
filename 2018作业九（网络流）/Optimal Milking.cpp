#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int inf = 0x3f3f3f3f, maxn = 300;
int k, c, m, r = inf, l = 0, mid, s, e;
int map[maxn][maxn] = {0}, g[maxn][maxn] = {0};
bool visited[maxn] = {0};
int layers[maxn] = {0};

void floyd() {
    for (int k = 1; k < e; k++) {
        for (int i = 1; i < e; i++) {
            for (int j = 1; j < e; j++) {
                if (map[i][j] > map[i][k] + map[k][j]) {
                    map[i][j] = map[i][k] + map[k][j];
                }
            }
        }
    }
}

void buildmap(int mid) {
    memset(g, 0, sizeof(g));
    for (int i = k + 1; i < e; ++i) g[s][i] = 1;
    for (int j = 1; j <= k; ++j) g[j][e] = m;
    for (int j = 1; j <= k; ++j) {
        for (int i = k + 1; i < e; ++i) {
            if (map[i][j] <= mid) g[i][j] = 1;
        }
    }
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
    cin >> k >> c >> m;
    s = 0; e = k + c + 1;
    for (int i = 1; i < e; ++i) {
        for (int j = 1; j < e; ++j) {
            cin >> map[i][j];
            if (i != j && map[i][j] == 0) map[i][j] = inf;
        }
    }
    floyd();
    int ans;
    while (l <= r) {
        mid = (l + r) / 2;
        buildmap(mid);
        if (dinic() == c) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout << ans << endl;
    return 0;
}