#include <vector>

using namespace std;


class boardLibrary
{
	private:
		int parent[9];
		list<boardLibrary> children;

	public:
		boardLibrary();
		void moveUp(int x, int parent[9]);
		void moveDown(int x, int parent[9]);
		void moveLeft(int x, int parent[9]);
		void moveRight(int x, int parent[9]);
		void findZero(int board[9]);
		void outputVector(int board[9]);
		bool goalCheck(int board[9]);
		void duplicateBoard(int destBoard[9], int origBoard[9]);
};