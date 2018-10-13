#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1050;
int c[MAX][MAX] = {0}, n;

int lowbit(int x) {
    return x & (-x);
}

int sum(int k, int l) {
    int ans = 0;
    for (int i = k; i > 0; i -= lowbit(i)) {
        for (int j = l; j  > 0; j -= lowbit(j)) {
            ans += c[i][j];
        }
    }
    return ans;
}

void update(int k, int l, int change) {
    for (int i = k; i <= n; i += lowbit(i)) {
        for (int j = l; j <= n; j += lowbit(j)) {
            c[i][j] += change;
        }
    }
}

int main() {
    int op, x, y, a, l, b, r, t;
    while (1) {
        cin >> op;
        if (op == 0) {
            cin >> n;
        }
        else if (op == 1) {
            cin >> x >> y >> a;
            update(x + 1, y + 1, a);
        }
        else if (op == 2) {
            cin >> l >> b >> r >> t;
            int ans = sum(r + 1, t + 1) - sum(l, t + 1) - sum(r + 1, b) + sum(l, b);
            cout << ans << endl;
        }
        else break;
    }
    return 0;
}