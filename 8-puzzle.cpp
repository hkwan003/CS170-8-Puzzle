#include <iostream>
#include <vector>


using namespace std;

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

int main()
{
	vector < vector <int> > board;
	vector <int> input_row;
	cout << "Please enter in your puzzle board using zero to represent your blank spot " << endl;
	cout << "Please enter in 3 numbers with spaces in between them: " << endl;
	int spot1, spot2, spot3;
	cin >> spot1 >> spot2 >> spot3; 
	input_row.push_back(spot1);
	input_row.push_back(spot2);
	input_row.push_back(spot3);
	board.push_back(input_row);
	input_row.clear();

	cout << endl << "Please input in the second row of numbers with spaces in between them: " << endl;
	cin >> spot1 >> spot2 >> spot3;
	input_row.push_back(spot1);
	input_row.push_back(spot2);
	input_row.push_back(spot3);
	board.push_back(input_row);
	input_row.clear();

	cout << endl << "Please input in the third row of numbers with spaces in between them: " << endl;
	cin >> spot1 >> spot2 >> spot3;
	input_row.push_back(spot1);
	input_row.push_back(spot2);
	input_row.push_back(spot3);
	board.push_back(input_row);
	input_row.clear();

	cout << endl;
	output_vector(board);

	

}