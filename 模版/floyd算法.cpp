#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 1010;
int dist[maxn][maxn], cost[maxn][maxn], n, m;
vector<int> path[maxn][maxn];

void floyd() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dist[i][j] = cost[i][j];
			if (dist[i][j] < inf) {
				path[i][j].push_back(i);
				path[i][j].push_back(j);
			}
		}
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k];
					path[i][j].insert(path[i][j].end(), path[k][j].begin() + 1, path[k][j].end());
				}
			}
		}
	}
}

int main() {
	int p, q;
	cin >> n >> m >> p >> q;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			cost[i][j] = inf;
		cost[i][i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		int s, e, t;
		cin >> s >> e >> t;
		cost[s][e] = min(cost[s][e], t);
	}
	floyd();
	cout << dist[p][q] << endl;
	for (int i = 0; i < path[p][q].size(); ++i)
		cout << path[p][q][i] << " ";
	cout << endl;
	return 0;
}


/*
测试数据：
input:
3 5 1 3
1 2 5
2 1 5
1 3 4
3 1 4
2 3 -2
output:
3
1 2 3
*/