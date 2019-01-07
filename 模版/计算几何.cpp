#include <iostream>
#include <cmath>
using namespace std;

// p13 向量表示
class CVector {
public:
	double x, y;
	CVector(double xx, double yy): x(xx), y(yy) {}
	CVector() {}
};

// 基本运算
// p14 向量加
CVector operator +(CVector p, CVector q) {
  return CVector(p.x + q.x, p.y + q.y);
}
// p15 向量减
CVector operator -(CVector p, CVector q) {
  return CVector(p.x - q.x, p.y - q.y);
}
// p16 数乘向量
CVector operator *(double k, CVector p) {
  return CVector(k * p.x, k * p.y);
}
// p17 向量点乘
double operator *(CVector p, CVector q) {
  return p.x * q.x + p.y * q.y;
}



// p19 向量模长
double length(CVector p) {
  return sqrt(p * p);
}
// p20 单位向量
CVector unit(CVector p) {
  return 1 / length(p) * p;
}
// p21 向量点乘
double dot(CVector p, CVector q) {
	return p.x*q.x+p.y*q.y;
}
// p21 p在n上的投影
double project(CVector p, CVector n) {
  return dot(p, unit(n));
}


// p24 向量叉乘
double operator ^(CVector p, CVector q) {
  return p.x * q.y - q.x * p.y;
}
// p26 两个矢量所围成的三角形面积
double area(CVector p, CVector q) {
  return (p^q) / 2;  
}


// p39 点、线的表示
class CPoint {
public:
  double x, y;
  CPoint(double xx, double yy): x(xx), y(yy) {}
  CPoint() {}
};
class CLine {
public:
  CPoint a, b;
  CLine(CPoint aa, CPoint bb): a(aa), b(bb) {}
  CLine() {}
};
// p40 常用常数与函数
double PI = acos(-1);
double INF = 1e20;
double EPS = 1e-6; 
bool IsZero(double x) {
  return -EPS < x && x < EPS;
}
bool FLarger(double a, double b) {
	return a - b > EPS;
}
bool FLess(double a, double b) {
	return b - a > EPS;
}


// p41 从a点指向b点的向量
CVector operator -(CPoint b, CPoint a) {
  return CVector(b.x - a.x, b.y - a.y);
}
// p41 将a沿p方向移动到b
CPoint operator +(CPoint a, CVector p) {
  return CPoint(a.x + p.x, a.y + p.y);
}
// p42 两点间距离
double dist(CPoint p, CPoint q) {
  return length(p - q);
}
// p43 点与线距离
double dist(CPoint p, CLine l) {
  return fabs((p - l.a) ^ (l.b - l.a))
         / length(l.b - l.a);
}
// p44 点b绕点a旋转alpha角度
CPoint rotate(CPoint b, CPoint a,
              double alpha) {
  CVector p = b - a;
  return CPoint(a.x + (p.x * cos(alpha)
                       - p.y * sin(alpha)),
                a.y + (p.x * sin(alpha)
                       + p.y * cos(alpha)));
}
// p45 点在直线左侧还是右侧
#define Point CPoint
int sideOfLine(Point p, Point a, Point b)
{ //判断p在直线 a->b的哪一侧
	double result = (b - a) ^ (p - a);
	if (IsZero(result))
		return 0; //p 在 a->b上
	else if (result > 0)
		return 1; //p在a->b左侧
	else
		return -1; //p在a->b右侧
}
// p46 过点作线的垂线
CLine Vertical(CPoint p, CLine l) {
  return CLine(p,
       p + (rotate(l.b, l.a, PI / 2) - l.a));
}
// p47 点到线的垂足
CPoint foot(CPoint p, CLine l) {
  return l.a + project(p - l.a, l.b - l.a)
               * unit(l.b - l.a);
}
// p48 两条直线的交点
#define isZero IsZero
CPoint intersect(CLine l, CLine m, string msg) {
  double x = area(m.a - l.a, l.b - l.a);
  double y = area(l.b - l.a, m.b - l.a);
  if (isZero(x + y)) {
    if (isZero(dist(l.a, m))) msg = "重合"; //改
    else msg = "平行";
    return CPoint(0,0); //改
  }
  return m.a + x / (x + y) * (m.b - m.a);
} //即便线段 l.a->l.b和 m.a->m.b没交点，也适用

