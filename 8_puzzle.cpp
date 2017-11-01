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
int maxNewNodes = 0;
int maxNewPriority = 0;
int puzzle[puzzle_size];
int tracebackCtr = 0;
int nodeCreationCtr = 0;
stack<boardLibrary> traceback;
vector<boardLibrary> newNodes;
vector<boardLibrary> visitedNodes;

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
void boardLibrary::moveRight(int x, boardLibrary root, int choice)
{
	if(x % columns < columns - 1)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		//cout << "move right" << endl;
		swap(childrenNode.parent[x + 1], childrenNode.parent[x]);	//perform swap operation on board
		childrenNode.predessor.push_back(root);
		childrenNode.depth = childrenDepth;
		if(choice == 1)
		{
			newNodes.push_back(childrenNode);
			childrenNode.heuristic = 0;
		}
		if(choice == 2)
		{
			childrenNode.heuristic = childrenNode.checkMisplace(childrenNode);
			priorityQ.push(childrenNode);
		}
		if(choice == 3)
		{
			childrenNode.manhattan();
			priorityQ.push(childrenNode);
		}
	}
	checkNewNodesSize();
	checkPriorityQSize();
}
void boardLibrary::moveLeft(int x, boardLibrary root, int choice)
{
	if(x % columns > 0)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		//cout << "move left" << endl;
		swap(childrenNode.parent[x - 1], childrenNode.parent[x]);
		childrenNode.predessor.push_back(root);
		childrenNode.depth = childrenDepth;
		if(choice == 1)
		{
			newNodes.push_back(childrenNode);
			childrenNode.heuristic = 0;
		}
		if(choice == 2)
		{
			childrenNode.heuristic = childrenNode.checkMisplace(childrenNode);
			priorityQ.push(childrenNode);
		}
		if(choice == 3)
		{
			childrenNode.manhattan();
			priorityQ.push(childrenNode);
		}
	}
	checkNewNodesSize();
	checkPriorityQSize();
}
void boardLibrary::moveUp(int x, boardLibrary root, int choice)
{
	if(x - columns >= 0)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		//cout << "move up" << endl;
		swap(childrenNode.parent[x - 3], childrenNode.parent[x]);
		childrenNode.predessor.push_back(root);
		childrenNode.depth = childrenDepth;
		if(choice == 1)
		{
			newNodes.push_back(childrenNode);
			childrenNode.heuristic = 0;
		}
		if(choice == 2)
		{
			childrenNode.heuristic = childrenNode.checkMisplace(childrenNode);
			priorityQ.push(childrenNode);
		}
		if(choice == 3)
		{
			childrenNode.manhattan();
			priorityQ.push(childrenNode);
		}
	}
	checkNewNodesSize();
	checkPriorityQSize();
}
void boardLibrary::moveDown(int x, boardLibrary root, int choice)
{
	if(x + columns < puzzle_size)
	{
		boardLibrary childrenNode;
		duplicateBoard(childrenNode.parent, root.parent);
		swap(childrenNode.parent[x + 3], childrenNode.parent[x]);
		childrenNode.predessor.push_back(root);
		childrenNode.depth = childrenDepth;
		if(choice == 1)
		{
			newNodes.push_back(childrenNode);
			childrenNode.heuristic = 0;
		}
		if(choice == 2)
		{
			childrenNode.heuristic = childrenNode.checkMisplace(childrenNode);
			priorityQ.push(childrenNode);
		}
		if(choice == 3)
		{
			childrenNode.manhattan();
			priorityQ.push(childrenNode);
		}
	}
	checkNewNodesSize();
	checkPriorityQSize();
}
void boardLibrary::expansion(boardLibrary root, int x)
{
	root.goalCheck();		//performs check if the goal matrix is found
	int zeroPos = root.findZero();
	childrenDepth++;
	nodeCreationCtr++;
	moveRight(zeroPos, root, x);
	moveLeft(zeroPos, root, x);
	moveUp(zeroPos, root, x);
	moveDown(zeroPos, root, x);
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
void boardLibrary::checkNewNodesSize()
{
	int temp = newNodes.size();
	if(temp > maxNewNodes)
	{
		maxNewNodes = newNodes.size();
	}
}
void boardLibrary::checkPriorityQSize()
{
	int temp = priorityQ.size();
	if(temp > maxNewPriority)
	{
		maxNewPriority = priorityQ.size();
	}
}
void boardLibrary::uniformSearch(boardLibrary node, int choice)
{
	cout << "Expanding State: " << endl;
	node.outputVector();
	cout << endl;
	newNodes.push_back(node);
	checkNewNodesSize();
	bool goalFound = false;

	while(newNodes.size() > 0 && !goalFound)
	{
		boardLibrary currentNode = newNodes.front();		//current node of system is first in newNodes
		visitedNodes.push_back(currentNode);				//puts the currentnode in the visited Queue
		if(currentNode.goalCheck() == false)
		{
			newNodes.erase(newNodes.begin());
			expansion(currentNode, choice);
		}
		else
		{
			goalFound = true;
			cout << "Goal Found!!!" << endl;
			currentNode.heuristic = 0;
			traceback.push(currentNode);
			pathtrace(currentNode, choice);
		}
	}
}

void outputSummary(int x)
{
	cout << endl;
	cout << "To solve this problem the search algorithm expanded a total of " << nodeCreationCtr << " nodes." << endl;
	if(x == 1)
	{
		cout << "The maximum number of nodes in the queue at any one time was " << maxNewNodes << " ." << endl;
	}
	else
	{
		cout << "The maximum number of nodes in the queue at any one time was " << maxNewPriority << " ." << endl;
	}
	cout << "The depth of the goal node was " << tracebackCtr << endl;
}

bool boardLibrary::checkOrigMatrix(boardLibrary node)
{
	if (node.parent[0] == puzzle[0] && node.parent[1] == puzzle[1] && node.parent[2] == puzzle[2] && node.parent[3] == puzzle[3] && node.parent[4] == puzzle[4] && node.parent[5] == puzzle[5] && node.parent[6] == puzzle[6] && node.parent[7] == puzzle[7] && node.parent[8] == puzzle[8])
	{
		return true;
	}
	return false;

}

void boardLibrary::manhattan()
{
	int one = 0;
	int two = 1;
	int three = 2;
	int four = 3;
	int five = 4;
	int six = 5;
	int seven = 6;
	int eight = 7;
	int heuristicCtr = 0;
	for(int i = 0; i < puzzle_size; i++)
	{
		if(this->parent[i] != 0)
		{
			if(this->parent[i] == 1)
			{
				int temp = (abs(i - one));
				if(temp == 1 || temp == 3)
				{
					heuristicCtr += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					heuristicCtr += 2;
				}
				if(temp == 5 || temp == 7)
				{
					heuristicCtr += 3;
				}
				if(temp == 8)
				{
					heuristicCtr += 4;
				}

			}
			if(this->parent[i] == 2)
			{
				int temp = (abs(i - two));
				if(temp == 1 || temp == 3)
				{
					heuristicCtr += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					heuristicCtr += 2;
				}
				if(temp == 5 || temp == 7)
				{
					heuristicCtr += 3;
				}
				if(temp == 8)
				{
					heuristicCtr += 4;
				}	
			}
			if(this->parent[i] == 3)
			{
				int temp = (abs(i - three));
				if(temp == 1 || temp == 3)
				{
					heuristicCtr += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					heuristicCtr += 2;
				}
				if(temp == 5 || temp == 7)
				{
					heuristicCtr += 3;
				}
				if(temp == 8)
				{
					heuristicCtr += 4;
				}
			}
			if(this->parent[i] == 4)
			{
				int temp = (abs(i - four));
				if(temp == 1 || temp == 3)
				{
					heuristicCtr += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					heuristicCtr += 2;
				}
				if(temp == 5 || temp == 7)
				{
					heuristicCtr += 3;
				}
				if(temp == 8)
				{
					heuristicCtr += 4;
				}
			}
			if(this->parent[i] == 5)
			{
				// cout << "does it go in here?" << endl;
				int temp = (abs(i - five));
				if(temp == 1 || temp == 3)
				{
					heuristicCtr += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					heuristicCtr += 2;
				}
				if(temp == 5 || temp == 7)
				{
					heuristicCtr += 3;
				}
				if(temp == 8)
				{
					heuristicCtr += 4;
				}
			}
			if(this->parent[i] == 6)
			{
				int temp = (abs(i - six));
				if(temp == 1 || temp == 3)
				{
					heuristicCtr += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					heuristicCtr += 2;
				}
				if(temp == 5 || temp == 7)
				{
					heuristicCtr += 3;
				}
				if(temp == 8)
				{
					heuristicCtr += 4;
				}
			}
			if(this->parent[i] == 7)
			{
				int temp = (abs(i - seven));
				if(temp == 1 || temp == 3)
				{
					heuristicCtr += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					heuristicCtr += 2;
				}
				if(temp == 5 || temp == 7)
				{
					heuristicCtr += 3;
				}
				if(temp == 8)
				{
					heuristicCtr += 4;
				}
			}
			if(this->parent[i] == 8)
			{
				int temp = (abs(i - eight));
				if(temp == 1 || temp == 3)
				{
					heuristicCtr += 1;
				}
				if(temp == 2 || temp == 4 || temp == 6)
				{
					heuristicCtr += 2;
				}
				if(temp == 5 || temp == 7)
				{
					heuristicCtr += 3;
				}
				if(temp == 8)
				{
					heuristicCtr += 4;
				}
			}
		}
	}
	this->heuristic = heuristicCtr;
}

void boardLibrary::ManhattanDistanceSearch(boardLibrary node, int choice)
{
	node.depth = 0;
	node.manhattan();
	priorityQ.push(node);
	bool goalFound = false;

	while(priorityQ.size() > 0 && !goalFound)
	{
		boardLibrary currentNode = priorityQ.top();
		visitedNodes.push_back(currentNode);
		checkPriorityQSize();
		if(currentNode.goalCheck() == false)
		{
			priorityQ.pop();
			expansion(currentNode, choice);
		}
		else
		{
			goalFound = true;
			cout << "Goal Found!!!" << endl;
			traceback.push(currentNode);
			pathtrace(currentNode, choice);
		}
	}
}

void boardLibrary::misplaced(boardLibrary node, int choice)
{
	node.depth = 0;
	node.heuristic = checkMisplace(node);
	priorityQ.push(node);
	bool goalFound = false;

	while(priorityQ.size() > 0 && !goalFound)
	{
		boardLibrary currentNode = priorityQ.top();
		visitedNodes.push_back(currentNode);
		checkPriorityQSize();
		if(currentNode.goalCheck() == false)
		{
			priorityQ.pop();
			expansion(currentNode, choice);
		}
		else
		{
			goalFound = true;
			cout << "Goal Found!!!" << endl;
			traceback.push(currentNode);
			pathtrace(currentNode, choice);
		}
	}
}
void boardLibrary::pathtrace(boardLibrary node, int choice)
{
	vector<boardLibrary> path;

	while(checkOrigMatrix(node) != true)
	{
		depth++;
		node = node.predessor.front();
		traceback.push(node);
		//path.push_back(node);
	}

	while(!traceback.empty())
	{
		boardLibrary obj = traceback.top();
		traceback.pop();
		if(choice == 3)
		{
			obj.manhattan();
		}
		cout << "The best state to expand with a g(n) = " << tracebackCtr << " and h(n) = " << obj.heuristic << " is..." << endl;
		obj.outputVector();
		tracebackCtr++;
		if(!traceback.empty())
		{
			cout << endl << "Expanding this node...." << endl;
		}
	}

	outputSummary(choice);
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
	cout << endl << "Welcome to Calvin Kwan's 8-puzzle solver. " << endl;
	cout << "Type 1 to use default puzzle, or 2 to enter in your own puzzle: " << endl;
	cin >> userInput;
	if (userInput == 1)
	{
		puzzle[0] = 1;
		puzzle[1] = 2;
		puzzle[2] = 3;

		puzzle[3] = 4;
		puzzle[4] = 0;
		puzzle[5] = 6;

		puzzle[6] = 7;
		puzzle[7] = 5;
		puzzle[8] = 8;

		cout << "Enter your choice of algorithm: " << endl;
		cout << endl << "1. Uniform Cost Search ";
		cout << endl << "2. A* with Misplaced Tile heuristic ";
		cout << endl << "3. A* with Manhattan distance heuristic " << endl;
		cin >> userInput;
		if(userInput == 1)
		{
			cout << endl;
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.uniformSearch(object, userInput);
		}
		if(userInput == 2)
		{
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.misplaced(object, userInput);
			userInput = 0;
		}
		if(userInput == 3)
		{
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.ManhattanDistanceSearch(object, userInput);
			userInput = 0;
		}
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
		cout << endl << "Please input in the second row of numbers with spaces in between them: " << endl;
		cin >> spot1 >> spot2 >> spot3;
		puzzle[3] = spot1;
		puzzle[4] = spot2;
		puzzle[5] = spot3;
		cout << endl << "Please input in the third row of numbers with spaces in between them: " << endl;
		cin >> spot1 >> spot2 >> spot3;
		puzzle[6] = spot1;
		puzzle[7] = spot2; 
		puzzle[8] = spot3;

		cout << endl;
		cout << "Enter your choice of algorithm: " << endl;
		cout << endl << "1. Uniform Cost Search ";
		cout << endl << "2. A* with Misplaced Tile heuristic ";
		cout << endl << "3. A* with Manhattan distance heuristic " << endl;
		cin >> userInput;
		if(userInput == 1)
		{
			cout << endl;
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.uniformSearch(object, userInput);
		}
		if(userInput == 2)
		{
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.misplaced(object, userInput);
		}
		if(userInput == 3)
		{
			boardLibrary object;
			object.duplicateBoard(object.parent, puzzle);
			object.ManhattanDistanceSearch(object, userInput);
		}
		
	}

}
