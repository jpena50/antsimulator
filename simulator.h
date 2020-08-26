#pragma once
#include <SFML/Graphics.hpp>


class Simulator
{
public:
	Simulator();
	void run();

private:
	enum class State
	{
		Ready,
		Running,
		Paused,
		Finished
	} state = State::Ready;

	sf::RenderWindow window;
	sf::Vector2u getWindowSize();

};