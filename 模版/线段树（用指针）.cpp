#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100010;
struct node {
	int l, r;
	node *left, *right;
	long long sum;
	long long inc;
} tree[4 * maxn];
int nodescount = 0;

void BuildTree(node *root, int l, int r) {
	root -> l = l;
	root -> r = r;
	root -> sum = 0;
	root -> inc = 0;
	if (l != r) {
		nodescount++;
		root -> left = tree + nodescount;
		nodescount++;
		root -> right = tree + nodescount;
		BuildTree(root -> left, l, (l + r) / 2);
		BuildTree(root -> right, (l + r) / 2 + 1, r);
	}
}
void Insert(node *root, int i, int v) {
	root -> sum += v;
	if (root -> l == root -> r) {
		return;
	}
	if (i <= (root -> l + root -> r) / 2) 
		Insert(root -> left, i, v);
	else Insert(root -> right, i, v);
}
void Add(node *root, int s, int e, long long c) {
	if (root -> l == s && root -> r == e) {
		root -> inc += c;
		return;
	}
	root -> sum += c * (e - s + 1);
	int mid = (root -> l + root -> r) / 2;
	if (e <= mid) Add(root -> left, s, e, c);
	else if (s > mid) Add(root -> right, s, e, c);
	else {
		Add(root -> left, s, mid, c);
		Add(root -> right, mid + 1, e, c);
	}
}
long long Query(node *root, int s, int e) {
	if (root -> l == s && root -> r == e) {
		return root -> sum + root -> inc * (e - s + 1);
	}
	root -> sum += root -> inc * (root -> r - root -> l + 1);
	root -> left -> inc += root -> inc;
	root -> right -> inc += root -> inc;
	root -> inc = 0;
	int mid = (root -> l + root -> r) / 2;
	if (e <= mid) return Query(root -> left, s, e);
	else if (mid < s) return Query(root -> right, s, e);
	else return Query(root -> left, s, mid) + Query(root -> right, mid + 1, e);
}


int main() {
	int m, n, a, b, c; char ch;
	cin >> n >> m;
	BuildTree(tree, 1, n);
	for (int i = 1; i <= n; ++i) {
		cin >> a;
		Insert(tree, i, a);
	}
	while (m--) {
		cin >> ch;
		if (ch == 'Q') {
			cin >> a >> b;
			cout << Query(tree, a, b) << endl;
		}
		else if (ch == 'C') {
			cin >> a >> b >> c;
			Add(tree, a, b, c);
		}
	}
	return 0;
}

/*
测试数据：
input:
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4
output:
4
55
9
15
*/
// Q 2 4 -> 15