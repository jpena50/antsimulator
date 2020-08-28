#pragma once
#include "includes.h"
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <cfloat>


class RNG 
{
public:
	RNG();
	double generateRandomDouble();

private:
	std::mt19937_64 generator;
	uniform_real_distribution<double> distribution;
};
