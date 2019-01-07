#include <iostream>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 1010;
struct edge {
	int s, e, w;
	edge(int ss, int ee, int ww): s(ss), e(ee), w(ww) {}
	edge() {}
};
vector<edge> edges;
int dist[maxn], n, m;

bool bellman_ford(int v) {
	for (int i = 1; i <= n; ++i) dist[i] = inf;
	dist[v] = 0;
	for (int k = 1; k < n; ++k) {
		bool flag = false;
		for (int i = 0; i < edges.size(); ++i) {
			int s = edges[i].s;
			int e = edges[i].e;
			if (dist[s] != inf && dist[s] + edges[i].w < dist[e]) {
				dist[e] = dist[s] + edges[i].w;
				flag = true;
			}
		}
		if (!flag) break;
	}
	for (int i = 0; i < edges.size(); ++i) {
		int s = edges[i].s;
		int e = edges[i].e;
		if (dist[s] + edges[i].w < dist[e])
			return true;
	}
	return false;
}

int main() {
	int p, q;
	cin >> n >> m >> p >> q;
	for (int i = 0; i < m; ++i) {
		int s, e, t;
		cin >> s >> e >> t;
		edges.push_back(edge(s, e, t));
	}
	if (bellman_ford(p)) cout << "no" << endl;
	else cout << dist[q] << endl;
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