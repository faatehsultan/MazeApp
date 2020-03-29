#include "Maze.h"



/*when source and destination not given in constructor,
	first cell wil be considered source and last cell will
	be considered destination. Initially, curPos will be
	at source point.*/

bool Maze::setCurrentPos(const Point cur)
{
	if (cur.col >= 0 && cur.row >= 0 &&
		cur.col < noOfCols && cur.row < noOfRows &&
		testPoint(cur))
	{
		curPos = cur;
		return true;
	}
	return false;
}

Maze::Maze(const int _noOfRows, const int _noOfCols) :noOfRows(_noOfRows),
noOfCols(_noOfCols), source(-1, -1), destination(-1, -1), 
curPos(source),maze(nullptr)
{
	if (_noOfCols <= 0 || _noOfRows <= 0)
		return;
	maze = new int* [noOfRows];
	for (int i = 0; i < noOfRows; i++)
		maze[i] = new int[noOfCols];
	resetMaze();
}
Maze::Maze(const int _noOfRows, const int _noOfCols,
	const Point src, const Point dest) :
	Maze(_noOfRows, _noOfCols)

{
	if (_noOfCols <= 0 || _noOfRows <= 0)
		return;
	setSource(src);
	setDestination(dest);
}
Maze::Maze(const Maze& ref) :
	Maze(ref.noOfRows, ref.noOfCols)
{
	for (int i = 0; i < noOfRows; i++)
	{
		for (int j = 0; j < noOfCols; j++)
			maze[i][j] = ref.maze[i][j];
	}
	setSource(ref.source);
	setCurrentPos(ref.curPos);
	setDestination(ref.destination);
}
Maze::~Maze()
{
	for (int i = 0; i < noOfRows; i++)
		delete[] maze[i];
	delete[]maze;
}
void Maze::setMaze(int** srcMaze)
{
	for (int i = 0; i < noOfRows; i++)
	{
		for (int j = 0; j < noOfCols; j++)
			maze[i][j] = srcMaze[i][j];
	}
	//default setting of source, destination and curPos
	bool set = false;
	for (int i = 0; i < noOfRows && !set; i++)
	{
		for (int j = 0; j < noOfCols && !set; j++)
		{
			if (maze[i][j])
			{
				setSource({ i, j });
				setCurrentPos({ i, j });
				set = true;
			}
		}
	}
	set = false;
	for (int i = noOfRows - 1; i >= 0 && !set; i--)
	{
		for (int j = noOfCols - 1; j >= 0 && !set; j--)
		{
			if (maze[i][j])
			{
				setDestination({ i, j });
				set = true;
			}
		}
	}
}
void Maze::resetMaze()
{
	for (int i = 0; i < noOfRows; i++)
	{
		for (int j = 0; j < noOfCols; j++)
			maze[i][j] = 0;
	}
}
bool Maze::setSource(const Point src)
{
	if (testPoint(src))
	{
		source = src;
		curPos = src;	//current position will also restart
		return true;
	}
	return false;
}
bool Maze::setDestination(const Point dest)
{
	if (testPoint(dest))
	{
		destination = dest;
		return true;
	}
	return false;
}
Point Maze::getSource()
{
	return source;
}
Point Maze::getDestination()
{
	return destination;
}
Point Maze::getCurrentPos()
{
	return curPos;
}
bool Maze::up()
{
	if (testPoint({ curPos.row - 1, curPos.col }))
	{
		curPos.row--;
		return true;
	}
	return false;
}
bool Maze::down()
{
	if (testPoint({ curPos.row + 1, curPos.col }))
	{
		curPos.row++;
		return true;
	}
	return false;
}
bool Maze::right()
{
	if (testPoint({ curPos.row, curPos.col + 1 }))
	{
		curPos.col++;
		return true;
	}
	return false;
}
bool Maze::left()
{
	if (testPoint({ curPos.row, curPos.col - 1 }))
	{
		curPos.col--;
		return true;
	}
	return false;
}
void Maze::displayMaze()
{
	for (int i = 0; i < noOfRows; i++)
	{
		//during display, S means source, D means
		//destination and [] will show current position

		for (int j = 0; j < noOfCols; j++)
		{
			Point cur(i, j);
			if (source == cur || destination == cur)
			{
				cout << ((curPos == cur) ? '[' : '\"')
					<< ((source == cur) ? 'S' : 'D')
					<< ((curPos == cur) ? ']' : '\"');
			}
			else
			{
				cout << ((curPos == cur) ? '[' : ' ')
					<< (bool)(maze[i][j])
					<< ((curPos == cur) ? ']' : ' ');
			}
		}
		cout << "\n\n";
	}
}
int& Maze::operator[](const Point p)
{
	return maze[p.row][p.col];
}
bool Maze::testPoint(Point p)
{
	return (p.col >= 0 && p.row >= 0 && p.col < noOfCols &&
		p.row < noOfRows && maze[p.row][p.col] == 1);
}
