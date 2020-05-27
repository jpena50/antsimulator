

#include "Animation.h"




void Animation::addFrame(Frame&& frame)
{
	totalLength += frame.duration;
	frames.push_back(std::move(frame));
}

void Animation::update(double elapsed)
{
	progress += elapsed;
	double p = progress;
	for (size_t i = 0; i < frames.size(); i++)
	{
		p -= frames[i].duration;

		if (p <= 0.0 || &(frames[i]) == &frames.back())
		{
			target.setTextureRect(frames[i].rect);
			break;
		}
	}
}