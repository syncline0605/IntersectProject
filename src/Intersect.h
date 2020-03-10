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
