#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

struct node {
    node *child[2], *prev;
    bool bad, visited;
    node() {
        memset(child, 0, sizeof(child));
        bad = visited = false;
        prev = NULL;
    }
} tree[30010];
int nodecount = 0;

void buildtree(string s) {
    node *p = tree + 1;
    for (int i = 0; i < s.length(); ++i) {
        if (!p -> child[s[i] - '0']) {
            p -> child[s[i] - '0'] = tree + nodecount;
            nodecount++;
        }
        p = p -> child[s[i] - '0'];
    }
    p -> bad = true;
}

void buildmap() {
    tree[0].child[0] = tree[0].child[1] = tree + 1;
    tree[1].prev = tree;
    deque<node *> qu;
    qu.push_back(tree + 1);
    while (!qu.empty()) {
        node *root = qu.front();
        qu.pop_front();
        for (int i = 0; i < 2; ++i) {
            node *p = root -> child[i];
            node *prev = root -> prev;
            while (!prev -> child[i]) prev = prev -> prev;
            if (p) {
                p -> prev = prev -> child[i];
                if (p -> prev -> bad) p -> bad = true;
                qu.push_back(p);
            }
            else root -> child[i] = prev -> child[i];
        }
    }
}

bool dfs(node *root) {
    if (root -> visited) return true;
    root -> visited = true;
    for (int i = 0; i < 2; ++i) {
        if (root -> child[i] && !root -> child[i] -> bad) {
            if (dfs(root -> child[i])) return true;
        }
    }
    root -> visited = false;
    return false;
}

int main() {
    int n; string s;
    nodecount = 2;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        buildtree(s);
    }
    buildmap();
    if (dfs(tree + 1)) cout << "TAK" << endl;
    else cout << "NIE" << endl;
}