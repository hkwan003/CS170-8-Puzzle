#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include "8_puzzle.h"

using namespace std;

const int columns = 3;
const int rows = 3;
int zero, one, two, three, four, five, six, seven, eight, nine;

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
		cout << "move right" << endl;
		//outputVector();
		swap(childrenNode.parent[x + 1], childrenNode.parent[x]);	//perform swap operation on board
		childrenNode.predessor.push_back(root);
		children.push_back(childrenNode);
		childrenNode.outputVector();

	}
}
void boardLibrary::moveLeft(int x, boardLibrary root)
{
	if(x % columns > 0)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		cout << "move left" << endl;
		//outputVector();
		swap(childrenNode.parent[x - 1], childrenNode.parent[x]);
		childrenNode.predessor.push_back(root);
		children.push_back(childrenNode);
		childrenNode.outputVector();
	}
}
void boardLibrary::moveUp(int x, boardLibrary root)
{
	if(x - columns >= 0)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		cout << "move up" << endl;
		//outputVector();
		swap(childrenNode.parent[x - 3], childrenNode.parent[x]);
		childrenNode.predessor.push_back(root);
		children.push_back(childrenNode);
		childrenNode.outputVector();
	}
}
void boardLibrary::moveDown(int x, boardLibrary root)
{
	if(x + columns < puzzle_size)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		cout << "move down" << endl;
		//outputVector();
		swap(childrenNode.parent[x + 3], childrenNode.parent[x]);
		childrenNode.predessor.push_back(root);
		children.push_back(childrenNode);
		childrenNode.outputVector();
	}
}
void boardLibrary::expansion(boardLibrary root)
{
	root.outputVector();
	cout << "prior to expansion: " << endl;
	root.goalCheck();		//performs check if the goal matrix is found
	int zeroPos = root.findZero();

	moveRight(zeroPos, root);
	moveLeft(zeroPos, root);
	moveUp(zeroPos, root);
	moveDown(zeroPos, root);

	cout << "expansion is finished: " << endl;
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
	cout << "is this being called:" << endl;
	vector<boardLibrary> newNodes;
	vector<boardLibrary> visitedNodes;

	newNodes.push_back(node);
	bool goalFound = false;

	while(newNodes.size() > 0 && !goalFound)
	{
		//cout << "size of newNodes: " << newNodes.size() << endl;

		boardLibrary currentNode = newNodes.front();		//current node of system is first in newNodes
		//cout << "output a set of the first nodes: " << endl;
		currentNode.outputVector();
		visitedNodes.push_back(currentNode);				//puts the currentnode in the visited Queue
		cout << "size of VisitedNodes: " << visitedNodes.size() << endl;
		newNodes.erase(newNodes.begin());								//removes it from list of nodes needing to be seen

		expansion(currentNode);
		cout << "output children size: " << currentNode.children.size() << endl;

		for(int i  = 0; i < this->children.size(); i++)
		{
			//cout << "is this even entering into this? " << endl;  
			boardLibrary currentChild = this->children[i];
			if(currentChild.goalCheck())
			{
				cout << "Goal Found!!!!" << endl;
				goalFound = true;
				currentChild.outputVector();
				pathtrace(currentChild);
			}
			if(!contains(newNodes, currentChild) && !contains(visitedNodes, currentChild))
			{
				newNodes.push_back(currentChild);
			}
		}
	}
}

bool boardLibrary::checkOrigMatrix(boardLibrary node)
{
	if (node.parent[0] == 1 && node.parent[1] == 2 && node.parent[2] == 3 && node.parent[3] == 4 && node.parent[4] == 6 && node.parent[5] == 0 && node.parent[6] == 7 && node.parent[7] == 5 && node.parent[8] == 8)
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
		node = node.predessor.front();
		cout << "outputting each iteration in between: " << endl;
		node.outputVector();
		path.push_back(node);
	}
}

int main()
{
	int puzzle[puzzle_size];
	int userInput;
	cout << "Welcome to Calvin Kwan's 8-puzzle solver. " << endl;
	cout << "Type 1 to use default puzzle, or 2 to enter in your own puzzle: " << endl;
	cin >> userInput;
	if (userInput == 1)
	{
		puzzle[0] = 1;
		puzzle[1] = 2;
		puzzle[2] = 3;

		puzzle[3] = 4;
		puzzle[4] = 6;
		puzzle[5] = 0;

		puzzle[6] = 7;
		puzzle[7] = 5;
		puzzle[8] = 8;

		cout << endl;

		boardLibrary object;
		object.duplicateBoard(object.parent, puzzle);
		object.uniformSearch(object);


	}
	cout << "Please enter in your puzzle board using zero to represent your blank spot " << endl;
	cout << "Please enter in 3 numbers with spaces in between them: " << endl;
	int spot1, spot2, spot3;
	//cin >> spot1 >> spot2 >> spot3; 
	// zero = 1;
	// one = 2;
	// three = 3;
	puzzle[0] = 1;
	puzzle[1] = 2;
	puzzle[2] = 3;

	cout << endl << "Please input in the second row of numbers with spaces in between them: " << endl;
	//cin >> spot1 >> spot2 >> spot3;
	// four = 4;
	// five = 6;
	// six = 0;
	puzzle[3] = 4;
	puzzle[4] = 6;
	puzzle[5] = 0;

	cout << endl << "Please input in the third row of numbers with spaces in between them: " << endl;
	//cin >> spot1 >> spot2 >> spot3;
	seven = 7;
	eight = 5; 
	nine = 8;
	puzzle[6] = 7;
	puzzle[7] = 5;
	puzzle[8] = 8;

	cout << endl;

	boardLibrary object;
	object.duplicateBoard(object.parent, puzzle);
	object.uniformSearch(object);

}
