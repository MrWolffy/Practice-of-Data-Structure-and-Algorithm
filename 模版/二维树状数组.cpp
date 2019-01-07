#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 5010;
int a[maxn][maxn], c[maxn][maxn], su[maxn][maxn] = {0}, n, m;

int lowbit(int k) {
	return k & (-k);
}
int sum(int k, int l) {
	int ans = 0;
	for (int i = k; i > 0; i -= lowbit(i)) {
		for (int j = l; j > 0; j -= lowbit(j)) {
			ans += c[i][j];
		}
	}
	return ans;
}
void update(int k, int l, int v) {
	int change = v - a[k][l];
	for (int i = k; i <= n; i += lowbit(i)) {
		for (int j = l; j <= m; j += lowbit(j)) {
			c[i][j] += change;
		}
	}
	a[k][l] = v;
}

int main() {
	int k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			su[i][j] = su[i][j-1] + su[i-1][j] - su[i-1][j-1] + a[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			c[i][j] = su[i][j] - su[i-lowbit(i)][j] - su[i][j-lowbit(j)] + su[i-lowbit(i)][j-lowbit(j)];
		}
	}
	while (k--) {
		int a, b, c, d; char ch;
		cin >> ch;
		if (ch == 'U') {
			cin >> a >> b >> c;
			update(a, b, c);
		}
		else if (ch == 'Q') {
			cin >> a >> b >> c >> d;
			cout << sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1) << endl;
		}
	}
	return 0;
}

/*
测试数据：
input:
4 4 5
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
U 2 3 3
Q 1 1 3 3
U 2 2 2
U 2 3 2
Q 2 2 3 4
output:
3
4
*/