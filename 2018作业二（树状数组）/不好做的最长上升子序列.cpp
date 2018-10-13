#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 300010;
struct t{
    int val;
    int pos;
    bool operator< (t b) const {
        if (val != b.val) return val < b.val;
        return pos > b.pos;
    }
} a[MAX];
int lis[MAX] = {0}, c[MAX] = {0}, n;

int lowbit(int x) {
    return x & (-x);
}

int query(int k) {
    int ans = 0;
    while (k > 0) {
        ans = max(ans, c[k]);
        k -= lowbit(k);
    }
    return ans;
}

void update(int k, int change) {
    lis[k] = change;
    while (k <= n) {
        c[k] = max(c[k], change);
        k += lowbit(k);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        scanf("%d", &a[i].val);
        a[i].pos = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        update(a[i].pos, query(a[i].pos) + 1);
    }
    printf("%d", *max_element(c + 1, c + n + 1));
    return 0;
}