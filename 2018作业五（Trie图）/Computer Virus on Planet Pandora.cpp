#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct trienode {
    trienode *child[26];
    vector<string> end;
    trienode *before;
    trienode() {
        memset(child, 0, sizeof(child));
        before = NULL;
        end.clear();
    }
};
trienode root1, root;
int matchcount;
set<string> virus;

void buildtree(string s) {
    trienode *p = &root1;
    for (int i = 0; i < s.length(); ++i) {
        if (p -> child[s[i] - 'A'] == NULL) {
            p -> child[s[i] - 'A'] = new trienode;
        }
        p = p -> child[s[i] - 'A'];
        if (i == s.length() - 1) (p -> end).push_back(s);
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
                while (q -> child[i] == NULL) q = q -> before;
                top -> child[i] -> before = q -> child[i];
                if (!(q -> child[i] -> end).empty()) {
                    (top -> child[i] -> end).insert((top -> child[i] -> end).end(), (q -> child[i] -> end).begin(), (q -> child[i] -> end).end());
                }
            }
        }
        for (int i = 0; i < 26; ++i) {
            if (top -> child[i]) qu.push_back(top -> child[i]);
        }
    }
}

void match(vector<char> s) {
    trienode *p = &root1;
    for (int i = 0; i < s.size(); ++i) {
        while (p -> child[s[i] - 'A'] == NULL) {
            p = p -> before;
        }
        if (p -> child[s[i] - 'A']) {
            p = p -> child[s[i] - 'A'];
            if (!(p -> end).empty()) {
                for (auto i = (p -> end).begin(); i < (p -> end).end(); ++i) {
                    if (virus.find(*i) != virus.end()) {
                        matchcount++;
                        virus.erase(*i);
                    }
                }
                (p -> end).clear();
            }
        }
    }
}

int main() {
    int n, t;
    string s;
    cin >> t;
    while (t--) {
        matchcount = 0; root1 = trienode(); root = trienode();
        virus.clear();
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> s;
            virus.insert(s);
            buildtree(s);
        }
        buildmap();
        cin >> s;
        vector<char> model;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '[') {
                int count = 0, j = i + 1;
                for (; s[j] >= '0' && s[j] <= '9'; ++j) {
                    count = count * 10 + s[j] - '0';
                }
                for (int k = 0; k < count; ++k) model.push_back(s[j]);
                i = j + 1;
                continue;
            }
            else model.push_back(s[i]);
        }
        match(model);
        reverse(model.begin(), model.end());
        match(model);
        cout << matchcount << endl;
    }
    return 0;
}