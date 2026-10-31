#pragma once

#include <string>
#include <vector>
#include <optional>
#include <random>

std::optional<std::vector<std::string>> readWords(const std::string& filePath);

std::string pickRandomWord(const std::vector<std::string>& words, std::mt19937& engine); // words must not be empty