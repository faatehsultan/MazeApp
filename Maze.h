#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include "Point.h"
using namespace std;

class Maze
{
protected:
	int** maze;
	int noOfRows;
	int noOfCols;
	Point curPos;
	Point source;
	Point destination;
	bool setCurrentPos(const Point cur);
public:
	Maze(const int _noOfRows, const int _noOfCols);
	Maze(const int _noOfRows, const int _noOfCols,
		const Point src, const Point dest);
	Maze(const Maze& ref);
	~Maze();
	void setMaze(int** srcMaze);
	void resetMaze();
	bool setSource(const Point src);
	bool setDestination(const Point dest);
	Point getSource();
	Point getDestination();
	Point getCurrentPos();
	bool up();
	bool down();
	bool right();
	bool left();
	void displayMaze();
	int& operator[](const Point p);
	bool testPoint(Point p);
};

#endif MAZE_H
