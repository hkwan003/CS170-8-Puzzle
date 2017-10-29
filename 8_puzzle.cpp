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

void boardLibrary::outputVector(int arr[9])
{
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void boardLibrary::findZero(int arr[9])
{
	for (int i = 0; i < puzzle_size; i++)
	{
		if(arr[i] == 0)
		{
			cout << "position of zero is at: " << i << endl;
		}
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
	object.findZero(puzzle);
}

//class puzzle
// {
// 	struct Node {
// 		list<Node> children;
// 		Node *parent;
// 		int *board_setup = new int[9];
// 		int x = 0;
// 	};

// 	bool puzzleGoal(int test[9])
// 	{
// 		int start_value = test[0];
// 		for(int i = 1; i < puzzle_size - 1; i++)
// 		{
// 			if(start_value > test[i])
// 			{
// 				return false;
// 			}
// 			else
// 			{
// 				start_value = test[i];
// 			}
// 		}
// 		return true;
// 	}

// 	void moveRight(int temp[9], int i)
// 	{
// 		if(i % columns < columns - 1)
// 		{
			
// 		}
// 	}
// 	void moveLeft(int temp[9], int i)
// 	{
		
// 	}
// 	void moveUp(int temp[9], int i)
// 	{
		
// 	}
// 	void moveDown(int temp[9], int i)
// 	{
		
// 	}
// };