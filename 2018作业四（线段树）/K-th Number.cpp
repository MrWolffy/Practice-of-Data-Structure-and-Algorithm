#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 100010;
struct {
    int l, r;
    vector<int> lst;
} node[maxn * 4];
int a[maxn];

void buildtree(int id, int l, int r) {
    node[id].l = l; node[id].r = r;
    if (l == r) {
        node[id].lst.push_back(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    buildtree(id * 2 + 1, l, mid);
    buildtree(id * 2 + 2, mid + 1, r);
    node[id].lst.resize(r - l + 1);
    merge(node[id * 2 + 1].lst.begin(), node[id * 2 + 1].lst.end(),
          node[id * 2 + 2].lst.begin(), node[id * 2 + 2].lst.end(),
          node[id].lst.begin());
}

int query(int id, int l, int r, int t) {
    if (node[id].l == l && r == node[id].r)
        return upper_bound(node[id].lst.begin(), node[id].lst.end(), t) - node[id].lst.begin();
    int mid = (node[id].l + node[id].r) / 2;
    if (mid >= r) return query(id * 2 + 1, l, r, t);
    else if (mid < l) return query(id * 2 + 2, l, r, t);
    else return query(id * 2 + 1, l, mid, t) + query(id * 2 + 2, mid + 1, r, t);
}

int search(int beg, int end, int k) {
    int low = -1000000000 - 1, high = 1000000000 + 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        int num = query(0, beg, end, mid);
        if (k <= num) high = mid;
        else low = mid + 1;
    }
    return low;
}

int main() {
    int m, n;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    buildtree(0, 0, n - 1);
    while (m--) {
        int i, j, k;
        scanf("%d%d%d", &i, &j, &k);
        printf("%d\n", search(i - 1, j - 1, k));
    }
}