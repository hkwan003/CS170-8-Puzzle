#include <iostream>
#include <vector>
#include <queue>


using namespace std;

struct node
{
	vector< vector <int> >puzzle_board;
};

void output_vector(vector < vector <int> > a)
{
	for (int i = 0; i < a.size(); i++)
	{
		for(int j = 0; j < a[i].size(); j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

void find_zero(vector < vector <int> > puzzle)
{
	int coorX = -1;
	int coorY = -1;
	for ( int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(puzzle[i][j] == 0)
			{
				coorX = i;
				coorY = j;
			}
		}
	}

	cout << "coorX: " << coorX << " coorY: " << coorY << endl;
}

void expand (vector < vector <int> > expansion_board)
{
	queue<vector <vector <int> > >queue_board;
	queue_board.push(expansion_board);

}


int main()
{
	vector < vector <int> > board;
	vector <int> input_row;
	cout << "Please enter in your puzzle board using zero to represent your blank spot " << endl;
	cout << "Please enter in 3 numbers with spaces in between them: " << endl;
	int spot1, spot2, spot3;
	//cin >> spot1 >> spot2 >> spot3; 
	input_row.push_back(1);
	input_row.push_back(2);
	input_row.push_back(3);
	board.push_back(input_row);
	input_row.clear();

	cout << endl << "Please input in the second row of numbers with spaces in between them: " << endl;
	//cin >> spot1 >> spot2 >> spot3;
	input_row.push_back(4);
	input_row.push_back(0);
	input_row.push_back(5);
	board.push_back(input_row);
	input_row.clear();

	cout << endl << "Please input in the third row of numbers with spaces in between them: " << endl;
	//cin >> spot1 >> spot2 >> spot3;
	input_row.push_back(6);
	input_row.push_back(7);
	input_row.push_back(8);
	board.push_back(input_row);
	input_row.clear();

	cout << endl;
	output_vector(board);

	find_zero(board);

	

}