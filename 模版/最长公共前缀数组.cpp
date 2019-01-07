#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 100010; 
const int maxj = int(ceil(log(MAXN) / log(2)));
const int inf = 0x3f3f3f3f;
int wa[MAXN], wb[MAXN], wv[MAXN], Ws[MAXN];
int sa[MAXN], Rank[MAXN], height[MAXN], dp[MAXN][MAXN];
void buildSA(const string s, int * sa, int n, int m) {
	int i, j, p, *pm = wa, *k2sa = wb, *t;
	for (i = 0; i<m; i++) Ws[i] = 0; 
	for (i = 0; i<n; i++) Ws[pm[i] = s[i]]++;
	for (i = 1; i<m; i++) Ws[i] += Ws[i - 1];
	for (i = n - 1; i >= 0; i--) sa[--Ws[pm[i]]] = i;
	for (j = p = 1; p < n; j <<= 1, m = p) { 
		for (p = 0, i = n - j; i < n; i++) k2sa[p++] = i;
		for (i = 0; i < n; i++)
			if (sa[i] >= j) k2sa[p++] = sa[i] - j;
		for (i = 0; i < m; i++) Ws[i] = 0;
		for (i = 0; i < n; i++) 
			Ws[ wv[i] = pm[k2sa[i]] ]++;
		for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
		for (i = n - 1; i >= 0; i--)
			sa[--Ws[wv[i]]] = k2sa[i];
		for (t = pm, pm = k2sa, k2sa = t, 
			pm[sa[0]] = 0, p = i = 1; i<n; i++) {
			int a = sa[i - 1], b = sa[i]; 
			if (k2sa[a] == k2sa[b] && a + j < n && b + j < n &&
					k2sa[a + j] == k2sa[b + j])
				pm[sa[i]] = p - 1;
			else
				pm[sa[i]] = p++; 
		} 
	}
	return;  
}
void BuildHeight(string str,int n,int * sa,int * Rank) {
    int i, j, k;
    for(int i = 0;i < n; ++i)
        Rank[sa[i]] =  i;
    height[0] = 0;
    for (i = k = 0; i < n - 1; height[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1];
                  str[i+k]==str[j+k]; k++);
}

int lcpl(int i, int j) {
	int x = 0;
	for (++i; i + (1 << x) - 1 <= j; x++);
	int k = j - (1 << --x) + 1;
	return min(dp[i][x], dp[k][x]);
}

int main() {
	string str = "banana";
	int len = str.length();
	buildSA(str, sa, len + 1, 127);
	BuildHeight(str, len + 1, sa, Rank);
	int maxj = int(ceil(log(len) / log(2)));
	for (int j = 0; j <= maxj; ++j) {
		for (int i = 0; i < len; ++i) {
			dp[i][j] = inf;
		}
	}
	for (int i = 0; i < len; ++i) dp[i][0] = height[i+1];
	for (int j = 1; j <= maxj; ++j) {
		for (int i = 0; i < len; ++i) {
			dp[i][j] = min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
		}
	}
	for (int i = 0; i < len; ++i) {
		for (int j = i + 1; j < len; ++j) {
			cout << lcpl(i, j) << " ";
		}
		cout << endl;
	}
	return 0;
}
