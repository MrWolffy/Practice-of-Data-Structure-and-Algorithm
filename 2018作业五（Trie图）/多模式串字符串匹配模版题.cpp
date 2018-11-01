#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

struct trienode {
    trienode *child[26];
    bool end;
    trienode *before;
    trienode() {
        memset(child, 0, sizeof(child));
        before = NULL;
        end = false;
    }
};
trienode root1, root;

void buildtree(string s) {
    trienode *p = &root1;
    for (int i = 0; i < s.length(); ++i) {
        if (p -> child[s[i] - 'a'] == NULL) {
            p -> child[s[i] - 'a'] = new trienode;
        }
        p = p -> child[s[i] - 'a'];
        if (i == s.length() - 1) p -> end = true;
    }
}

void buildmap() {
    root1.before = &root;
    for (int i = 0; i < 26; ++i) root.child[i] = &root1;
    deque<trienode *> qu;
    qu.push_back(&root1);
    while (!qu.empty()) {
        trienode *top = qu.front();
        qu.pop_front();
        for (int i = 0; i < 26; ++i) {
            if (top -> child[i]) {
                trienode *q = top -> before;
                while (q -> child[i] == NULL) {
                    q = q -> before;
                }
                top -> child[i] -> before = q -> child[i];
                if (q -> child[i] -> end) top -> child[i] -> end = true;
            }
        }
        for (int i = 0; i < 26; ++i) {
            if (top -> child[i]) qu.push_back(top -> child[i]);
        }
    }
}

bool match(string s) {
    trienode *p = &root1;
    for (int i = 0; i < s.length(); ++i) {
        while (p -> child[s[i] - 'a'] == NULL) {
            p = p -> before;
        }
        if (p -> child[s[i] - 'a']) {
            p = p -> child[s[i] - 'a'];
            if (p -> end) return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    string s;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        buildtree(s);
    }
    buildmap();
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> s;
        if (match(s)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}