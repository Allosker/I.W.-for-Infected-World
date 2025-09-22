#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <ctime>


template<typename T>
inline T random_number(T min, T max)
{
	static std::mt19937 pseudo_random(static_cast<unsigned int>(std::time(nullptr)));

	std::uniform_real_distribution<T> random_number{min, max};

	return random_number(pseudo_random);
}

inline size_t random_number(size_t min, size_t max)
{
	static std::mt19937 pseudo_random(static_cast<unsigned int>(std::time(nullptr)));

	std::uniform_int_distribution random_number{ min, max };

	return random_number(pseudo_random);
}


#endif // RANDOM_H
