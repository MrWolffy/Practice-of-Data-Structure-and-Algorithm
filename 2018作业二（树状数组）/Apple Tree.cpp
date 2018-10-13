#include <iostream>
#include <vector>
using namespace std;

const int MAX = 100010;
int a[MAX], c[MAX], n;
int b[MAX], e[MAX], t = 0;
bool visited[MAX] = {0};
vector<vector<int> > mp;

int lowbit(int x) {
    return x & (-x);
}

void init() {
    int sum[MAX] = {0};
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i-1] + a[i];
    }
    for (int i = 1; i <= n; ++i) {
        c[i] = sum[i] - sum[i - lowbit(i)];
    }
}

int sum(int k) {
    int ans = 0;
    while (k > 0) {
        ans += c[k];
        k = k - lowbit(k);
    }
    return ans;
}

void update(int k, int ne) {
    int change = ne - a[k];
    a[k] = ne;
    while (k <= n) {
        c[k] += change;
        k += lowbit(k);
    }
}

void dfs(int k) {
    if (visited[k]) return;
    visited[k] = true;
    b[k] = ++t;
    for (auto i = mp[k].begin(); i < mp[k].end(); ++i) {
        if (!visited[*i]) {
            dfs(*i);
        }
    }
    e[k] = t;
}

int main() {
    int u, v, m, x;
    char ch;
    cin >> n;
    for (int i = 0; i <= n + 1; ++i) {
        a[i] = 1;
        mp.push_back(vector<int>());
    }
    init();
    for (int i = 1; i < n; ++i) {
        cin >> u >> v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }
    dfs(1);
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> ch >> x;
        if (ch == 'Q') {
            cout << sum(e[x]) - sum(b[x] - 1) << endl;
        }
        else if (ch == 'C') {
            if (a[b[x]] == 1) update(b[x], 0);
            else if (a[b[x]] == 0) update(b[x], 1);
        }
    }
    return 0;
}