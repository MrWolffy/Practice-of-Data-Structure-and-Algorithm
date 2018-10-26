#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef struct {
    int x;
    int h, d;
    int flag;
} Square;
typedef struct {
    int line;
    int lc, rc;
    int cnt;
    int s1;
} Point;
Point tre[88888], temp;
Square s[11015];
int pos[11015];
void Update(int l, int r, int x, int a, int b, int t);
void Atonce(int l, int r, int x);
int Bsech(int l, int r, int k) {
    int m;
    m = (l + r) / 2;
    if (pos[m] < k)
        return Bsech(m + 1, r, k);
    if (pos[m] > k)
        return Bsech(l, m - 1, k);
    return m;
}
bool comp(Square a, Square b) {
    if (a.x < b.x || a.x == b.x && a.flag == 1 && b.flag == -1)
        return 1;
    return 0;
}
int main() {
    int i, n, x1, y1, x2, y2, len, sum;
    while (scanf("%d", &n) != EOF) {
        len = 1;
        sum = 0;
        memset(tre, 0, sizeof(tre));
        for (i = 1; i <= n; i++) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            s[i * 2 - 1].x = x1, s[i * 2].x = x2;
            s[i * 2 - 1].h = s[i * 2].h = y2;
            s[i * 2 - 1].d = s[i * 2].d = y1;
            s[i * 2 - 1].flag = 1, s[i * 2].flag = -1;
            pos[i * 2 - 1] = y1, pos[i * 2] = y2;
        }
        n = n * 2;
        sort(s + 1, s + n + 1, comp);
        sort(pos + 1, pos + n + 1);
        for (i = 2; i <= n; i++) {
            if (pos[i] != pos[i - 1])
                pos[++len] = pos[i];
        }
        for (i = 1; i <= n; i++) {
            x1 = Bsech(1, len, s[i].d);
            x2 = Bsech(1, len, s[i].h);
            temp = tre[1];
            Update(1, len - 1, 1, x1, x2 - 1, s[i].flag);
            sum += abs(tre[1].s1 - temp.s1) + temp.line * 2 * (s[i].x - s[i - 1].x);
        }
        printf("%d\n", sum);
    }
    return 0;
}

void Update(int l, int r, int x, int a, int b, int t) {
    int m;
    if (l >= a && r <= b) {
        tre[x].cnt += t;
        Atonce(l, r, x);
        return;
    }
    m = (l + r) / 2;
    if (a <= m)
        Update(l, m, x * 2, a, b, t);
    if (b >= m + 1)
        Update(m + 1, r, x * 2 + 1, a, b, t);
    Atonce(l, r, x);
}

void Atonce(int l, int r, int x) {
    if (tre[x].cnt >= 1)
        tre[x].s1 = pos[r + 1] - pos[l], tre[x].line = 1, tre[x].lc = tre[x].rc = 1;
    else
        tre[x].s1 = tre[x * 2].s1 + tre[x * 2 + 1].s1, tre[x].line = 0, tre[x].lc = tre[x].rc = 0;

    if (tre[x].cnt == 0 && l != r) {
        if (tre[x * 2].lc == 1)
            tre[x].lc = 1;
        if (tre[x * 2 + 1].rc == 1)
            tre[x].rc = 1;
        tre[x].line = tre[x * 2].line + tre[x * 2 + 1].line;
        if (tre[x * 2].rc == 1 && tre[x * 2 + 1].lc == 1)
            tre[x].line--;
    }
}