#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <cmath>

#define NOCROSS 0
#define ONECROSS 1
#define TWOCROSS 2

using namespace std;

ofstream input;
ofstream output;

struct Point {
	double x;
	double y;
	double length;
};

typedef Point Vector;

struct Line {
	Point p1, p2;
};

struct Circle {
	Point center;
	double r;
};

vector<Line> lineSet;
vector<Circle> circleSet;
set<Point> pointSet;

//解析命令行
void parseCommandLine(int argc, char* argv[])
{
	string in = "-i";
	string out = "-o";
	for (int i = 1; i <= argc; i++)
	{
		string command(argv[i]);
		if (!command.compare(in))
		{
			input.open(argv[++i], ios::in);
		}
		else if (!command.compare(out))
		{
			output.open(argv[++i], ios::out);
		}
	}
}
//从输入文件里获取输入对象
void getInput()
{

}

//求两向量的点乘结果
double dot(Vector a, Vector b)
{

}

//求连接两点的向量
Vector getVector(Point a, Point b)
{

}

//求两点之间的距离
double getPointsDistance(Point a, Point b)
{

}

//求点在直线上的投影坐标
Point getProjection(Point a, Line l)
{

}

//求点到直线的距离
double getPointLineDistance(Point a, Line l)
{

}

//求两直线交点
int getPoint(Line l1, Line l2, Point& crossPoint)
{

}

//求直线与圆的交点
int getPoint(Line l, Circle c, pair<Point, Point>& crossPair)
{

}

//求两圆交点
int getPoint(Circle c1, Circle c2, pair<Point, Point>& crossPair)
{

}

//计算总交点个数
int calPoint()
{

}

int main(int argc, char* argv[])
{
	parseCommandLine(argc, argv);
	getInput();
	int n = calPoint();
	output << n << endl;
}
