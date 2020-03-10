#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <cmath>
#include "Intersect.h"

using namespace std;

//解析命令行
void parseCommandLine(int argc, char* argv[], string& inputstring, string& outputstring)
{
	string in = "-i";
	string out = "-o";
	for (int i = 1; i < argc; i++)
	{
		string command = argv[i];
		if (!command.compare(in))
		{
			inputstring = argv[++i];
		}
		else if (!command.compare(out))
		{
			outputstring = argv[++i];
		}
	}
}
//从输入文件里获取输入对象
void getInput(string inputstring, vector<Line>& lineSet, vector<Circle>& circleSet)
{
	ifstream input;
	input.open(inputstring, ios::in);
	int n;
	const string line = "L";
	const string circle = "C";
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
	input.close();
}

//求两向量的点乘结果
double dot(Vector a, Vector b) noexcept
{
	return (a.x * b.x + a.y * b.y);
}

//求两点之间的距离
double getPointsDistance(Point a, Point b) noexcept
{
	const double x = a.x - b.x;
	const double y = a.y - b.y;
	return (sqrt(x * x + y * y));
}

//求连接两点，从点a指向点b的向量
Vector getVector(Point a, Point b) noexcept
{
	Vector newVec;
	newVec.x = b.x - a.x;
	newVec.y = b.y - a.y;
	newVec.length = sqrt((newVec.x) * (newVec.x) + (newVec.y) * (newVec.y));
	return newVec;
}

//求某一向量的单位向量
Vector getUnitVector(Vector v) noexcept
{
	Vector unitVector;
	unitVector.x = v.x / v.length;
	unitVector.y = v.y / v.length;
	unitVector.length = 1;
	return unitVector;
}

//求点在直线上的投影坐标
Point getProjection(Point a, Line l) noexcept
{
	Vector e = getVector(l.p1, l.p2);
	const Vector k = getVector(l.p1, a);
	const double r = dot(k, e) / e.length;
	Point pr = {0, 0};
	e = getUnitVector(e);
	pr.x = l.p1.x + r * e.x;
	pr.y = l.p1.y + r * e.y;
	return pr;
}

//求点到直线的距离
double getPointLineDistance(Point a, Line l) noexcept
{
	const Point pr = getProjection(a, l);
	return getPointsDistance(a, pr);
}

//通过极坐标系上的极角和极径求在直角坐标系中的坐标
Point getCoorFromPolar(double x, double r) noexcept
{
	Point newPoint;
	newPoint.x = x * cos(r);
	newPoint.y = x * sin(r);
	return newPoint;
}

//通过坐标求出这一点代表的向量和x轴的夹角
double getAngleFromPoint(Point p) noexcept
{
	return atan2(p.y, p.x);
}

//求两直线交点
int getPoint(Line l1, Line l2, Point& crossPoint) noexcept
{
	const int flag1 = (l1.p1.x == l1.p2.x) ? 0 : 1;
	const int flag2 = (l2.p1.x == l2.p2.x) ? 0 : 1;
	if (flag1 == 0 && flag2 == 0)
	{
		return NOCROSS;
	}
	const double a1 = l1.p1.y - l1.p2.y;
	const double b1 = l1.p2.x - l1.p1.x;
	const double c1 = l1.p1.x * l1.p2.y - l1.p2.x * l1.p1.y;
	const double a2 = l2.p1.y - l2.p2.y;
	const double b2 = l2.p2.x - l2.p1.x;
	const double c2 = l2.p1.x * l2.p2.y - l2.p2.x * l2.p1.y;

	const double D = a1 * b2 - a2 * b1;
	if (D == 0)
	{
		return NOCROSS;
	}
	crossPoint.x = (b1 * c2 - b2 * c1) / D;
	crossPoint.y = (a2 * c1 - a1 * c2) / D;
	return ONECROSS;
}

//求直线与圆的交点
int getPoint(Line l, Circle c, pair<Point, Point>& crossPair) noexcept
{
	const Point pr = getProjection(c.center, l);
	const double distance = getPointsDistance(c.center, pr);
	if (distance > c.r)
	{
		return NOCROSS;
	}
	else if (distance == c.r)
	{
		crossPair.first = pr;
		return ONECROSS;
	}
	else
	{
		const Vector e = getUnitVector(getVector(l.p1, l.p2));
		const double m = sqrt(c.r * c.r - distance * distance);
		crossPair.first.x = pr.x + m * e.x;
		crossPair.first.y = pr.y + m * e.y;
		crossPair.second.x = pr.x - m * e.x;
		crossPair.second.y = pr.y - m * e.y;
		return TWOCROSS;
	}
}

//求两圆交点
int getPoint(Circle c1, Circle c2, pair<Point, Point>& crossPair) noexcept
{
	const double distance = getPointsDistance(c1.center, c2.center);
	if ((distance > c1.r + c2.r) || (distance < fabs(c1.r - c2.r)))
	{
		return NOCROSS;
	}
	else if (distance == c1.r + c2.r || distance == fabs(c1.r - c2.r))
	{
		const Vector e = getUnitVector(getVector(c1.center, c2.center));
		crossPair.first.x = c1.center.x + c1.r * e.x;
		crossPair.first.y = c1.center.y + c1.r * e.y;
		return ONECROSS;
	}
	else
	{
		const double a = acos((c1.r * c1.r + distance * distance - c2.r * c2.r) / (2 * c1.r * distance));
		const Vector e = getVector(c1.center, c2.center);
		const double t = getAngleFromPoint(e);
		const Point p1 = getCoorFromPolar(c1.r, t + a);
		const Point p2 = getCoorFromPolar(c1.r, t - a);
		crossPair.first.x = c1.center.x + p1.x;
		crossPair.first.y = c1.center.y + p1.y;
		crossPair.second.x = c1.center.x + p2.x;
		crossPair.second.y = c1.center.y + p2.y;
		return TWOCROSS;
	}
}

//计算总交点个数
int calPoint(vector<Line>& lineSet, vector<Circle>& circleSet, set<Point>& pointSet)
{
	for (unsigned int i = 0; i < lineSet.size(); i++)
	{
		for (unsigned int j = i + 1; j < lineSet.size(); j++)
		{
			Point crossPoint;
			const int result = getPoint(lineSet.at(i), lineSet.at(j), crossPoint);
			if (result == ONECROSS)
			{
				pointSet.insert(crossPoint);
			}
		}
		for (unsigned int j = 0; j < circleSet.size(); j++)
		{
			pair<Point, Point> crossPair;
			const int result = getPoint(lineSet.at(i), circleSet.at(j), crossPair);
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
	for (unsigned int i = 0; i < circleSet.size(); i++)
	{
		for (unsigned int j = i + 1; j < circleSet.size(); j++)
		{
			pair<Point, Point> crossPair;
			const int result = getPoint(circleSet.at(i), circleSet.at(j), crossPair);
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
	
	string inputstring = "";
	string outputstring = "";
	vector<Line> lineSet;
	vector<Circle> circleSet;
	set<Point> pointSet;

	parseCommandLine(argc, argv, inputstring, outputstring);
	getInput(inputstring, lineSet, circleSet);
	const int n = calPoint(lineSet, circleSet, pointSet);

	ofstream output;
	output.open(outputstring, ios::out);

	output << n << endl;
	output.close();
}
