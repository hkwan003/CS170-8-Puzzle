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
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void findZero(int board[9]);
		void outputVector(int board[9]);
};