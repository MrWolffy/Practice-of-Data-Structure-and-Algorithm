#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 100010;
int parent[maxn];

int GetRoot(int a) {
	if (parent[a] != a)
		parent[a] = GetRoot(parent[a]);
	return parent[a];
}
void Merge(int a, int b) {
	parent[GetRoot(b)] = GetRoot(a);
}
bool Query(int a, int b) {
	return GetRoot(a) == GetRoot(b);
}

int main() {
	memset(parent, 0, sizeof(parent));
	int n, m, a, b; char c;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) parent[i] = i;
	while (m--) {
		cin >> c >> a >> b;
		if (c == 'A') Merge(a, b);
		else if (c == 'Q') cout << int(Query(a, b)) << endl;
	}
	return 0;
}


/*测试数据：
input:
5 6
A 1 2
Q 1 2
Q 1 3
A 2 4
A 2 5
Q 4 5
output:
1
0
1
*/