#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
using namespace std;

const int maxn = 100010;
const int maxm = 26;
struct CNode {
	CNode *child[maxm];
	vector<int> danger;
	CNode *prev;
	CNode() {
		memset(child, 0, sizeof(child));
		prev = NULL;
	}
} tree[maxn];
int nodescount = 2;
bool visited[maxn];

void Insert(CNode *root, string s, int idx) {
	CNode *p = root;
	for (int i = 0; i < s.length(); ++i) {
		if (p -> child[s[i] - 'a'] == NULL) {
			p -> child[s[i] - 'a'] = tree + nodescount;
			nodescount++;
		}
		p = p -> child[s[i] - 'a'];
	}
	p -> danger.push_back(idx);
}
void BuildDfa() {
	for (int i = 0; i < maxm; ++i) tree[0].child[i] = tree + 1;
	tree[0].prev = NULL;
	tree[1].prev = tree;
	deque<CNode *> q;
	q.push_back(tree + 1);
	while (!q.empty()) {
		CNode *proot = q.front();
		q.pop_front();
		for (int i = 0; i < maxm; ++i) {
			CNode *p = proot -> child[i];
			if (p) {
				CNode *pprev = proot -> prev;
				while (pprev -> child[i] == NULL)
					pprev = pprev -> prev;
				p -> prev = pprev -> child[i];
				if (!p -> prev -> danger.empty()) {
					p -> danger.insert(p -> danger.end(), p -> prev -> danger.begin(), p -> prev -> danger.end());
				}
				q.push_back(p);
			}
		}
	}
}
bool searchDfa(string s) {
	CNode *p = tree + 1;
	bool flag = false;
	for (int i = 0; i < s.length(); ++i) {
		while (p -> child[s[i] - 'a'] == NULL)
			p = p -> prev;
		p = p -> child[s[i] - 'a'];
		if (!p -> danger.empty()) {
			flag = true;
			for (int j = 0; j < p -> danger.size(); ++j) 
				visited[p -> danger[j]] = 1;
		}
	}
	return flag;
}

int main() {
	int m, n; string str;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> str;
		Insert(tree + 1, str, i);
	}
	BuildDfa();
	cin >> m;
	for (int i = 0; i < m; ++i) {
		memset(visited, 0, sizeof(visited));
		cin >> str;
		if (searchDfa(str)) {
			for (int i = 0; i < n; ++i) {
				if (visited[i]) cout << i << " ";
			}
			cout << endl;
		}
		else cout << "no" << endl;
	}
	return 0;
}


/*
测试数据：
input:
5
abc
bc
bcd
def
gh
2
abcd
ak
output:
0 1 2
no
*/