#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>

using std::vector;

const int DIFFICULTY_SIZES[3] = { 12, 18, 24 };
const int NUMBER_OF_BOMBS[3] = { 40, 80, 120 };

void printTitle()
{
	std::cout << "\n\t    ---------MINESWEEPER---------\n\n";
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

void countBombsNearBoxes(vector<vector<char>>& field)
{
	for (int i = 0; i < field.size(); i++)
	{
		for (int j = 0; j < field.size(); j++)
		{
			int counterForBombs = 0;

			if (field[i][j] == '*')
			{
				continue;
			}

			if (i != field.size() - 1 && i != 0)
			{
				if (field[i + 1][j] == '*')
					counterForBombs++;
			
				if (field[i - 1][j] == '*')
					counterForBombs++;

				if (j != field.size() - 1 && j != 0)
				{
					if (field[i - 1][j - 1] == '*')
						counterForBombs++;
			
					if (field[i - 1][j +1] == '*')
						counterForBombs++;

					if (field[i + 1][j + 1] == '*')
						counterForBombs++;

					if (field[i + 1][j - 1] == '*')
						counterForBombs++;

				}
			}

			if (j != field.size() - 1 && j)
			{
				if (field[i][j + 1] == '*')
					counterForBombs++;
			
				if (field[i][j - 1] == '*')
					counterForBombs++;

			}
			
			field[i][j] = (counterForBombs + '0');
		}
	}
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
				std::cout << "[" << field[i][j] << "]";
			
			else
				std::cout << " " << field[i][j] << " ";
		
		}
		std::cout << '\n';
	}
}

void moveToDifferentBoxes(const vector<vector<char>> field, const char keyPressed, int& chosenX, int& chosenY)
{
	switch (keyPressed)
	{
	case 'w':
		chosenY = (chosenY == 0) ? 0 : chosenY - 1;
		break;
	case 's':
		chosenY = (chosenY == (field.size() - 1)) ? chosenY : chosenY + 1;
		break;
	case 'a':
		chosenX = (chosenX == 0) ? 0 : chosenX - 1;
		break;
	case 'd':
		chosenX = (chosenX == (field.size() - 1)) ? chosenX : chosenX + 1;
		break;
	}
}

void chooseAction(vector<vector<char>>& field, int chosenX = 0, int chosenY = 0)
{
	bool isGameOver = false;
	while (!isGameOver)
	{
		printField(field, chosenY, chosenX);

		char keyPressed = _getch();

		switch (keyPressed)
		{
		case 'w': case 's': case 'a': case 'd':
			moveToDifferentBoxes(field, keyPressed, chosenX, chosenY);
			break;
		}

		system("cls");
		chooseAction(field, chosenX, chosenY);
	}
}

void generateBombs(vector<vector<char>>& field, int& bombsToPut)
{
	while (bombsToPut > 0)
	{
		int x = rand() % field.size();
		int y = rand() % field.size();

		if (field[y][x] != '*')
		{
			field[y][x] = '*';
			bombsToPut--;
		}
		else
			generateBombs(field, bombsToPut);
	
	}
}

int main()
{
	int difficulty = difficultyChosen();
	int sizeOfField = DIFFICULTY_SIZES[difficulty];
	int numberOfBombs = NUMBER_OF_BOMBS[difficulty];
	
	vector<vector<char>> field = vector<vector<char>>(sizeOfField, vector<char>(sizeOfField, '0'));

	generateBombs(field, numberOfBombs);
	countBombsNearBoxes(field);
	chooseAction(field);

	return 0;
}
