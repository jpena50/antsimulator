#include "rng.h"

RNG::RNG()
{
	std::mt19937_64 generator(time(0));
	distribution = uniform_real_distribution<double>(0.0, 1.0);
}

double RNG::generateRandomDouble()
{
	return distribution(generator);
}
