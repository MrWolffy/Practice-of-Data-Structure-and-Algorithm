#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

const int maxn = 200020;
int wa[maxn], wb[maxn], wv[maxn], Ws[maxn];
int sa[maxn], r[maxn];
int Rank[maxn], height[maxn];
char str[maxn];

void buildsa(const char *s, int sa[], int n, int m) {
    int i, j, p, *pm = wa, *k2sa = wb, *t;
    for (i = 0; i<m; i++) Ws[i] = 0;
    for (i = 0; i<n; i++) Ws[pm[i] = s[i]]++;
    for (i = 1; i<m; i++) Ws[i] += Ws[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--Ws[pm[i]]] = i;
    for (j = p = 1; p < n; j <<= 1, m = p) {
        for (p = 0, i = n - j; i < n; i++) k2sa[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= j) k2sa[p++] = sa[i] - j;
        for (i = 0; i < m; i++) Ws[i] = 0;
        for (i = 0; i < n; i++) Ws[wv[i] = pm[k2sa[i]]]++;
        for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--Ws[wv[i]]] = k2sa[i];
        for (t = pm, pm = k2sa, k2sa = t, pm[sa[0]] = 0, p = i = 1; i<n; i++) {
            int a = sa[i - 1], b = sa[i];
            if (k2sa[a] == k2sa[b] && k2sa[a + j] == k2sa[b + j])
                pm[sa[i]] = p - 1;
            else
                pm[sa[i]] = p++;
        }
    }
}

void buildheight(const char *str, int n, int *sa, int *rank) {
    int i, j, k;
    for (i = 0; i <= n; ++i) rank[sa[i]] = i;
    for (i = k = 0; i < n; height[rank[i++]] = k)
        for (k ? k-- : 0, j = sa[rank[i] - 1]; str[i+k] == str[j+k]; k++) ;
}

int main() {
    scanf("%s", str);
    int len1 = strlen(str);
    str[len1] = 'z' + 1;
    scanf("%s", str + len1 + 1);
    int len = strlen(str);
    buildsa(str, sa, len + 1, 130);
    buildheight(str, len, sa, Rank);
    int ans = 0;
    for (int i = 1; i <= len; ++i) {
        if (height[i] > ans && 1ll * (sa[i] - len1) * (sa[i-1] - len1) < 0)
            ans = height[i];
    }
    cout << ans << endl;
    return 0;
}