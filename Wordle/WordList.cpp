#include "WordList.h"
#include "GameRules.h"
#include "StringUtils.h"

#include <fstream>

std::optional<std::vector<std::string>> readWords(const std::string& filePath)
{
	std::vector<std::string> words;

	std::ifstream file(filePath);

	if (!file) return std::nullopt;

	std::string line;

	while (std::getline(file, line))
	{
		line = trim(line);
		const WordStatus status = validateWord(line);

		if (status != WordStatus::Valid) continue;

		toUpper(line);
		words.push_back(line);
	}

	return words;
}

std::string pickRandomWord(const std::vector<std::string>& words, std::mt19937& engine)
{
	std::uniform_int_distribution<std::size_t> indexDistribution(0, words.size() - 1);

	const std::size_t index = indexDistribution(engine);

	return words[index];
}