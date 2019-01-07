#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 100010;
struct CNode {
	int l, r;
	int minv, maxv;
} tree[4 * maxn];
int maxv = -inf, minv = inf;

void BuildTree(int root, int l, int r) {
	tree[root].l = l;
	tree[root].r = r;
	tree[root].minv = inf;
	tree[root].maxv = -inf;
	if (l != r) {
		BuildTree(2 * root + 1, l, (l + r) / 2);
		BuildTree(2 * root + 2, (l + r) / 2 + 1, r);
	}
}
void Insert(int root, int i, int v) {
	tree[root].minv = min(tree[root].minv, v);
	tree[root].maxv = max(tree[root].maxv, v);
	if (tree[root].l == tree[root].r) return;
	if (i <= (tree[root].l + tree[root].r) / 2) 
		Insert(2 * root + 1, i, v);
	else Insert(2 * root + 2, i, v);
}
void Query(int root, int s, int e) {
	if (tree[root].minv >= minv && tree[root].maxv <= maxv) return;
	if (tree[root].l == s && tree[root].r == e) {
		minv = min(tree[root].minv, minv);
		maxv = max(tree[root].maxv, maxv);
		return;
	}
	int mid = (tree[root].l + tree[root].r) / 2;
	if (e <= mid) Query(2 * root + 1, s, e);
	else if (mid < s) Query(2 * root + 2, s, e);
	else {
		Query(2 * root + 1, s, mid);
		Query(2 * root + 2, mid + 1, e);
	}
}


int main() {
	int m, n, p, q; char ch;
	cin >> n >> m;
	BuildTree(0, 1, n);
	for (int i = 1; i <= n; ++i) {
		cin >> p;
		Insert(0, i, p);
	}
	while (m--) {
		cin >> ch >> p >> q;
		if (ch == 'Q') {
			minv = inf; maxv = -inf;
			Query(0, p, q);
			cout << maxv << " " << minv << endl;
		}
		else if (ch == 'U') Insert(0, p, q);
	}
	return 0;
}


/*
测试数据：
input:
6 6
1 7 3 4 2 5
Q 1 5
Q 4 6
Q 2 2
U 3 2
U 4 8
Q 1 4
output:
1 7
2 5
7 7
1 8
*/