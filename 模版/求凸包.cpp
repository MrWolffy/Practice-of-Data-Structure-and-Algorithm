//POJ1113 Wall , 极角序扫描法求凸包 by Guo Wei
#include <iostream> 
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;
#define EPS 1e-6
int Sign(double x) { // 判断 x 是大于0,等于0还是小于0 
	return fabs(x)<EPS?0:x>0?1: -1;
}
struct Point {
	double x,y;
	Point(double xx = 0,double yy = 0):x(xx),y(yy) { }
	Point operator-(const Point & p) const {
		return Point(x-p.x,y-p.y);
	}
	bool operator <(const Point & p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};
typedef Point Vector;
double Cross(const Vector & v1, const Vector & v2) 
{//叉积
	return v1.x * v2.y - v2.x * v1.y;
}
double Distance(const Point & p1,const Point & p2) 
{
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}


//POJ1113 Wall , 水平序扫描法求凸包 by Guo Wei
int Graham(vector<Point>  & points, vector<Point> & stack) {
//在凸包上，但不是顶点的点，没有抛弃，留在stack里面
	if( points.size() < 3)
		return 0;
	stack.clear();
	//先按坐标排序，最左下的放到points[0] 
  sort(points.begin(),points.end()); stack.push_back(points[0]);
	stack.push_back(points[1]);
	int n = points.size();

	for(int i = 2; i< n; ++i) { //做右半凸包
		while(stack.size()>1)	{//定要这一条
			Point p2 = * (stack.end()-1);
			Point p1 = * (stack.end()-2);
			if( Sign(Cross(p2-p1,points[i]-p2) < 0)) {
			//p2->points[i]向右转，才让p2出栈 ，这样能保留凸包边上的点 
				stack.pop_back();
			}
			else
				break;
		}
		stack.push_back(points[i]);
	}
	int size = stack.size();
	//此时栈顶定是points[n-1] 
	stack.push_back(points[n-2]);
	for(int i = n-3; i >= 0;--i) { //做左半凸包
		while(stack.size() > size) {
			Point p2 = * (stack.end()-1);
			Point p1 = * (stack.end()-2);
			if( Sign(Cross(p2-p1,points[i]-p2) < 0)) 				stack.pop_back();
			else
				break;
		}
		stack.push_back(points[i]);
	}
	stack.pop_back();
	return stack.size();
}	

int main() {
	int n;
	cin >> n;
	vector<Point> points; vector<Point> stack;
	for (int i = 0; i < n; ++i) {
		double x, y;
		cin >> x >> y;
		points.push_back(Point(x, y));
	}
	int num = Graham(points, stack);
	for (int i = 0; i < num; ++i) {
		cout << stack[i].x << " " << stack[i].y << endl;
	}
	return 0;
}

/*
测试数据：
input:
9
200 400
300 400
300 300
400 300
400 400
500 400
500 200
350 200
200 200
output:
200 200
350 200
500 200
500 400
400 400
300 400
200 400
*/