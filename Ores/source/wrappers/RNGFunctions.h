#pragma once

#include <ctime>

namespace RNG
{
	inline void InitRNG()
	{
		srand(time((time_t)NULL));
	}
	
	inline int RandomInt(int const max)
	{
		return rand() % (max + 1);
	}

	inline int RandomInt(int const min, int const max)
	{
		if (min >= 0)
		{
			return rand() % min + ((max + 1) - min);
		}
		else
		{
			return rand() % ((max + 1) + abs(min)) + min;
		}
	}
}