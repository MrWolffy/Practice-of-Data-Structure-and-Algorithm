#include <iostream>
#include <vector>
using namespace std;

#define MyMax 200
int G[MyMax][MyMax]; //改
int dfn[MyMax] ;
int low[MyMax] ;
int Father[MyMax];
bool bIsCutVetext[MyMax];
int nTime;
int n,m;

void Tarjan(int u, int father)
{	
	Father[u] = father;
	int i,j,k;
	low[u] = dfn[u] = nTime ++;
	for(int v = 1;v <= n ;v ++ ) { //改
		if (!G[u][v]) continue; //改
		if( ! dfn[v]) {
			Tarjan(v,u);
			low[u] = min(low[u],low[v]);
		}
		else if( father != v )
			low[u] = min(low[u],dfn[v]);
	}
}
void Count()
{
	int i,nRootSons = 0;
	Tarjan(1,0);
	for( i = 2;i <= n;i ++ ) {
		int v = Father[i];
		if( v == 1 )
			nRootSons ++;
		else if( dfn[v] <= low[i])
			bIsCutVetext[v] = true;
	}
	if( nRootSons > 1)
		bIsCutVetext[1] = true;
	for( i = 1;i <= n;i ++ )
		if( bIsCutVetext[i] )
			cout << i << endl;
	for( i = 1;i <= n;i ++) {
		int v = Father[i];
		if(v >0 &&  dfn[v] < low[i] && G[v][i] == 1) //改
			cout << v << "," << i <<endl;
	}
}

int main()
{
	int u,v;
	int i;
	
	nTime = 1;
	cin >> n >> m ;
	memset(G, 0, sizeof(G)); //改
	for(  i = 1;i <= m;i ++ ) {
		cin >> u >> v;
		G[v][u]++;
		G[u][v]++;
	}
	memset( dfn,0,sizeof(dfn));
	memset( Father,0,sizeof(Father));
	memset( bIsCutVetext,0,sizeof(bIsCutVetext));
	Count();
	return 0;
}

/*
测试数据：
input:
11 14
1 2
1 4
1 5
1 6
2 11
2 3
4 3
4 9
5 8
5 7
6 7
7 10
7 10
11 3
output:
1
4
5
7
5,8
4,9
*/