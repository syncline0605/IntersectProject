#pragma 
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <cmath>

#define NOCROSS 0
#define ONECROSS 1
#define TWOCROSS 2

#define EPS (0.00001)

using namespace std;

int compareDouble(double x) noexcept
{
	if (fabs(x) < EPS) return 0;
	if (x < 0) return -1;
	else return 1;
}

struct Point {
	double x;
	double y;
	double length;

	bool operator ==(const Point& b) const noexcept
	{
		if (compareDouble(x - b.x) == 0 && compareDouble(y - b.y) == 0) return true;
		return false;
	}
	bool operator <(const Point& b) const noexcept
	{
		if (compareDouble(x - b.x) == 0 && compareDouble(y - b.y) < 0) return true;
		if (compareDouble(x - b.x) < 0) return true;
		return false;
	}
	
};

typedef Point Vector;

struct Line {
	struct Point p1, p2;
};

struct Circle {
	struct Point center;
	double r;
};

void parseCommandLine(int argc, char* argv[], string& inputstring, string& outputstring);
void getInput(string inputstring, vector<Line>& lineSet, vector<Circle>& circleSet);
double dot(Vector a, Vector b) noexcept;
double getPointsDistance(Point a, Point b) noexcept;
Vector getVector(Point a, Point b) noexcept;
Vector getUnitVector(Vector v) noexcept;
Point getProjection(Point a, Line l) noexcept;
double getPointLineDistance(Point a, Line l) noexcept;
Point getCoorFromPolar(double x, double r) noexcept;
double getAngleFromPoint(Point p) noexcept;
int getPoint(Line l1, Line l2, Point& crossPoint) noexcept;
int getPoint(Line l, Circle c, pair<Point, Point>& crossPair) noexcept;
int getPoint(Circle c1, Circle c2, pair<Point, Point>& crossPair) noexcept;
int calPoint(vector<Line>& lineSet, vector<Circle>& circleSet, set<Point>& pointSet);