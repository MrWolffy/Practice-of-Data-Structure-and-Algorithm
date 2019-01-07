#include <iostream>    
#include <queue>   
#include <vector>  
#include <algorithm>   
#include <deque>   
#include <cstring> //改
using namespace std;
#define INFINITE 999999999
int G[300][300], G1[300][300]; //改         
bool Visited[300];
int Layer[300];
int n,m;

bool CountLayer()   {
	int layer = 0;     
	deque<int>q;
	memset(Layer,0xff,sizeof(Layer));
	Layer[1] = 0;  q.push_back(1);
	while( ! q.empty()) {
		int v = q.front();
		q.pop_front();
		for( int j = 1; j <= m; j ++ ) {
			if( G[v][j] > 0 && Layer[j] == -1 ) {
				Layer[j] = Layer[v] + 1; 
				if( j == m ) return true;
				else q.push_back(j);
			}
		}
	}
	return false;
}

int Dinic() {
	int i;  	
	int s;
	int nMaxFlow = 0;
	deque<int> q;
	while( CountLayer() ) {
		q.push_back(1);
		memset(Visited,0,sizeof(Visited));   
		Visited[1] = 1;
		while( !q.empty()) {
			int nd = q.back();
			if( nd == m ) {
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
				for( i = 1;i <= m; i ++ )  {
				      if( G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 &&
				   	! Visited[i]) {
						Visited[i] = 1;
						q.push_back(i);
						break;
					}
				}

				if( i > m)
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
		int s,e,c;
		memset( G,0,sizeof(G));
		for( i = 0;i < n;i ++ ) {
			cin >> s >> e >> c;
			G[s][e] += c;
		}
		memcpy(G1, G, sizeof(G)); //改
		cout << Dinic() << endl;
		for (int i = 1; i <= m; ++i) { //改开始
			for (int j = 1; j <= m; ++j) {
				if (G[i][j] < G1[i][j]) {
					cout << i << " " << j << " " << G1[i][j] - G[i][j] << endl;
				}
			}
		} //改结束
	
	}
	return 0;
}

/*
测试数据：
input:
5 4
1 2 40
1 4 20
2 4 20
2 3 30
3 4 10
output:
50
1 2 30
1 4 20
2 3 10
2 4 20
3 4 10
*/