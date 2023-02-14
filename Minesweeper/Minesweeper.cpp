#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>

using std::vector;

const int DIFFICULTY_SIZES[3] = { 12, 18, 24 };
const int NUMBER_OF_BOMBS[3] = { 10, 80, 120 };

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
	int fieldLastIndex = field.size() - 1;

	for (int i = 0; i <= fieldLastIndex; i++)
	{
		for (int j = 0; j <= fieldLastIndex; j++)
		{
			int counterForBombs = 0;

			if (field[i][j] == '*')
				continue;

			if (i != fieldLastIndex && field[i + 1][j] == '*')
				counterForBombs++;

			if (i != 0 && field[i - 1][j] == '*')
				counterForBombs++;

			if (j != 0 && i != 0 && field[i - 1][j - 1] == '*')
				counterForBombs++;

			if (j != fieldLastIndex && i != 0 && field[i - 1][j + 1] == '*')
				counterForBombs++;

			if (i != fieldLastIndex && j != fieldLastIndex && field[i + 1][j + 1] == '*')
				counterForBombs++;

			if (i != fieldLastIndex && j != 0 && field[i + 1][j - 1] == '*')
				counterForBombs++;

			if (j != fieldLastIndex && field[i][j + 1] == '*')
				counterForBombs++;

			if (j != 0 && field[i][j - 1] == '*')
				counterForBombs++;

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
	int sizeOfField = field.size() - 1;

	switch (keyPressed)
	{
	case 'w':
		chosenY = (chosenY == 0) ? 0 : chosenY - 1;
		break;
	case 's':
		chosenY = (chosenY == sizeOfField) ? chosenY : chosenY + 1;
		break;
	case 'a':
		chosenX = (chosenX == 0) ? 0 : chosenX - 1;
		break;
	case 'd':
		chosenX = (chosenX == sizeOfField) ? chosenX : chosenX + 1;
		break;
	}
}

void openBox(vector<vector<char>>& actualField, vector<vector<char>>& userField, int x, int y, bool& isGameOver)
{
	int sizeOfActualField = actualField.size() - 1;

	userField[y][x] = actualField[y][x];

	if (actualField[y][x] == '*')
	{
		isGameOver = true;
	}
	else if (actualField[y][x] == '0')
	{
		if (y != sizeOfActualField && (actualField[y + 1][x] != '*' && userField[y + 1][x] == '-'))
		{
			if (actualField[y + 1][x] == '0')
				openBox(actualField, userField, x, y + 1, isGameOver);

			else
				userField[y + 1][x] = actualField[y + 1][x];
		}
		if (y != 0 && (actualField[y - 1][x] != '*' && userField[y - 1][x] == '-'))
		{
			if (actualField[y - 1][x] == '0')
				openBox(actualField, userField, x, y - 1, isGameOver);

			else
				userField[y - 1][x] = actualField[y - 1][x];
		}
		if ((x != 0 && y != 0) && 
			(actualField[y - 1][x - 1] != '*' && userField[y - 1][x - 1] == '-'))
		{
			if (actualField[y - 1][x - 1] == '0')
				openBox(actualField, userField, x - 1, y - 1, isGameOver);

			else
				userField[y - 1][x - 1] = actualField[y - 1][x - 1];
		}
		if ((x != sizeOfActualField && y != 0) && 
			(actualField[y - 1][x + 1] != '*' && userField[y - 1][x + 1] == '-'))
		{
			if (actualField[y - 1][x + 1] == '0')
				openBox(actualField, userField, x + 1, y - 1, isGameOver);

			else
				userField[y - 1][x + 1] = actualField[y - 1][x + 1];
		}
		if ((y != sizeOfActualField && x != sizeOfActualField) && 
			(actualField[y + 1][x + 1] != '*' && userField[y + 1][x + 1] == '-'))
		{ 
			if (actualField[y + 1][x + 1] == '0')
				openBox(actualField, userField, x + 1, y + 1, isGameOver);

			else
				userField[y + 1][x + 1] = actualField[y + 1][x + 1];
		}
		if ((y != sizeOfActualField && x != 0) && 
			(actualField[y + 1][x - 1] != '*' && userField[y + 1][x - 1] == '-'))
		{
			if (actualField[y + 1][x - 1] == '0')
				openBox(actualField, userField, x - 1, y + 1, isGameOver);

			else
				userField[y + 1][x - 1] = actualField[y + 1][x - 1];
		}
		if (x != sizeOfActualField && (actualField[y][x + 1] != '*' && userField[y][x + 1] == '-'))
		{ 
			if (actualField[y][x + 1] == '0')
				openBox(actualField, userField, x + 1, y, isGameOver);

			else
				userField[y][x + 1] = actualField[y][x + 1];
		}
		if (x != 0 && (actualField[y][x - 1] != '*' && userField[y][x - 1] == '-'))
		{
			if (actualField[y][x - 1] == '0')
				openBox(actualField, userField, x - 1, y - 1, isGameOver);

			else
				userField[y][x - 1] = actualField[y][x - 1];
		}
	}
}

void chooseAction(vector<vector<char>>& actualField, vector<vector<char>>& userField, int chosenX = 0, int chosenY = 0)
{
	bool isGameOver = false;
	while (!isGameOver)
	{
		system("cls");
		printField(userField, chosenY, chosenX);

		char keyPressed = _getch();

		switch (keyPressed)
		{
		case 'w': case 's': case 'a': case 'd':
			moveToDifferentBoxes(actualField, keyPressed, chosenX, chosenY);
			break;
		case 32:
			openBox(actualField, userField, chosenX, chosenY, isGameOver);
			break;
		}
	}
}

void generateCoordinates(vector<vector<char>>& field, int& x, int& y)
{
	int sizeOfField = field.size();

	x = rand() % sizeOfField;
	y = rand() % sizeOfField;

	if (field[y][x] == '*')
		generateCoordinates(field, x, y);

}

void generateBombs(vector<vector<char>>& field, int bombsToPut)
{
	srand(time(0));
	while (bombsToPut > 0)
	{
		int x = 0, y = 0;
		generateCoordinates(field, x, y);
		bombsToPut--;
		field[y][x] = '*';
	}
}

int main()
{
	int difficulty = difficultyChosen();
	int sizeOfField = DIFFICULTY_SIZES[difficulty];
	int numberOfBombs = NUMBER_OF_BOMBS[difficulty];
	
	vector<vector<char>> actualField = vector<vector<char>>(sizeOfField, vector<char>(sizeOfField, '0'));
	vector<vector<char>> userField = vector<vector<char>>(sizeOfField, vector<char>(sizeOfField, '-'));

	generateBombs(actualField, numberOfBombs);
	countBombsNearBoxes(actualField);
	chooseAction(actualField, userField);

	return 0;
}
