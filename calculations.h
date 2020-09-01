
#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cfloat>
#include "rng.h"

class RNG;

class Calculator
{
public:
	Calculator();
	Calculator(RNG rng);
	double getRandomDouble();
	void setRNG(RNG rng);
private:
	RNG rng;
};



////////////////////////////////////////////////////////////
/// ---brief a different method of calculating the magnitude
///        of the vector that's more efficent. Found on
///https://www.h3xed.com/programming/fast-unit-vector-calculation-for-2d-games
///
/// ---param v1    vector to get magnitude of.
///
////////////////////////////////////////////////////////////
sf::Vector2f vectorNormalize(sf::Vector2f vector);

////////////////////////////////////////////////////////////
/// ---brief return the magnitude of the given vector.
///
/// ---param angle    angle in degrees to convert to radians
///
////////////////////////////////////////////////////////////
float degToRad(float angle);

////////////////////////////////////////////////////////////
/// ---brief return the magnitude of the given vector.
///
/// ---param v1    vector to get magnitude of.
///
////////////////////////////////////////////////////////////
float vectorLength(sf::Vector2f vector);

///////////////////////////////////////////////////////////
/// ---brief return factorial of decimal number. an approximation only
///        with help from Stack Overflow and dominiccooney on GitHub
///http://stackoverflow.com/questions/15454183/how-to-make-a-function-that-computes-the-factorial-for-numbers-with-decimals
///https://gist.github.com/dominiccooney/2f1332b49076bf1c8929
////////////////////////////////////////////////////////////
float gamma(float z);

////////////////////////////////////////////////////////////
/// ---brief return angle of vector for SFML. I am not sure if 
///        SFML has an affect on this as my understanding is still
///        weak on the coordinate system SFML has. I have a suspicion
///        that it does based on code I have found on SFML forums that
///        is contained here.
///
/// ---param vector    vector to get to angle of in SFML world.
///
///
////////////////////////////////////////////////////////////
float getAngle(sf::Vector2f vector);


////////////////////////////////////////////////////////////
/// ---brief return a normalized vector between two points
///
/// ---param v1   vector 1
/// ---param v2   vector 2
///
////////////////////////////////////////////////////////////
sf::Vector2f getNormalizedVector(sf::Vector2f v1, sf::Vector2f v2);

float standardNormal();

float uniformAngle(double random);



void printVector(sf::Vector2f vector);