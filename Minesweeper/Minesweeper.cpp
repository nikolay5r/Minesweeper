#include <iostream>
#include <conio.h>
#include <vector>
#include <cstdlib>

using std::vector;

const int DIFFICULTY_SIZES[3] = { 12, 18, 24 };
const int NUMBER_OF_BOMBS[3] = { 144, 80, 120 };

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

void countBombsNearBoxes(vector<vector<char>>& field, const int sizeOfField)
{
	int sizeOfField1 = field.size() - 1;

	for (int i = 0; i <= sizeOfField1; i++)
	{
		for (int j = 0; j <= sizeOfField1; j++)
		{
			int counterForBombs = 0;

			if (field[i][j] == '*')
				continue;

			if (i != sizeOfField - 1 && field[i + 1][j] == '*')
				counterForBombs++;

			if (i != 0 && field[i - 1][j] == '*')
				counterForBombs++;

			if (j != 0 && i != 0 && field[i - 1][j - 1] == '*')
				counterForBombs++;

			if (j != sizeOfField - 1 && i != 0 && field[i - 1][j + 1] == '*')
				counterForBombs++;

			if (i != sizeOfField - 1 && j != sizeOfField - 1 && field[i + 1][j + 1] == '*')
				counterForBombs++;

			if (i != sizeOfField - 1 && j != 0 && field[i + 1][j - 1] == '*')
				counterForBombs++;

			if (j != sizeOfField - 1 && field[i][j + 1] == '*')
				counterForBombs++;

			if (j != 0 && field[i][j - 1] == '*')
				counterForBombs++;

			field[i][j] = (counterForBombs + '0');
		}
	}
}

void printField(const vector<vector<char>> field, const int sizeOfField, const int bombsLeft, int chosenY = 0, int chosenX = 0)
{
	printTitle();
	for (int i = 0; i < sizeOfField; i++)
	{
		std::cout << '\t';
		for (int j = 0; j < sizeOfField; j++)
		{
			if (i == chosenY && j == chosenX)
				std::cout << "[" << field[i][j] << "]";
			
			else
				std::cout << " " << field[i][j] << " ";
		
		}
		std::cout << '\n';
	}
	std::cout << "Bombs left to be flagged: " << bombsLeft;
}

void moveToDifferentBoxes(const vector<vector<char>> field, const int sizeOfField, const char keyPressed, int& chosenX, int& chosenY)
{
	switch (keyPressed)
	{
	case 'w':
		chosenY = (chosenY == 0) ? 0 : chosenY - 1;
		break;
	case 's':
		chosenY = (chosenY == sizeOfField - 1) ? chosenY : chosenY + 1;
		break;
	case 'a':
		chosenX = (chosenX == 0) ? 0 : chosenX - 1;
		break;
	case 'd':
		chosenX = (chosenX == sizeOfField - 1) ? chosenX : chosenX + 1;
		break;
	}
}

