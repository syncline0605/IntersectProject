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

//����������
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
//�������ļ����ȡ�������
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

//���������ĵ�˽��
double dot(Vector a, Vector b)
{
	return (a.x * b.x + a.y * b.y);
}

//������֮��ľ���
double getPointsDistance(Point a, Point b)
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	return (sqrt(x * x + y * y));
}

//���������㣬�ӵ�aָ���b������
Vector getVector(Point a, Point b)
{
	Vector newVec;
	newVec.x = b.x - a.x;
	newVec.y = b.y - a.y;
	newVec.length = sqrt((newVec.x) * (newVec.x) + (newVec.y) * (newVec.y));
	return newVec;
}

//��ĳһ�����ĵ�λ����
Vector getUnitVector(Vector v)
{
	Vector unitVector;
	unitVector.x = v.x / v.length;
	unitVector.y = v.y / v.length;
	unitVector.length = 1;
	return unitVector;
}

//�����ֱ���ϵ�ͶӰ����
Point getProjection(Point a, Line l)
{
	Vector e = getVector(l.p1, l.p2);
	Vector k = getVector(l.p1, a);
	double r = dot(k, e) / e.length;
	Point pr;
	pr.x = l.p1.x + r * e.x;
	pr.y = l.p1.y + r * e.y;
	return pr;
}

//��㵽ֱ�ߵľ���
double getPointLineDistance(Point a, Line l)
{
	Point pr = getProjection(a, l);
	return getPointsDistance(a, pr);
}

//����ֱ�߽���
int getPoint(Line l1, Line l2, Point& crossPoint)
{

}

//��ֱ����Բ�Ľ���
int getPoint(Line l, Circle c, pair<Point, Point>& crossPair)
{
	Point pr = getProjection(c.center, l);
	double distance = getPointsDistance(c.center, pr);
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
		Vector e = getUnitVector(getVector(l.p1, l.p2));
		double m = sqrt(c.r * c.r - distance * distance);
		crossPair.first.x = pr.x + m * e.x;
		crossPair.first.y = pr.y + m * e.y;
		crossPair.second.x = pr.x - m * e.x;
		crossPair.second.y = pr.y - m * e.y;
		return TWOCROSS;
	}
}

//����Բ����
int getPoint(Circle c1, Circle c2, pair<Point, Point>& crossPair)
{

}

//�����ܽ������
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
