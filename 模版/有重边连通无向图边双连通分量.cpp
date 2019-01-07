#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MyMax 200
int G[MyMax][MyMax]; //改
int dfn[MyMax] ;
int low[MyMax] ;
int nTime;
int n,m;
struct Edge2
{
	int u;
	int v;
	Edge2(int u_,int v_):u(u_),v(v_) { }
};
deque<Edge2> Edges;
int nBlockNo = 0;
void Tarjan(int u, int father)
{	
	int i,j,k;
	low[u] = dfn[u] = nTime ++;
	for(int v = 1;v <= n ;v ++ ) { //改
		if (!G[u][v]) continue; //改
		if( ! dfn[v]) {
			Edges.push_back(Edge2(u,v));
			Tarjan(v,u);
			low[u] = min(low[u],low[v]);
			Edge2 tmp(0, 0);
			if(dfn[u] < low[v] && G[u][v] == 1) { //改开始
				tmp = Edges.back();
				Edges.pop_back ();
				if (!(tmp.u == u && tmp.v == v))
					cout << "Block No: " << ++nBlockNo << endl;
				while ( !(tmp.u == u && tmp.v == v) ) {
					cout << tmp.u << "," <<
						 tmp.v << endl;
					tmp = Edges.back();
					Edges.pop_back ();
				}
			} //改结束
		}
		else {
			if( v != father ) {
			       low[u] = min(low[u],dfn[v]);
			       if( dfn[u] > dfn[v])
					Edges.push_back(Edge2(u,v));
			}
		}
	} 
}
int main()
{

	int u,v;
	int i;
	nTime = 1;
	cin >> n >> m ;
	nBlockNo = 0;
	for(  i = 1;i <= m;i ++ ) {
		cin >> u >> v;
		G[v][u]++;
		G[u][v]++;
	}
	memset( dfn,0,sizeof(dfn));
	Tarjan(1,0);
	Edge2 tmp(0, 0); //改开始
	cout << "Block No: " << ++nBlockNo << endl;
	while (!Edges.empty()) {
		tmp = Edges.back();
		Edges.pop_back ();
		cout << tmp.u << "," <<
				tmp.v << endl;
	} //改结束
	return 0;
}

/*
测试数据：
case 1:
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
Block No: 1
7,10
6,1
7,6
5,7
1,5
11,2
3,11
4,1
3,4
2,3
1,2
case 2:
input:
8 9
1 2
1 3
1 5
3 5
2 4
4 6
4 7
6 8
7 8
output:
Block No: 1
7,4
8,7
6,8
4,6
Block No: 2
5,1
3,5
1,3
*/