#include "io.h"

#include <iostream>

// one function to rule them all
template<typename T>
static T read(char const *const message)
{
	T in;
	std::cout << message;
	std::cout.flush();

	std::cin >> in;
	return in;
}

double getDouble(char const *const message)
{
	return read<double>(message);
}

int getInt(char const *const message)
{
	return read<int>(message);
}

char getChar(char const *const message)
{
	return read<char>(message);
}
