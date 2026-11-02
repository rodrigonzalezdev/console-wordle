#include "Console.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

bool enableConsoleColors()
{
	const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	if (output == INVALID_HANDLE_VALUE || output == nullptr) return false;

	DWORD mode = 0;

	if (GetConsoleMode(output, &mode) == 0) return false;

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	return SetConsoleMode(output, mode) != 0;
}