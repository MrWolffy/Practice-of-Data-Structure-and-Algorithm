#include <iostream>
using namespace std;

const int MAXN = 10000;
int ans[MAXN] = {0}, pre[MAXN] = {0}, n;
struct {
    int l, r;
    int len;
} node[MAXN * 4];

void buildtree(int id, int l, int r) {
    node[id].l = l;
    node[id].r = r;
    node[id].len = r - l + 1;
    int mid = (l + r) / 2;
    if (l != r) {
        buildtree(id * 2, l, mid);
        buildtree(id * 2 + 1, mid + 1, r);
    }
}

int query(int id, int num) {
    node[id].len -= 1;
    if (node[id].l == node[id].r) return node[id].l;
    if (node[id * 2].len < num)
        return query((id * 2) + 1, num - node[id * 2].len);
    else return query(id * 2, num);
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &pre[i]);
    }
    buildtree(1, 1, n);
    for (int i = n; i >= 1; --i) {
        ans[i] = query(1, pre[i] + 1);
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}