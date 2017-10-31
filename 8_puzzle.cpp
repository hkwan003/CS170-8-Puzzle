#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include "8_puzzle.h"

using namespace std;

const int columns = 3;
const int rows = 3;
int puzzle[puzzle_size];
stack<boardLibrary> traceback;
vector<boardLibrary> newNodes;
vector<boardLibrary> visitedNodes;
int depth;

boardLibrary::boardLibrary()
{
	for (int i = 0; i < puzzle_size; i++)
	{
		parent[i] = 0;			//initalizes the default to zero array by default
	}
}
void boardLibrary::outputVector()
{
	cout << this->parent[0] << " " << this->parent[1] << " " << this->parent[2] << endl;
	cout << this->parent[3] << " " << this->parent[4] << " " << this->parent[5] << endl;
	cout << this->parent[6] << " " << this->parent[7] << " " << this->parent[8] << endl;
}
int boardLibrary::findZero()
{
	for (int i = 0; i < puzzle_size; i++)
	{
		if(this->parent[i] == 0)
		{
			return i;
		}
	}
	cout << "There is no zero on this puzzle board" << endl;
	return -1;
}
bool boardLibrary::goalCheck()
{
	if (this->parent[0] == 1 && this->parent[1] == 2 && this->parent[2] == 3 && this->parent[3] == 4 && this->parent[4] == 5 && this->parent[5] == 6 && this->parent[6] == 7 && this->parent[7] == 8 && this->parent[8] == 0)
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
void boardLibrary::moveRight(int x, boardLibrary root)
{
	if(x % columns < columns - 1)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		//cout << "move right" << endl;
		swap(childrenNode.parent[x + 1], childrenNode.parent[x]);	//perform swap operation on board
		//childrenNode.outputVector();
		childrenNode.predessor.push_back(root);
		newNodes.push_back(childrenNode);
		//childrenNode.outputVector();

	}
}
void boardLibrary::moveLeft(int x, boardLibrary root)
{
	if(x % columns > 0)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		//cout << "move left" << endl;
		swap(childrenNode.parent[x - 1], childrenNode.parent[x]);
		//childrenNode.outputVector();
		childrenNode.predessor.push_back(root);
		newNodes.push_back(childrenNode);
		//childrenNode.outputVector();
	}
}
void boardLibrary::moveUp(int x, boardLibrary root)
{
	if(x - columns >= 0)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		//cout << "move up" << endl;
		swap(childrenNode.parent[x - 3], childrenNode.parent[x]);
		//childrenNode.outputVector();
		childrenNode.predessor.push_back(root);
		newNodes.push_back(childrenNode);
		//childrenNode.outputVector();
	}
}
void boardLibrary::moveDown(int x, boardLibrary root)
{
	if(x + columns < puzzle_size)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		//cout << "move down" << endl;
		swap(childrenNode.parent[x + 3], childrenNode.parent[x]);
		//childrenNode.outputVector();
		childrenNode.predessor.push_back(root);
		newNodes.push_back(childrenNode);
		//childrenNode.outputVector();
	}
}
void boardLibrary::expansion(boardLibrary root)
{
	root.goalCheck();		//performs check if the goal matrix is found
	int zeroPos = root.findZero();

	moveRight(zeroPos, root);
	moveLeft(zeroPos, root);
	moveUp(zeroPos, root);
	moveDown(zeroPos, root);
}
bool boardLibrary::samePuzzle(boardLibrary node)
{
	bool samePuzzle = true;
	for (int i = 0; i < puzzle_size; i++)
	{
		if( parent[i] != node.parent[i])
		{
			samePuzzle = false;
		}
	}
	return samePuzzle;
}
bool contains(vector<boardLibrary> list, boardLibrary object)
{
	bool contains = false;

	for(int i = 0; i < list.size(); i++)
	{
		if(list[i].samePuzzle(object))
		{
			contains = true;
		}
	}
	return contains;
}
void boardLibrary::uniformSearch(boardLibrary node)
{
	cout << "Expanding State: " << endl;
	node.outputVector();
	cout << endl;
	newNodes.push_back(node);
	bool goalFound = false;

	while(newNodes.size() > 0 && !goalFound)
	{
		boardLibrary currentNode = newNodes.front();		//current node of system is first in newNodes
		visitedNodes.push_back(currentNode);				//puts the currentnode in the visited Queue
		if(currentNode.goalCheck() == false)
		{
			newNodes.erase(newNodes.begin());
			expansion(currentNode);
		}
		else
		{
			goalFound = true;
			cout << "Goal Found!!!" << endl;
			traceback.push(currentNode);
			pathtrace(currentNode);
		}
	}
}

