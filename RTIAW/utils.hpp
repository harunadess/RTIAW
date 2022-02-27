#ifndef UTILS_H
#define UTILS_H

#include <random>
#include "precision.hpp"

// constants
const prec INF = std::numeric_limits<prec>::infinity();
const prec pi = (prec)3.1415926535897932385;

// utility functions
inline prec degreesToRadians(prec deg)
{
	return deg * pi / 180.0;
}

inline prec randomNumber()
{
	static std::uniform_real_distribution<prec> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline prec randomNumber(prec min, prec max)
{
	return min + (max - min) * randomNumber();
}

// clamp x to the range [min,max]
inline prec clamp(prec x, prec min, prec max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

#endif // !UTILS_H
