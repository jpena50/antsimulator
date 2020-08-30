#pragma once
#include "includes.h"
#include "rng.h"
#include <vector>
#include "ant.h"

class Ant;

class Simulator
{
public:
	Simulator();
	void run();
	sf::Vector2u getWindowSize();
	double getRandomDouble();
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
};
