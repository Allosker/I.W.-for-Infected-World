#pragma once // Random.h

#include <random>
#include <ctime>

#include "umbrella headers/sfml.h"


namespace Util
{

	template<typename T>
	inline T random_number(T min, T max)
	{
		if (min == 0 && max == 0)
			return 0;

		static std::mt19937 pseudo_random(static_cast<unsigned int>(std::time(nullptr)));

		std::uniform_real_distribution<T> random_number{ min, max };

		return random_number(pseudo_random);
	}

	inline int random_number(int min, int max)
	{
		if (min == 0 && max == 0)
			return 0;

		static std::mt19937 pseudo_random(static_cast<unsigned int>(std::time(nullptr)));

		std::uniform_int_distribution random_number{ min, max };

		return random_number(pseudo_random);
	}


	template<typename T>
	inline Vec2<T> random_point(Vec2<T> min_range, Vec2<T> max_range)
	{
		if (min_range.x == 0 && min_range.y == 0 && max_range.x == 0 && max_range.y == 0)
			return { 0,0 };

		return { random_number<T>(min_range.x, max_range.x), random_number<T>(min_range.y, max_range.y) };
	}

}