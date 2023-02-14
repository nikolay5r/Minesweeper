#include <iostream>
#include <vector>

using std::vector;

const int DIFFICULTY_SIZES[3] = { 12, 18, 24 };

int difficultyChosen()
{
	std::cout << "\n\n\n";
	std::cout << "\tChoose difficulty of the game: \n"
		<< "\t   easy - 0\n"
		<< "\t   medium - 1\n"
		<< "\t   hard - 2\n"
		<< "\tYour choice: ";
	int chosenDifficulty = 0;
	std::cin >> chosenDifficulty;

	system("cls");

	return chosenDifficulty;
}

void printField(vector<vector<char>> field)
{
	std::cout << "\n\n\n";
	for (int i = 0; i < field.size(); i++)
	{
		std::cout << '\t';
		for (int j = 0; j < field.size(); j++)
		{
			std::cout << " " << field[i][j] << " ";
		}
		std::cout << '\n';
	}
}

int main()
{
	int sizeOfField = DIFFICULTY_SIZES[difficultyChosen()];
	
	vector<vector<char>> field = vector<vector<char>>(sizeOfField, vector<char>(sizeOfField, '0'));

	printField(field);

	return 0;
}
