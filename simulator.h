#pragma once

#include <vector>
#include "ant.h"
#include "calculations.h"

class Ant;

class Simulator
{
public:
	Simulator();
	void run();
	sf::Vector2u getWindowSize();
	double getRandomDouble();
	void updateAntsWindowSize(sf::Vector2f newSize);
	void updateAnts(double t, double dt);
	void drawAnts();
private:
	enum class State
	{
		Ready,
		Running,
		Paused,
		Finished
	} state = State::Ready;

	sf::RenderWindow window;
	RNG rng;
	vector<Ant> ants;
	vector<Ant>::iterator iter;
	sf::Texture texture;
	sf::IntRect spriteRect;
	Calculator calc;
};
