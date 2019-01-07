#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 1010;
int n, m;
struct edge {
	int e, w;
	edge(int ee, int ww): e(ee), w(ww) {}
	edge() {}
};
vector<edge> g[maxn];
int updateTimes[maxn];
int dist[maxn];
bool visited[maxn];
vector<int> path[maxn];

bool spfa(int v) {
	memset(updateTimes, 0, sizeof(updateTimes));
	memset(visited, 0, sizeof(visited));
	for (int i = 1; i <= n; ++i) path[i].clear();
	path[v].push_back(v);
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
			int e = g[s][i].e;
			if (dist[s] != inf && dist[e] > dist[s] + g[s][i].w) {
				dist[e] = dist[s] + g[s][i].w;
				path[e] = path[s];
				path[e].push_back(e);
				if (!visited[e]) {
					q.push_back(e); 
					visited[e] = true;
				}
				++updateTimes[e];
				if (updateTimes[e] >= n) return false;
			}
		}
	}
	return true;
}

int main() {
	int p, q;
	cin >> n >> m >> p >> q;
	for (int i = 1; i < maxn; ++i) g[i].clear();
	int s, e, t;
	for (int i = 0; i < m; ++i) {
		cin >> s >> e >> t;
		g[s].push_back(edge(e,t));
	}
	if (spfa(p)) {
		cout << dist[q] << endl;
		for (int i = 0; i < path[q].size(); ++i) cout << path[q][i] << " ";
		cout << endl;
	}
	else cout << "no" << endl;
	return 0;
}

/*测试数据：
case 1
input:
3 5 1 3
1 2 5
2 1 5
1 3 4
3 1 4
2 3 -2
output:
3
case 2
input:
3 5 1 3
1 2 3
2 1 3
2 3 4
3 2 4
2 3 -8
output:
no
*/