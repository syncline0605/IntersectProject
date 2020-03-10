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

using namespace std;

struct Point {
	double x;
	double y;
	double length;

	bool operator==(const Point b) const
	{
		return (x == b.x) && (y == b.y);
	}
	bool operator!=(const Point b) const
	{
		return (!((x == b.x) && (y == b.y)));
	}
	bool operator<=(const Point b) const
	{
		return x <= b.x;
	}
	bool operator<(const Point b) const
	{
		return x < b.x;
	}
	bool operator>=(const Point b) const
	{
		return x >= b.x;
	}
	bool operator>(const Point b) const
	{
		return x > b.x;
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