void outputDepth()
{
	cout << "Depth of solution is: " << depth << endl;
}

bool boardLibrary::checkOrigMatrix(boardLibrary node)
{
	if (node.parent[0] == puzzle[0] && node.parent[1] == puzzle[1] && node.parent[2] == puzzle[2] && node.parent[3] == puzzle[3] && node.parent[4] == puzzle[4] && node.parent[5] == puzzle[5] && node.parent[6] == puzzle[6] && node.parent[7] == puzzle[7] && node.parent[8] == puzzle[8])
	{
		return true;
	}
	return false;

}



void boardLibrary::pathtrace(boardLibrary node)
{
	vector<boardLibrary> path;
	cout << "tracing path currently" << endl;

	while(checkOrigMatrix(node) != true)
	{
		depth++;
		node = node.predessor.front();
		traceback.push(node);
		//path.push_back(node);
	}

	while(!traceback.empty())
	{
		cout << "printing traceback: " << endl;
		boardLibrary obj = traceback.top();
		traceback.pop();
		obj.outputVector();
	}
}

int main()
{
	depth = 0;			//setting the g(n) = 0
	int userInput;
	cout << "Welcome to Calvin Kwan's 8-puzzle solver. " << endl;
	cout << "Type 1 to use default puzzle, or 2 to enter in your own puzzle: " << endl;
	cin >> userInput;
	if (userInput == 1)
	{
		puzzle[0] = 1;
		puzzle[1] = 0;
		puzzle[2] = 8;

		puzzle[3] = 4;
		puzzle[4] = 6;
		puzzle[5] = 2;

		puzzle[6] = 5;
		puzzle[7] = 3;
		puzzle[8] = 7;

		cout << endl;

		boardLibrary object;
		object.duplicateBoard(object.parent, puzzle);
		object.uniformSearch(object);
	}
	if(userInput == 2)
	{
		cout << "Please enter in your puzzle board using zero to represent your blank spot " << endl;
		cout << "Please enter in 3 numbers with spaces in between them: " << endl;
		int spot1, spot2, spot3;
		cin >> spot1 >> spot2 >> spot3; 
		puzzle[0] = spot1;
		puzzle[1] = spot2;
		puzzle[2] = spot3;
		// puzzle[0] = 0;
		// puzzle[1] = 1;
		// puzzle[2] = 2;

		cout << endl << "Please input in the second row of numbers with spaces in between them: " << endl;
		cin >> spot1 >> spot2 >> spot3;
		puzzle[3] = spot1;
		puzzle[4] = spot2;
		puzzle[5] = spot3;
		// puzzle[3] = 4;
		// puzzle[4] = 5;
		// puzzle[5] = 3;

		cout << endl << "Please input in the third row of numbers with spaces in between them: " << endl;
		cin >> spot1 >> spot2 >> spot3;
		puzzle[6] = spot1;
		puzzle[7] = spot2; 
		puzzle[8] = spot3;
		// puzzle[6] = 7;
		// puzzle[7] = 8;
		// puzzle[8] = 6;

		cout << endl;

		cout << "Enter your choice of algorithm: " << endl;
		cout << endl << "1. Uniform Cost Search ";
		cout << endl << "2. A* with Misplaced Tile heuristic ";
		cout << endl << "3. A* with Manhattan distance heuristic " << endl;
		cin >> userInput;
		if(userInput == 1)
		{
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.uniformSearch(object);
		}
		if(userInput == 2)
		{
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.uniformSearch(object);
			outputDepth();
		}
		
	}

}
