#include <vector>

using namespace std;

// struct node
// {
// 	int new_board[9];
// 	node(int board[9])
// 	{
// 		for(int i = 0; i < 9; i++)
// 		{
// 			new_board[i] = board[i];
// 		}
// 	}
// };

class boardLibrary
{
	private:
		int parent[9];
		//list<node> children;

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