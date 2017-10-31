#include <vector>

using namespace std;

const int puzzle_size = 9;

class boardLibrary
{
	// private:
	// 	int parent[puzzle_size];
	// 	list<boardLibrary> children;

	private:

	public:
		boardLibrary();
		int parent[puzzle_size];
		vector<boardLibrary> children;
		vector<boardLibrary> predessor;
		int depth;
		int heuristic;
		void moveUp(int x, boardLibrary root);
		void moveDown(int x, boardLibrary root);
		void moveLeft(int x, boardLibrary root);
		void moveRight(int x, boardLibrary root);
		int findZero();
		void outputVector();
		void outputVector(int origpuzzle[puzzle_size]);
		bool goalCheck();
		void duplicateBoard(int destBoard[puzzle_size], int origBoard[puzzle_size]);
		void expansion(boardLibrary node);
		bool ifListContainsNode(boardLibrary node);
		bool samePuzzle(boardLibrary node);
		void uniformSearch(boardLibrary node);
		void pathtrace(boardLibrary node);
		bool checkOrigMatrix(boardLibrary node);
		int checkMisplace(boardLibrary node);
		void misplaced(boardLibrary node);
		void manhattan(boardLibrary node);

};