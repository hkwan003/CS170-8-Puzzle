#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <cmath>
#include "8_puzzle.h"

using namespace std;

struct overLoadComparsion
{
	bool operator()(const boardLibrary node1, const boardLibrary node2)
	{
		return (node1.depth + node1.heuristic) > (node2.depth + node2.heuristic);
	}
};

const int columns = 3;
const int rows = 3;
int puzzle[puzzle_size];
stack<boardLibrary> traceback;
vector<boardLibrary> newNodes;
vector<boardLibrary> visitedNodes;

// bool overLoadComparsion(boardLibrary node1, boardLibrary node2)
// {
// 	return true;
// }
priority_queue< boardLibrary, vector<boardLibrary> , overLoadComparsion >priorityQ; //make min-heap
int depth;
int childrenDepth = 0;


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

void boardLibrary::outputVector(int nodeParent[9])
{
	cout << nodeParent[0] << " " << nodeParent[1] << " " << nodeParent[2] << endl;
	cout << nodeParent[3] << " " << nodeParent[4] << " " << nodeParent[5] << endl;
	cout << nodeParent[6] << " " << nodeParent[7] << " " << nodeParent[8] << endl;
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
		childrenNode.depth = childrenDepth;
		childrenNode.heuristic = childrenNode.checkMisplace(childrenNode);
		cout << "children depth: " << childrenNode.depth << " childrenNode heuristic: " << childrenNode.heuristic << endl;
		childrenNode.outputVector();
		cout << endl;
		childrenNode.predessor.push_back(root);
		newNodes.push_back(childrenNode);
		priorityQ.push(childrenNode);
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
		childrenNode.depth = childrenDepth;
		childrenNode.heuristic = childrenNode.checkMisplace(childrenNode);
		cout << "children depth: " << childrenNode.depth << " childrenNode heuristic: " << childrenNode.heuristic << endl;
		childrenNode.outputVector();
		cout << endl;
		childrenNode.predessor.push_back(root);
		newNodes.push_back(childrenNode);
		priorityQ.push(childrenNode);
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
		childrenNode.depth = childrenDepth;
		childrenNode.heuristic = childrenNode.checkMisplace(childrenNode);
		cout << "children depth: " << childrenNode.depth << " childrenNode heuristic: " << childrenNode.heuristic << endl;
		childrenNode.outputVector();
		cout << endl;
		childrenNode.predessor.push_back(root);
		newNodes.push_back(childrenNode);
		priorityQ.push(childrenNode);
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
		childrenNode.depth = childrenDepth;
		childrenNode.heuristic = childrenNode.checkMisplace(childrenNode);
		cout << "children depth: " << childrenNode.depth << " childrenNode heuristic: " << childrenNode.heuristic << endl;
		childrenNode.outputVector();
		cout << endl;
		childrenNode.predessor.push_back(root);
		newNodes.push_back(childrenNode);
		priorityQ.push(childrenNode);
		//childrenNode.outputVector();
	}
}
void boardLibrary::expansion(boardLibrary root)
{
	root.goalCheck();		//performs check if the goal matrix is found
	int zeroPos = root.findZero();
	childrenDepth++;
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

void boardLibrary::manhattan(boardLibrary node)
{
	int one = 0;
	int two = 1;
	int three = 2;
	int four = 3;
	int five = 4;
	int six = 5;
	int seven = 6;
	int eight = 7;

	for(int i = 0; i < puzzle_size; i++)
	{
		if(node.parent[i] != 0)
		{
			if(node.parent[i] == 1)
			{
				int temp = (abs(i - one));
				if(temp == 1 || temp == 3)
				{
					node.heuristic += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					node.heuristic += 2;
				}
				if(temp == 5 || temp == 7)
				{
					node.heuristic += 3;
				}
				if(temp == 8)
				{
					node.heuristic += 4;
				}

			}
			if(node.parent[i] == 2)
			{
				int temp = (abs(i - two));
				if(temp == 1 || temp == 3)
				{
					node.heuristic += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					node.heuristic += 2;
				}
				if(temp == 5 || temp == 7)
				{
					node.heuristic += 3;
				}
				if(temp == 8)
				{
					node.heuristic += 4;
				}	
			}
			if(node.parent[i] == 3)
			{
				int temp = (abs(i - three));
				if(temp == 1 || temp == 3)
				{
					node.heuristic += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					node.heuristic += 2;
				}
				if(temp == 5 || temp == 7)
				{
					node.heuristic += 3;
				}
				if(temp == 8)
				{
					node.heuristic += 4;
				}
			}
			if(node.parent[i] == 4)
			{
				int temp = (abs(i - four));
				if(temp == 1 || temp == 3)
				{
					node.heuristic += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					node.heuristic += 2;
				}
				if(temp == 5 || temp == 7)
				{
					node.heuristic += 3;
				}
				if(temp == 8)
				{
					node.heuristic += 4;
				}
			}
			if(node.parent[i] == 5)
			{
				cout << "does it go in here?" << endl;
				int temp = (abs(i - five));
				if(temp == 1 || temp == 3)
				{
					node.heuristic += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					node.heuristic += 2;
				}
				if(temp == 5 || temp == 7)
				{
					node.heuristic += 3;
				}
				if(temp == 8)
				{
					node.heuristic += 4;
				}
			}
			if(node.parent[i] == 6)
			{
				int temp = (abs(i - six));
				if(temp == 1 || temp == 3)
				{
					node.heuristic += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					node.heuristic += 2;
				}
				if(temp == 5 || temp == 7)
				{
					node.heuristic += 3;
				}
				if(temp == 8)
				{
					node.heuristic += 4;
				}
			}
			if(node.parent[i] == 7)
			{
				int temp = (abs(i - seven));
				if(temp == 1 || temp == 3)
				{
					node.heuristic += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					node.heuristic += 2;
				}
				if(temp == 5 || temp == 7)
				{
					node.heuristic += 3;
				}
				if(temp == 8)
				{
					node.heuristic += 4;
				}
			}
			if(node.parent[i] == 8)
			{
				int temp = (abs(i - eight));
				if(temp == 1 || temp == 3)
				{
					node.heuristic += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					node.heuristic += 2;
				}
				if(temp == 5 || temp == 7)
				{
					node.heuristic += 3;
				}
				if(temp == 8)
				{
					node.heuristic += 4;
				}
			}
		}
	}
	cout << endl;
	node.outputVector();
	cout << endl;
	cout << "Manhattan distance: " << node.heuristic << endl;

}

void boardLibrary::misplaced(boardLibrary node)
{
	cout << "inside of misplaced tile heuristic" << endl;
	node.depth = 0;
	node.heuristic = checkMisplace(node);
	priorityQ.push(node);
	bool goalFound = false;

	while(priorityQ.size() > 0 && !goalFound)
	{
		boardLibrary currentNode = priorityQ.top();
		visitedNodes.push_back(currentNode);
		if(currentNode.goalCheck() == false)
		{
			priorityQ.pop();
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

int boardLibrary::checkMisplace(boardLibrary node)
{
	int cost = 0;
	if(node.parent[0] != 1)
	{
		cost++;
	}
	if(node.parent[1] != 2)
	{
		cost++;
	}
	if(node.parent[2] != 3)
	{
		cost++;
	}
	if(node.parent[3] != 4)
	{
		cost++;
	}
	if(node.parent[4] != 5)
	{
		cost++;
	}
	if(node.parent[5] != 6)
	{
		cost++;
	}
	if(node.parent[6] != 7)
	{
		cost++;
	}
	if(node.parent[7] != 8)
	{
		cost++;
	}
	return cost;
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
			object.misplaced(object);
			//object.uniformSearch(object);
			//cout << "Misplace tile cost: " << object.checkMisplace(object) << endl;
			//outputDepth();
		}
		if(userInput == 3)
		{
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.manhattan(object);
		}
		
	}

}
