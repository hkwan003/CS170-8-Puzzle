#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include "8_puzzle.h"

using namespace std;

const int puzzle_size = 9;
const int columns = 3;
const int rows = 3;

boardLibrary::boardLibrary()
{}

void boardLibrary::outputVector(int arr[puzzle_size])
{
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void boardLibrary::findZero(int arr[puzzle_size])
{
	for (int i = 0; i < puzzle_size; i++)
	{
		if(arr[i] == 0)
		{
			cout << "position of zero is at: " << i << endl;
		}
	}
}

bool boardLibrary::goalCheck(int arr[puzzle_size])
{
	if (arr[0] == 0 && arr[1] == 1 && arr[2] == 2 && arr[3] == 3 && arr[4] == 4&& arr[5] == 5 && arr[6] == 6 && arr[7] == 7 && arr[8] == 8 &&  arr[9] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void boardLibrary::duplicateBoard(int destBoard[puzzle_size], int origBoard[puzzle_size])
{
	for (int i = 0; i < puzzle_size; i++)
	{
		destBoard[i] = origBoard[i];
	}
}

void boardLibrary::moveRight(int x, int root[puzzle_size])
{
	boardLibrary tempObj;
	if(x % columns < columns - 1)
	{
		int childBoard[puzzle_size];
		tempObj.duplicateBoard(childBoard, root);
		swap(childBoard[x + 1], childBoard[x]);	//perform swap operation on board
		cout << "shifted vector:" << endl;
		tempObj.outputVector(childBoard);	//does check to output new shifted vector
		tempObj.duplicateBoard(parent, root);	//copies the parent to the parent variable
		
		cout << "display parent: " << endl;
		tempObj.outputVector(parent);


	}
}

void boardLibrary::moveLeft(int x, int root[puzzle_size])
{
	boardLibrary tempObj;
	if(x % columns > 0)
	{
		int childBoard[puzzle_size];
		tempObj.duplicateBoard(childBoard, root);
		swap(childBoard[x - 1], childBoard[x]);
		tempObj.duplicateBoard(parent, root);

	}
}

void boardLibrary::moveUp(int x, int root[puzzle_size])
{
	boardLibrary tempObj;
	if(x - columns >= 0)
	{
		int childBoard[puzzle_size];
		tempObj.duplicateBoard(childBoard, root);
		swap(childBoard[i - 3], childBoard[i]);
		tempObj.duplicateBoard(parent, root);
	}
}

void boardLibrary::moveDown(int x, int root[puzzle_size])
{
	boardLibrary tempObj;
	if(x + columns < puzzle_size)
	{
		int childBoard[puzzle_size];
		tempObj.duplicateBoard(childBoard, root);
		swap(childBoard[x + 3], childBoard[x]);
		tempObj.duplicateBoard(parent, root);
	}
}


int main()
{
	int puzzle[puzzle_size];
	cout << "Please enter in your puzzle board using zero to represent your blank spot " << endl;
	cout << "Please enter in 3 numbers with spaces in between them: " << endl;
	int spot1, spot2, spot3;
	//cin >> spot1 >> spot2 >> spot3; 
	puzzle[0] = 1;
	puzzle[1] = 2;
	puzzle[2] = 3;

	cout << endl << "Please input in the second row of numbers with spaces in between them: " << endl;
	//cin >> spot1 >> spot2 >> spot3;
	puzzle[3] = 4;
	puzzle[4] = 0;
	puzzle[5] = 5;

	cout << endl << "Please input in the third row of numbers with spaces in between them: " << endl;
	//cin >> spot1 >> spot2 >> spot3;
	puzzle[6] = 6;
	puzzle[7] = 7;
	puzzle[8] = 8;

	cout << endl;

	boardLibrary object;
	object.outputVector(puzzle);
	cout << "output second puzzle " << endl;
	//object.findZero(puzzle);
	object.moveRight(4, puzzle);
}
