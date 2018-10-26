#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 10010;
int b[MAXN], e[MAXN], seg[MAXN * 4];
struct {
    int l, r;
    bool cover;
} node[MAXN * 16];
map<int, int> mp;
int ans = 0;

void buildtree(int id, int l, int r) {
    node[id].cover = false;
    node[id].l = l;
    node[id].r = r;
    if (l != r) {
        int mid = (l + r) / 2;
        buildtree(id * 2 + 1, l, mid);
        buildtree(id * 2 + 2, mid + 1, r);
    }
}

bool update(int id, int l, int r) {
    int ll = node[id].l, rr = node[id].r;
    if (node[id].cover && ll <= l && rr >= r) return false;
    else if (ll == l && rr == r) {
        node[id].cover = true;
        return true;
    }
    int mid = (ll + rr) / 2;
    bool f1, f2, f3, f4;
    if (mid >= r) f1 = update(id * 2 + 1, l, r);
    else if (mid < l) f2 = update(id * 2 + 2, l, r);
    else {
        f3 = update(id * 2 + 1, l, mid);
        f4 = update(id * 2 + 2, mid + 1, r);
    }
    node[id].cover = node[id * 2 + 1].cover && node[id * 2 + 2].cover;
    if (mid >= r) return f1;
    else if (mid < l) return f2;
    else return f3 || f4;
}

int main() {
    int c, n, t1, t2;
    scanf("%d", &c);
    while (c--) {
        ans = 0;
        mp.clear();
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &t1, &t2);
            b[i] = t1; e[i] = t2;
            seg[i * 4] = t1; seg[i * 4 + 1] = t1 - 1;
            seg[i * 4 + 2] = t2; seg[i * 4 + 3] = t2 + 1;
        }
        sort(seg, seg + n * 4);
        int size = unique(seg, seg + n * 4) - seg;
        for (int i = 0; i < size; ++i) mp.insert(make_pair(seg[i], i));
        buildtree(0, 0, size);
        for (int i = n - 1; i >= 0; --i) {
            if (update(0, mp[b[i]], mp[e[i]])) ++ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}