#ifndef MAZE_APP_H
#define MAZE_APP_H
#include <iostream>
#include <ctime>
#include "Maze.h"
#include "Stack.h"
using namespace std;

class MazeApp :public Maze
{
private:
	Stack<Point> stack;
	int isMovementPossible();
	bool isDeadEnd();
	bool backtrack();
	bool isPointTraversed(const Point p);
	bool up();
	bool down();
	bool left();
	bool right();

	MazeApp(const int _noOfRows, const int _noOfCols);
	MazeApp(const int _noOfRows, const int _noOfCols,
		const Point src, const Point dest);
	bool traverse();

public:	
	static void start();
};

#endif MAZE_APP_H
