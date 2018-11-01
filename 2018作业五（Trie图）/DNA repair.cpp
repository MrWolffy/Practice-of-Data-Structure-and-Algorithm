#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

struct node {
    node *child[4], *prev;
    bool danger;
    node () {
        memset(child, 0, sizeof(child));
        danger = false;
        prev = NULL;
    }
} tree[2000];
int dict[256] = {0}, dp[1010][1010] = {0};
const int inf = 0xffffff;
int nodecount = 0;
string s;

void buildtree(string s) {
    node *p = tree + 1;
    for (int i = 0; i < s.length(); ++i) {
        if (!p -> child[dict[s[i]]]) {
            p -> child[dict[s[i]]] = tree + nodecount;
            nodecount++;
        }
        p = p -> child[dict[s[i]]];
    }
    p -> danger = true;
}

void buildmap() {
    for (int i = 0; i < 4; ++i) tree[0].child[i] = tree + 1;
    tree[1].prev = tree;
    queue<node *> qu;
    qu.push(tree + 1);
    while (!qu.empty()) {
        node *root = qu.front();
        qu.pop();
        for (int i = 0; i < 4; ++i) {
            node *p = root -> child[i];
            if (p) {
                node *prev = root -> prev;
                while (!prev -> child[i]) prev = prev -> prev;
                p -> prev = prev -> child[i];
                if (p -> prev -> danger) p -> danger = true;
                qu.push(p);
            }
        }
    }
}

int Son(int j, int k) {
    node *p = tree + j;
    while (!p -> child[k]) {
        p = p -> prev;
    }
    if (p -> child[k] -> danger) return inf;
    return p -> child[k] - tree;
}

int main() {
    dict['G'] = 1; dict['C'] = 2; dict['T'] = 3;
    int n, t = 1;
    while (1) {
        cin >> n;
        if (n == 0) return 0;
        nodecount = 2;
        memset(tree, 0, sizeof(tree));
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            cin >> s;
            buildtree(s);
        }
        buildmap();
        cin >> s;
        int l = s.length();
        for (int i = 0; i <= l; ++i) {
            for (int j = 0; j <= nodecount; ++j) {
                dp[i][j] = inf;
            }
        }
        dp[0][1] = 0;
        for (int i = 0; i < l; ++i) {
            for (int j = 1; j < nodecount; ++j) {
                for (int k = 0; k < 4; ++k) {
                    int son = Son(j, k);
                    if (son == inf) continue;
                    dp[i+1][son] = min(dp[i+1][son], dp[i][j] + (k != dict[s[i]]));
                }
            }
        }
        int mincount = inf;
        for (int j = 1; j < nodecount; ++j) {
            if (!tree[j].danger)
                mincount = min(mincount, dp[l][j]);
        }
        cout << "Case " << t << ": ";
        t++;
        if (mincount != inf) cout << mincount << endl;
        else cout << -1 << endl;
    }
}