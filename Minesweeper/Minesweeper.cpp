#include <iostream>
#include <conio.h>
#include <vector>

using std::vector;

bool isGameOver = false;

const int DIFFICULTY_SIZES[3] = { 12, 18, 24 };

void printTitle()
{
	std::cout << "\n\t    ---------MINESWEEPER---------\n";
}

int difficultyChosen()
{
	printTitle();
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

void printField(vector<vector<char>> field, int chosenY = 0, int chosenX = 0)
{
	printTitle();
	for (int i = 0; i < field.size(); i++)
	{
		std::cout << '\t';
		for (int j = 0; j < field.size(); j++)
		{
			if (i == chosenY && j == chosenX)
			{
				std::cout << "[" << field[i][j] << "]";
			}
			else
			{
				std::cout << " " << field[i][j] << " ";
			}
		}
		std::cout << '\n';
	}
}

void chooseAction(vector<vector<char>>& field)
{
	char keyPressed = _getch();
	int chosenX = field.size() / 2 - 1;
	int chosenY = field.size() / 2 - 1;

	switch (keyPressed)
	{
	case 'w':
		chosenY = chosenY == 0 ? chosenY : chosenY--;
		break;
	case 's':
		chosenY = chosenY == (field.size() - 1) ? chosenY : chosenY++;
		break;
	case 'a':
		chosenX = chosenX == 0 ? chosenX : chosenX--;
		break;
	case 'd':
		chosenX = chosenX == (field.size() - 1) ? chosenX : chosenX++;
		break;
	}

	printField(field, chosenX, chosenY);
}

int main()
{
	int sizeOfField = DIFFICULTY_SIZES[difficultyChosen()];
	
	vector<vector<char>> field = vector<vector<char>>(sizeOfField, vector<char>(sizeOfField, '0'));

	while (!isGameOver)
	{
		chooseAction(field);
	}

	return 0;
}
