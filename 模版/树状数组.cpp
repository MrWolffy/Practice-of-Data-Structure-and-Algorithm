#include <iostream>
using namespace std;

const int maxn = 100010;
int a[maxn], c[maxn], n;

int lowbit(int x) {
	return x & (-x);
}
int sum(int k) {
	int ans = 0;
	while (k > 0) {
		ans += c[k];
		k -= lowbit(k);
	}
	return ans;
}
void update(int k, int v) {
	int change = v - a[k];
	a[k] += change;
	while (k <= n) {
		c[k] += change;
		k += lowbit(k);
	}
}

int main() {
	int m, p, q; char ch;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	int su[maxn] = {0};
	for (int i = 1; i <= n; ++i) su[i] = su[i-1] + a[i];
	for (int i = 1; i <= n; ++i) c[i] = su[i] - su[i - lowbit(i)];
	while (m--) {
		cin >> ch >> p >> q;
		if (ch == 'Q') cout << sum(q) - sum(p - 1) << endl;
		else if (ch == 'U') update(p, q);
	}
	return 0;
}


/*测试数据：
input:
5 6
1 1 1 1 1
Q 1 5
Q 3 4
U 2 5
U 3 2
U 4 3
Q 1 4
output:
5
2
11
*/
