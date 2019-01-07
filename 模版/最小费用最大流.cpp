#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 1010;
int n, m;
struct edge {
	int e, w, t;
	edge(int ee, int ww, int tt): e(ee), w(ww), t(tt) {}
	edge() {}
};
vector<edge> g[maxn];
int dist[maxn];
bool visited[maxn];
vector<int> path[maxn];

bool spfa(int v, int w) {
	memset(visited, 0, sizeof(visited));
	for (int i = 1; i <= n; ++i) path[i].clear();
	for (int i = 1; i <= n; ++i) dist[i] = inf;
	dist[v] = 0;
	deque<int> q; 
	q.push_back(v);
	visited[v] = true;
	while (!q.empty()) {
		int s = q.front();
		q.pop_front();
		visited[s] = false;
		for (int i = 0; i < g[s].size(); ++i) {
			if (g[s][i].w <= 0) continue;
			int e = g[s][i].e;
			if (dist[s] != inf && dist[e] > dist[s] + g[s][i].t) {
				dist[e] = dist[s] + g[s][i].t;
				path[e] = path[s];
				path[e].push_back(i);
				if (!visited[e]) {
					q.push_back(e); 
					visited[e] = true;
				}
			}
		}
	}
	return (dist[w] != inf);
}

int main() {
	int p, q, inc = 0, f = 0;
	cin >> n >> m >> p >> q;
	int s, e, w, t;
	for (int i = 0; i < m; ++i) {
		cin >> s >> e >> w >> t;
		g[s].push_back(edge(e, w, t));
		g[e].push_back(edge(s, w, t));
	}
	while (spfa(p, q)) {
		++inc;
		f += dist[q];
		s = p;
		for (int i = 0; i < path[q].size(); ++i) {
			e = g[s][path[q][i]].e;
			g[s][path[q][i]].w--;
			g[e].push_back(edge(s, 1, -g[s][path[q][i]].t));
			s = e;
		}
	}
	cout << inc << " " << f << endl;
	return 0;
}

/*
测试数据：
input:
10 15 1 10
7 1 1 13784
6 1 1 31692
4 9 1 16318
5 10 1 521
10 3 1 16420
5 2 1 11817
6 4 1 29070
8 5 1 13614
2 9 1 17168
8 1 1 19260
1 2 1 6076
2 3 1 1038
3 6 1 12917
2 6 1 17815
10 4 1 26493
output:
3 144184
*/