#include "MazeApp.h"
#include <Windows.h>



int MazeApp::isMovementPossible()
{
	int count = 0;
	if (testPoint({ curPos.row + 1, curPos.col }))
		count++;
	if (testPoint({ curPos.row - 1, curPos.col }))
		count++;
	if (testPoint({ curPos.row, curPos.col + 1 }))
		count++;
	if (testPoint({ curPos.row, curPos.col - 1 }))
		count++;
	return count;
}

bool MazeApp::isDeadEnd()
{
	//function will only be used when stack is not empty
	int count = 0;
	if (!isPointTraversed({ curPos.row + 1, curPos.col }) &&
		testPoint({ curPos.row + 1, curPos.col }))
		count++;
	if (!isPointTraversed({ curPos.row - 1, curPos.col }) &&
		testPoint({ curPos.row - 1, curPos.col }))
		count++;
	if (!isPointTraversed({ curPos.row, curPos.col + 1 }) &&
		testPoint({ curPos.row, curPos.col + 1 }))
		count++;
	if (!isPointTraversed({ curPos.row, curPos.col - 1 }) &&
		testPoint({ curPos.row, curPos.col - 1 }))
		count++;

	if (!count)
		return true;
	return false;
}

bool MazeApp::backtrack()
{
	if (stack.isEmpty())
		return false;
	maze[curPos.row][curPos.col] = -2;
	setCurrentPos(stack.pop());
	return true;
}

MazeApp::MazeApp(const int _noOfRows, const int _noOfCols) 
	:Maze(_noOfRows, _noOfCols)
{
}

MazeApp::MazeApp(const int _noOfRows, const int _noOfCols,
	const Point src, const Point dest) : Maze(_noOfRows, _noOfCols,
		src, dest)
{
}



bool MazeApp::traverse()
{
	srand(time(0));
	setCurrentPos(getSource());

	bool possible = true;

	while (getCurrentPos() != getDestination() && possible)
	{
		//check if any movement possible or not (including backtracking)
		if(!isMovementPossible())	
			possible = false;
		else if (stack.getNumberOfElements() && isDeadEnd())
			backtrack();
		else
		{
			//move any random possible direction
			bool moved;
			int random = rand() % 4;
			do
			{
				Point previousPoint(this->getCurrentPos());

				if (random == 0)
					moved = up();
				if (random == 1)
					moved = down();
				if (random == 2)
					moved = left();
				if (random == 3)
					moved = right();

				random = (random + 1) % 4;
				if (moved)
					stack.push(previousPoint);
			} while (!moved);
		}
		displayMaze();
		Sleep(100);
		system("CLS");
	}
	return possible;
}

void MazeApp::start()
{
	int ROW_SIZE;
	int COL_SIZE;
	do
	{
		cout << "\t\tMAZE SOLVER\n";
		cout << "\t\t-----------\n\n";
		cout << "Enter Maze rowSize: ";
		cin >> ROW_SIZE;
		cout << "Enter Maze colSize: ";
		cin >> COL_SIZE;
		if (!ROW_SIZE || !COL_SIZE)
		{
			cout << "\nInvalid Input!\n";
			Sleep(300);
			system("cls");
		}
	} while (!ROW_SIZE || !COL_SIZE);
	system("CLS");


	cout << "\t\tMAZE SOLVER\n";
	cout << "\t\t-----------\n\n";
	MazeApp m(ROW_SIZE, COL_SIZE);
	m.displayMaze();
	Sleep(500);
	system("CLS");


	cout << "Enter Board:\n";
	int** board = new int* [ROW_SIZE];
	for (int i = 0; i < ROW_SIZE; i++)
		board[i] = new int[COL_SIZE];
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
			cin >> board[i][j];
	}
	system("CLS");

	m.setMaze(board);
	Point s, d;
	cout << "\t\tMAZE SOLVER\n";
	cout << "\t\t-----------\n\n";
	cout << "Enter Source: ";
	cin >> s.row;
	cin >> s.col;
	m.setSource(s);
	cout << "Enter Destination: ";
	cin >> d.row;
	cin >> d.col;
	m.setDestination(d);
	cout << "\n";
	m.displayMaze();
	system("PAUSE");
	system("CLS");

	cout << "\t\tMAZE SOLVER\n";
	cout << "\t\t-----------\n\n";
	cout << "NOW START TRAVERSING!\n";
	system("PAUSE");
	system("CLS");

	cout << "\t\tMAZE SOLVER\n";
	cout << "\t\t-----------\n\n";
	if (m.traverse())
		cout << "Path Possible\n\n\n";
	else
		cout << "Path not Possible\n\n\n";
}

bool MazeApp::isPointTraversed(const Point p)
{
	//if given point is traversed, it will be present in stack
	//so search it in stack
	Stack<Point> temp(stack);
	while(temp.getNumberOfElements())
	{
		Point tempPoint(temp.pop());
		if (tempPoint == p)
			return true;
	}
	return false;
}

bool MazeApp::up()
{
	if (!isPointTraversed({ getCurrentPos().row - 1, getCurrentPos().col })
		&& Maze::up())
		return true;
	return false;
}
bool MazeApp::down()
{
	if (!isPointTraversed({ getCurrentPos().row + 1, getCurrentPos().col })
		&& Maze::down())
		return true;
	return false;
}
bool MazeApp::left()
{
	if (!isPointTraversed({ getCurrentPos().row, getCurrentPos().col - 1 })
		&& Maze::left())
		return true;
	return false;
}
bool MazeApp::right()
{
	if (!isPointTraversed({ getCurrentPos().row, getCurrentPos().col + 1 })
		&& Maze::right())
		return true;
	return false;
}