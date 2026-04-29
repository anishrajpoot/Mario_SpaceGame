#pragma once
#include <cstdlib>

class Random
{
public:
	static int Range(int min, int max)
	{
		return min + rand() % max;
	}
};