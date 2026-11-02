#include "WordList.h"
#include "GameRules.h"
#include "Game.h"
#include "Input.h"
#include "Console.h"

#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <random>
#include <optional>

int main()
{
	if (!enableConsoleColors())
	{
		std::cerr << "Warning: couldn't enable console colors, so letter tiles may not display correctly.\n";
	}

	const std::string filePath = "words.txt";

	const std::optional<std::vector<std::string>> words = readWords(filePath);

	if (!words.has_value())
	{
		std::cerr << std::format("Couldn't open {}\n", filePath);

		waitForEnter();

		return 1;
	}

	if (words->empty())
	{
		std::cerr << std::format("{} doesn't contain any {}-letter words.\n", filePath, wordLength);

		waitForEnter();

		return 1;
	}

	std::random_device seedSource;

	std::mt19937 engine(seedSource());

	std::cout << "Let's play some Wordle!\n\n";

	do
	{
		playGame(*words, engine);

	} while (askPlayAgain());

	return 0;
}