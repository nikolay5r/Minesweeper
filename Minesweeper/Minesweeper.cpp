#include <iostream>

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
	
	

	return 0;
}
