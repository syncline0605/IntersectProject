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

}

//���������ĵ�˽��
double dot(Vector a, Vector b)
{

}

//���������������
Vector getVector(Point a, Point b)
{

}

//������֮��ľ���
double getPointsDistance(Point a, Point b)
{

}

//�����ֱ���ϵ�ͶӰ����
Point getProjection(Point a, Line l)
{

}

//��㵽ֱ�ߵľ���
double getPointLineDistance(Point a, Line l)
{

}

//����ֱ�߽���
int getPoint(Line l1, Line l2, Point& crossPoint)
{

}

//��ֱ����Բ�Ľ���
int getPoint(Line l, Circle c, pair<Point, Point>& crossPair)
{

}

//����Բ����
int getPoint(Circle c1, Circle c2, pair<Point, Point>& crossPair)
{

}

//�����ܽ������
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
