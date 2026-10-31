#include "Input.h"
#include "Score.h"
#include "Display.h"
#include "GameRules.h"
#include "WordList.h"

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <format>
#include <random>

int main()
{
	const std::string filePath = "words.txt";

	const std::optional<std::vector<std::string>> words = readWords(filePath);

	if (!words.has_value())
	{
		std::cerr << std::format("Couldn't open the file {}\n", filePath);

		return 1;
	}

	if (words->empty())
	{
		std::cerr << std::format("{} doesn't contain any {}-letter words.\n", filePath, wordLength);

		return 1;
	}

	std::random_device seedSource;

	std::mt19937 engine(seedSource());

	const std::string answer = pickRandomWord(*words, engine);

	bool guessedCorrectly = false;

	for (std::size_t attempt = 0; attempt < maxAttempts; ++attempt)
	{
		std::cout << "Attempt " << attempt + 1 << '/' << maxAttempts << '\n';

		const std::string guess = readGuess();

		const std::array<LetterState, wordLength> guessResult = scoreGuess(guess, answer);

		printGuess(guess, guessResult);

		if (guess == answer)
		{
			guessedCorrectly = true;

			if (attempt == 0) std::cout << "That is correct, great job! You got it on the first try!\n"; 
			else std::cout << "That is correct, great job! You got it in " << attempt + 1 << " tries!\n";

			break;
		}
	}

	if (!guessedCorrectly)
	{
		std::cout << "That was close, better luck next time! The answer was: " << answer << '\n';
	}

	return 0;
}