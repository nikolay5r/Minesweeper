#include <iostream>
#include <vector>

using std::vector;

const int DIFFICULTY_SIZES[3] = { 12, 18, 24 };

int difficultyChosen()
{
	std::cout << "Choose difficulty of the game: \n"
		<< "\t0: easy\n"
		<< "\t1: medium\n"
		<< "\t2: hard\n";
	int chosenDifficulty = 0;
	std::cin >> chosenDifficulty;

	return chosenDifficulty;
}

int main()
{
	int size = DIFFICULTY_SIZES[difficultyChosen()];
	
	vector<vector<int>> field = vector<vector<int>>(size, vector<int>(size));

	return 0;
}
