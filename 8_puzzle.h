using namespace std;

struct node
{
	list<node> children;
	node *parent;
	int new_board[9];
	int x;
	node(int old_board[9])
	:  parent(0), x(0)
	{
		for(int i = 0; i < 9; i++)
		{
			new_board[i] = old_board[i];
		}
	}
};

class boardLibrary
{
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