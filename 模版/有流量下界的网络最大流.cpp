#include <iostream>    
#include <queue>   
#include <vector>  
#include <algorithm>   
#include <deque>   
using namespace std;
#define INFINITE 999999999
int G[300][300], G1[300][300], lc[300][300]; //改    
bool Visited[300];
int Layer[300];
int n,m;
int s, t, x, y; //改
int nodescount; //改

bool CountLayer(int ss, int ee)   { //改
	int layer = 0;     
	deque<int>q;
	memset(Layer,0xff,sizeof(Layer));
	Layer[ss] = 0;  q.push_back(ss); //改
	while( ! q.empty()) {
		int v = q.front();
		q.pop_front();
		for( int j = 1; j <= nodescount; j ++ ) { //改
			if( G[v][j] > 0 && Layer[j] == -1 ) {
				Layer[j] = Layer[v] + 1; 
				if( j == ee ) return true; //改
				else q.push_back(j);
			}
		}
	}
	return false;
}

int Dinic(int ss, int ee) { //改
	int i;  	
	int nMaxFlow = 0;
	deque<int> q;
	while( CountLayer(ss, ee) ) { //改
		q.push_back(ss); //改
		memset(Visited,0,sizeof(Visited));   
		Visited[ss] = 1; //改
		while( !q.empty()) {
			int nd = q.back();
			if( nd == ee ) { //改
				int nMinC = INFINITE;
				int nMinC_vs;
				for( i = 1;i < q.size(); i ++ ) {
					int vs = q[i-1];
					int ve = q[i];
					if( G[vs][ve] > 0 ) {
						if( nMinC > G[vs][ve] ) {
							nMinC = G[vs][ve];
							nMinC_vs = vs;
						}
					}
				}
				nMaxFlow += nMinC;
				for( i = 1;i < q.size(); i ++ ) {
					int vs = q[i-1];
					int ve = q[i];
					G[vs][ve] -= nMinC;
					G[ve][vs] += nMinC;
				}
				while( !q.empty() && q.back() != nMinC_vs ) { 
					Visited[q.back()] = 0; 
					q.pop_back();
				}

			}
			else {
				for( i = 1;i <= nodescount; i ++ )  { //改
				      if( G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 &&
				   	! Visited[i]) {
						Visited[i] = 1;
						q.push_back(i);
						break;
					}
				}
				if( i > nodescount) //改
					q.pop_back();
			}
		}
	}
	return nMaxFlow;
}

int main()
{
	while (cin >> n >> m ) {
		int i,j,k;
		int b,e,c, minv, sum11 = 0; //改开始
		s = 1; t = m;
		x = m + 1; y = m + 2;
		nodescount = m + 2;
		memset( G,0,sizeof(G));
		memset(lc, 0, sizeof(lc));
		bool flag = true;
		for( i = 0;i < n;i ++ ) {
			cin >> b >> e >> c >> minv;
			G[b][e] += c - minv;
			G[b][x] += minv;
			G[y][e] += minv;
			sum11 += minv;
			lc[b][e] += minv;
			if (c < minv) flag = false;
		}
		if (!flag) {
			cout << "no" << endl;
			continue;
		}
		memcpy(G1, G, sizeof(G));
		G[t][s] = INFINITE;
		int sum1 = Dinic(y, x);
		if (sum1 < sum11) {
			cout << "no" << endl;
			continue;
		}
		sum1 = 0;
		for (int i = 1; i <= nodescount; ++i) {
			if (G[s][i] < G1[s][i]) sum1 += G1[s][i] - G[s][i];
		}
		G[s][t] = G[t][s] = 0;
		int sum2 = Dinic(s, t);
		cout << sum1 + sum2 << endl;
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (G1[i][j] - G[i][j] + lc[i][j] > 0)
					cout << i << " " << j << " " << G1[i][j] - G[i][j] + lc[i][j] << endl;
			}
		} //改结束
	}
	return 0;
}

/*
测试数据：
case 1:
input:
3 4
1 2 6 2
2 3 4 3
3 4 7 3
output:
4
1 2 4
2 3 4
3 4 4
case 2:
input:
3 4
1 2 6 5
2 3 4 4
3 4 7 5
output:
no
*/