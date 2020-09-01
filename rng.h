#pragma once
#include <random>
#include <iostream>
#include <time.h>  

using namespace std;


class Calculator;
class RNG 
{
public:
	RNG();
	double generateRandomDouble();

private:
	std::mt19937_64 generator;
	uniform_real_distribution<double> distribution;
};
