#pragma once
#include "includes.h"

enum FrameDirection { kForward = 1, kReverse = -1 };

struct Frame {
    sf::IntRect rect;
    double duration; // seconds
    FrameDirection Direction;
    FrameDirection RtLdirection;
    FrameDirection UtDdirection;
};

class Ant
{
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f direction;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectangle;
    Frame currentFrame;
    double animLength;
    float speed;
    bool moving;

public:
    Ant();
    void input();
    void update(double time, double dt);
    void updateAnim(double dt);
    void updatePos(double time, double dt);
    void setRotation(sf::Vector2f velocity);
    void setTexture(sf::Texture* texture, sf::IntRect* spriteRect);
    void setRectangle(sf::IntRect* rect);
    void setSpeed(float s);
    void setPosition(sf::Vector2f p);
    sf::Sprite getSprite();
    float getSpeed();
    sf::Vector2f getPosition();


};
