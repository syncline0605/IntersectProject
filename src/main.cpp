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

fstream input;
fstream output;

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
	int n;
	string line = "L";
	string circle = "C";
	input >> n;
	for (int i = 0; i < n; i++)
	{
		string kind;
		input >> kind;
		if (!kind.compare(line))
		{
			Line newline;
			input >> newline.p1.x >> newline.p1.y >> newline.p2.x >> newline.p2.y;
			lineSet.push_back(newline);
		}
		else if (!kind.compare(circle))
		{
			Circle newCircle;
			input >> newCircle.center.x >> newCircle.center.y >> newCircle.r;
			circleSet.push_back(newCircle);
		}
	}
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
	for (int i = 0; i < lineSet.size(); i++)
	{
		for (int j = i + 1; j < lineSet.size(); j++)
		{
			Point crossPoint;
			int result = getPoint(lineSet.at(i), lineSet.at(j), crossPoint);
			if (result == ONECROSS)
			{
				pointSet.insert(crossPoint);
			}
		}
		for (int j = 0; j < circleSet.size(); j++)
		{
			pair<Point, Point> crossPair;
			int result = getPoint(lineSet.at(i), circleSet.at(j), crossPair);
			if (result == ONECROSS)
			{
				pointSet.insert(crossPair.first);
			}
			else if (result == TWOCROSS)
			{
				pointSet.insert(crossPair.first);
				pointSet.insert(crossPair.second);
			}
		}
	}
	for (int i = 0; i < circleSet.size(); i++)
	{
		for (int j = i + 1; j < circleSet.size(); j++)
		{
			pair<Point, Point> crossPair;
			int result = getPoint(circleSet.at(i), circleSet.at(j), crossPair);
			if (result == ONECROSS)
			{
				pointSet.insert(crossPair.first);
			}
			else if (result == TWOCROSS)
			{
				pointSet.insert(crossPair.first);
				pointSet.insert(crossPair.second);
			}
		}
	}
	return pointSet.size();
}

int main(int argc, char* argv[])
{
	parseCommandLine(argc, argv);
	getInput();
	int n = calPoint();
	output << n << endl;
}
