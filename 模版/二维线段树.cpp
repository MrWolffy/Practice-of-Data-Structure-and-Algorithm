#include <iostream>
using namespace std;

const int maxn = 1010;
struct node {
	node *xb, *xn, *db, *dn;
	int x1, y1, x2, y2; // x1 < x2, y1 < y2
	long long sum, inc;
	int midx() {
		return (x1 + x2) / 2;
	}
	int midy() {
		return (y1 + y2) / 2;
	}
} tree[16 * maxn * maxn];
int nodescount = 1;
int A[maxn][maxn];

void buildtree(node *root, int x1, int x2, int y1, int y2) {
	root -> x1 = x1; root -> x2 = x2;
	root -> y1 = y1; root -> y2 = y2;
	root -> sum = 0; root -> inc = 0;
	if (x1 != x2 && y1 != y2) {
		int midx = root -> midx(), midy = root -> midy();
		root -> xb = tree + nodescount; nodescount++;
		root -> xn = tree + nodescount; nodescount++;
		root -> db = tree + nodescount; nodescount++;
		root -> dn = tree + nodescount; nodescount++;
		buildtree(root -> xb, x1, midx, y1, midy);
		buildtree(root -> xn, x1, midx, midy + 1, y2);
		buildtree(root -> db, midx + 1, x2, y1, midy);
		buildtree(root -> dn, midx + 1, x2, midy + 1, y2);
	}
}
void insert(node *root, int x, int y, int v) {
	root -> sum += v;
	if (root -> x1 == root -> x2 && root -> y1 == root -> y2) return;
	int midx = root -> midx(), midy = root -> midy();
	if (x <= midx && y <= midy) insert(root -> xb, x, y, v);
	else if (x <= midx && y > midy) insert(root -> xn, x, y, v);
	else if (x > midx && y <= midy) insert(root -> db, x, y, v);
	else insert(root -> dn, x, y, v);
}
void insert(node *root, int x1, int x2, int y1, int y2, int v) {
	if (root -> x1 == x1 && root -> x2 == x2 &&
		root -> y1 == y1 && root -> y2 == y2) {
		root -> inc += v;
		return;
	}
	root -> sum += v * (x2 - x1 + 1) * (y2 - y1 + 1);
	int midx = root -> midx(), midy = root -> midy();
	if (x1 <= midx && y1 <= midy) insert(root -> xb, x1, min(x2, midx), y1, min(y2, midy), v);
	if (x1 <= midx && y2 > midy) insert(root -> xn, x1, min(x2, midx), max(y1, midy), y2, v);
	if (x2 > midx && y1 <= midy) insert(root -> db, max(x1, midx), x2, y1, min(y2, midy), v);
	if (x2 > midx && y2 > midy) insert(root -> dn, max(x1, midx), x2, max(y1, midy), y2, v);
}
long long query(node *root, int x1, int x2, int y1, int y2) {
	if (root -> x1 == x1 && root -> x2 == x2 &&
		root -> y1 == y1 && root -> y2 == y2) {
		return root -> sum + root -> inc * (x2 - x1 + 1) * (y2 - y1 + 1);
	}
	root -> sum += root -> inc * (root -> y2 - root -> y1 + 1) * (root -> x2 - root -> x1 + 1);
	root -> xb -> inc += root -> inc;
	root -> xn -> inc += root -> inc;
	root -> db -> inc += root -> inc;
	root -> dn -> inc += root -> inc;
	root -> inc = 0;
	int midx = root -> midx(), midy = root -> midy();
	int ans = 0;
	if (x1 <= midx && y1 <= midy) ans += query(root -> xb, x1, min(x2, midx), y1, min(y2, midy));
	if (x1 <= midx && y2 > midy) ans += query(root -> xn, x1, min(x2, midx), max(y1, midy + 1), y2);
	if (x2 > midx && y1 <= midy) ans += query(root -> db, max(x1, midx + 1), x2, y1, min(y2, midy));
	if (x2 > midx && y2 > midy) ans += query(root -> dn, max(x1, midx + 1), x2, max(y1, midy + 1), y2);
	return ans;
}

int main() {
	int n, m, w;
	cin >> n >> m >> w;
	buildtree(tree, 1, n, 1, m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int p; cin >> p;
			insert(tree, i, j, p);
			A[i][j] = p;
		}
	}
	while (w--) {
		int a, b, c, d; char ch;
		cin >> ch;
		if (ch == 'U') {
			cin >> a >> b >> c;
			insert(tree, a, b, c - A[a][b]);
			A[a][b] = c;
		}
		else if (ch == 'Q') {
			cin >> a >> b >> c >> d;
			cout << query(tree, a, c, b, d) << endl;
		}
	}
	return 0;
}