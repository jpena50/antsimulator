#pragma once
#include <vector>
#include "includes.h"

struct Frame {
	sf::IntRect rect;
	double duration; // seconds
};

class Animation {
	std::vector<Frame> frames;
	double totalLength;
	double progress;
	sf::Sprite& target;

public:
	Animation(sf::Sprite& target);
	virtual ~Animation();
	void addFrame(Frame&& frame);
	void update(double elapsed);
	const double getLength() const { return totalLength; }
};