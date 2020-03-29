#ifndef POINT_H
#define POINT_H
#include <string>
using namespace std;

struct Point
{
	int row;
	int col;
	Point() :row(0), col(0)
	{}
	Point(int _row, int _col) :row(_row), col(_col)
	{}
	string str()
	{
		return string('(' + to_string(row) + ", " + to_string(col) + ')');
	}
	bool operator==(const Point p2)
	{
		return (row == p2.row && col == p2.col);
	}
	Point& operator=(const Point p2)
	{
		row = p2.row;
		col = p2.col;
		return *this;
	}
	bool operator!=(const Point p2)
	{
		return !(*this == p2);
	}
};

#endif POINT_H
