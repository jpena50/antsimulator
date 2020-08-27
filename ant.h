#pragma once
#include "includes.h"
#include "simulator.h"
#include <random>
#include <iostream>

enum class FrameDirection { kForward = 1, kReverse = -1 };

struct Frame {
    sf::IntRect rect;
    double duration; // seconds
    FrameDirection Direction;
};

class Ant
{
private:
    Simulator* sim;
    std::random_device device;
    std::mt19937_64 generator;
    uniform_real_distribution<double> distribution;
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
    bool moving;
    bool atDestination;

public:
    Ant(sf::IntRect rectangle, Simulator* simulator);
    void input();
    //void makeMove(double dt);
    void nextMove();
    void update(double time, double dt);
    void updateAnim(double dt);
    void updatePos(double time, double dt);
    void setRotation(sf::Vector2f velocity);
    void setTexture(sf::Texture* texture, sf::IntRect* spriteRect);
    void setRectangle(sf::IntRect* rect);
    void setSpeed(float s);
    void setPosition(sf::Vector2f p);
    void setSimulator(Simulator* sim);
    sf::Sprite getSprite();
    float getSpeed();
    sf::Vector2f getPosition();
};