// p49 判断线段规范相交
#define Vector CVector
#define eps EPS
double Cross(const Vector & v1, const Vector & v2)
{ 	//叉积
	return v1.x * v2.y - v1.y * v2.x;
}
bool IsFormalCross(Point p1, Point p2, Point p3, 
	Point p4)
{//判断p1->p2和p3->p4是否规范相交
   return Cross(p2 - p1, p3 - p1)* 
		Cross(p2 - p1, p4 - p1) < -eps  &&
	    Cross(p4 - p3, p1 - p3)*
			Cross(p4 - p3, p2 - p3) < -eps;
}





#include <map>
// p50 两条线段相交的各种情况
#define Seg CLine
pair<int, Point> CrossPoint(Seg s1, Seg s2);

// pair<int,Point> result = CrossPoint(s1,s2);
/*
	返回值 result.first:
	0  规范相交，
	1  端点重合，但不平行，不共线
	2  一个端点在另一个内部 s1端点在 s2内部 (不平行，不共线）
	3  一个端点在另一个内部 s2端点在 s1内部 (不平行，不共线）
	4  无交点，不平行，不共线，两直线交点是result.second 
	5  平行
	6  共线且有公共点
	7  共线且无公共点
	8  s1,s2无交点，但是s2所在直线和s1有交点，即交点在s1上
	9  s1,s2无交点，但是s1所在直线和s2有交点，即交点在s2上

有交点的情况下，交点都是： result.second
*/
bool FLessEq(double a, double b)
{
	return b - a > EPS || IsZero(b-a);
}
bool PointInSeg(Point p, Seg L)
{
	double tmp = Cross(L.a - p, L.a - L.b);
	if (!IsZero(tmp)) 
		return false; 
	if ( FLessEq(min(L.a.x, L.b.x),p.x) && 
           FLessEq(p.x ,max(L.a.x, L.b.x)) &&
   	     FLessEq(min(L.a.y, L.b.y), p.y) && 
           FLessEq(p.y , max(L.a.y, L.b.y)))
		  return true;
	return false;
}

// 这里需要增加一些
bool operator==(CPoint p1, CPoint p2) {
	return isZero(p1.x - p2.x) && isZero(p1.y - p2.y);
}
#define Area area
#define Distance dist
// 结束
pair<int, Point> CrossPoint(Seg s1, Seg s2)  {
	Point p1 = s1.a;
	Point p2 = s1.b;
	Point p3 = s2.a;
	Point p4 = s2.b;

	double a1 = Area(p3 - p1, p4 - p1);
	double a2 = Area(p4 - p2, p3 - p2);//这些顺序不能乱
	if (Cross(p2 - p1, p3 - p1)* 
		Cross(p2 - p1, p4 - p1) < -EPS &&
		Cross(p4 - p3, p1 - p3)*
		Cross(p4 - p3, p2 - p3) < -EPS) {// 规范相交  
		return 
		  make_pair(0,p1+(a1/(a1 + a2))*(p2 - p1));
	}
	if (!(IsZero(Cross(p2 - p1, p3 - p4)))) {	
		//不平行,不共线
		if (p1 == p3 || p1 == p4)  
		//端点重合且不平行，不共线 
			return make_pair(1, p1);
		if (p2 == p3 || p2 == p4)
			return make_pair(1, p2);
		if (PointInSeg(p1, s2))
			return make_pair(2, p1);
		if (PointInSeg(p2, s2))
			return make_pair(2, p2);
		if (PointInSeg(p3, s1))
			return make_pair(3, p3);
		if (PointInSeg(p4, s1))
			return make_pair(3, p4);
		Point crossPoint = 
			p1+(a1/(a1+ a2))*(p2 - p1);
		if (PointInSeg(crossPoint, s1))
			return make_pair(8, crossPoint);
		if (PointInSeg(crossPoint, s2))
			return make_pair(9, crossPoint);
		return make_pair(4, crossPoint); 
	// 直线和线段也无交点，不平行，不共线，两直线交点是second

	}
	if (!IsZero(Distance(p1, s2)))
		return make_pair(5, Point(0, 0)); //平行
	//下面都是共线，且有公共点 
	if (PointInSeg(p1, s2))
		return make_pair(6, p1);
	if (PointInSeg(p2, s2))
		return make_pair(6, p2);
	if (PointInSeg(p3, s1))
		return make_pair(6, p3);
	if (PointInSeg(p4, s1))
		return make_pair(6, p4);
	return make_pair(7, Point(0, 0));//共线，且无公共点 
}

// p56 线与线夹角
double angle(CLine l, CLine m) {
  return acos(fabs(
               project(l.b - l.a, m.b - m.a)
               / length(l.b - l.a)));
}










// p23 求b关于a的对称
CVector duichen(CVector a, CVector b) {
	return 2 * project(b, a) * a - b;
}

int main() {
	return 0;
}
