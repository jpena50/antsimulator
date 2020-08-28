#pragma once 
#define _USE_MATH_DEFINES

#include "simulator.h"
#include <cmath>

class Simulator;

enum class FrameDirection { kForward = 1, kReverse = -1 };

struct Frame {
    sf::IntRect rect;
    double duration; // seconds
    FrameDirection Direction;
};

class Ant
{
private:
    Simulator * sim;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f direction;
    sf::Vector2f destination;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectangle;
    Frame currentFrame;
    float lengths[5];
    double animLength;
    float speed;
    float sigmaU;
    float sigmaV;
    float u;
    float v;
    float stepSize;
    bool moving;
    bool atDestination;
    

public:
    Ant();
    Ant(Simulator* simulator);
    Ant(sf::IntRect rectangle, Simulator* simulator);
    Ant(sf::Texture* texture, sf::IntRect* spriteRect, Simulator* simulator);
    void input();
    void nextMove();
    void update(double time, double dt);
    void updateAnim(double dt);
    void updatePos(double time, double dt);
    void setRotation(sf::Vector2f velocity);
    void setTexture(sf::Texture* texture, sf::IntRect* spriteRect);
    void setTexture(sf::Texture texture, sf::IntRect spriteRect);
    void setRectangle(sf::IntRect* rect);
    void setSpeed(float s);
    void setPosition(sf::Vector2f p);
    void setSimulator(Simulator* sim);
    bool isClose(sf::Vector2f v1, sf::Vector2f v2);
    float getSpeed();
    sf::Sprite getSprite();
    sf::Vector2f getPosition();
    sf::Vector2f levyFlight();
    
};
