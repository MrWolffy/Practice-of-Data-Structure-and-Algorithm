#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1010;
bool g[maxn][maxn];
int dfn[maxn] = {0}, low[maxn] = {0}, t = 0, n;
deque<int> stk;

void tarjan(int u) {
	if (dfn[u]) return;
	dfn[u] = low[u] = ++t;
	stk.push_back(u);
	for (int v = 1; v <= n; ++v) {
		if (!g[u][v]) continue;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (find(stk.begin(), stk.end(), v) != stk.end())
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int w = -1;
		while (u != w) {
			w = stk.back();
			cout << w << " ";
			stk.pop_back();
		}
		cout << endl;
	}
}

int main() {
	int m, u, v;
	cin >> n >> m;
	memset(g, 0, sizeof(g));
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		g[u][v] = true;
	}
	// tarjan(1);
	for (int i = 1; i <= n; ++i) tarjan(i);
	return 0;
}


/*测试数据：
case 1
input:
7 9
1 2
1 6
2 3
3 4
3 5
4 5
4 2
6 7
7 1
output:
5
4 3 2
7 6 1
case 2
input:
2 0
output:
1
2
*/