void openBox(vector<vector<char>>& actualField, vector<vector<char>>& userField, const int sizeOfField, const int x, const int y, bool& isGameOver)
{
	userField[y][x] = userField[y][x] == '+' ? '+' : actualField[y][x];
	
	if (actualField[y][x] == '*')
	{
		isGameOver = true;
	}
	else if (actualField[y][x] == '0')
	{
		if (y != (sizeOfField - 1) && (actualField[y + 1][x] != '*' && userField[y + 1][x] == '-'))
		{
			userField[y + 1][x] = actualField[y + 1][x];

			if (actualField[y + 1][x] == '0')
				openBox(actualField, userField, sizeOfField , x, y + 1, isGameOver);

		}
		if (y != 0 && (actualField[y - 1][x] != '*' && userField[y - 1][x] == '-'))
		{
			userField[y - 1][x] = actualField[y - 1][x];

			if (actualField[y - 1][x] == '0')
				openBox(actualField, userField, sizeOfField, x, y - 1, isGameOver);

		}
		if ((x != 0 && y != 0) && 
			(actualField[y - 1][x - 1] != '*' && userField[y - 1][x - 1] == '-'))
		{
			userField[y - 1][x - 1] = actualField[y - 1][x - 1];

			if (actualField[y - 1][x - 1] == '0')
				openBox(actualField, userField, sizeOfField, x - 1, y - 1, isGameOver);

		}
		if ((x != (sizeOfField - 1) && y != 0) &&
			(actualField[y - 1][x + 1] != '*' && userField[y - 1][x + 1] == '-'))
		{
			userField[y - 1][x + 1] = actualField[y - 1][x + 1];

			if (actualField[y - 1][x + 1] == '0')
				openBox(actualField, userField, sizeOfField, x + 1, y - 1, isGameOver);

		}
		if ((y != (sizeOfField - 1) && x != (sizeOfField - 1)) &&
			(actualField[y + 1][x + 1] != '*' && userField[y + 1][x + 1] != '-'))
		{ 
			userField[y + 1][x + 1] = actualField[y + 1][x + 1];

			if (actualField[y + 1][x + 1] == '0')
				openBox(actualField, userField, sizeOfField, x + 1, y + 1, isGameOver);

		}
		if ((y != (sizeOfField - 1) && x != 0) &&
			(actualField[y + 1][x - 1] != '*' && userField[y + 1][x - 1] == '-'))
		{
			userField[y + 1][x - 1] = actualField[y + 1][x - 1];

			if (actualField[y + 1][x - 1] == '0')
				openBox(actualField, userField, sizeOfField, x - 1, y + 1, isGameOver);

		}
		if (x != (sizeOfField - 1) && (actualField[y][x + 1] != '*' && userField[y][x + 1] == '-'))
		{ 
			userField[y][x + 1] = actualField[y][x + 1];

			if (actualField[y][x + 1] == '0')
				openBox(actualField, userField, sizeOfField, x + 1, y, isGameOver);
			
		}
		if (x != 0 && (actualField[y][x - 1] != '*' && userField[y][x - 1] == '-'))
		{
			userField[y][x - 1] = actualField[y][x - 1];

			if (actualField[y][x - 1] == '0')
				openBox(actualField, userField, sizeOfField, x - 1, y, isGameOver);

		}
	}
}

void flagBox(vector<vector<char>>& userField, int& bombsLeft, const int x, const int y)
{
	if (userField[y][x] == '-')
	{
		userField[y][x] = '+';
		bombsLeft--;
	}
	else if (userField[y][x] == '+')
	{
		userField[y][x] = '-';
		bombsLeft++;
	}
}

bool checkIfFlagsAreOnRightBoxes(const vector<vector<char>> actualField, const vector<vector<char>> userField, const int sizeOfField)
{
	for (int i = 0; i < sizeOfField; i++)
	{
		for (int j = 0; j < sizeOfField; j++)
		{
			if (actualField[i][j] == '*' && userField[i][j] != '+')
			{
				return false;
			}
		}
	}

	return true;
}

int playerActions(vector<vector<char>>& actualField, vector<vector<char>>& userField, const int sizeOfField, const int numberOfBombs, int chosenX = 0, int chosenY = 0)
{
	bool isGameOver = false;

	int bombsLeft = numberOfBombs;

	while (!isGameOver)
	{
		system("cls");
		printField(userField, sizeOfField, bombsLeft, chosenY, chosenX);

		char keyPressed = _getch();

		switch (keyPressed)
		{
		case 'w': case 's': case 'a': case 'd':
			moveToDifferentBoxes(actualField, sizeOfField, keyPressed, chosenX, chosenY);
			break;
		case 32:
			openBox(actualField, userField, sizeOfField, chosenX, chosenY, isGameOver);
			break;
		case 'f':
			flagBox(userField, bombsLeft, chosenX, chosenY);
			break;
		}

		if (bombsLeft == 0)
		{
			if (checkIfFlagsAreOnRightBoxes(actualField, userField, sizeOfField))
				return 1;

			else
				isGameOver = true;
		}
	}

	return 0;
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
	countBombsNearBoxes(actualField, sizeOfField);
	
	if (playerActions(actualField, userField, sizeOfField, numberOfBombs) == 1)
	{

	}
	else
	{

	}

	return 0;
}
