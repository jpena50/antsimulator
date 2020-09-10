#pragma once 
#define _USE_MATH_DEFINES
#include "calculations.h"


enum class FrameDirection { kForward = 1, kReverse = -1 };

struct Frame {
    sf::IntRect rect;
    double duration; // seconds
    FrameDirection Direction;
};

class Ant
{
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f direction;
    sf::Vector2f destination;
    sf::Vector2f previousPos;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectangle;
    sf::RenderWindow* window;
    sf::Vector2f windowSize;
    RNG& rng;
    Frame currentFrame;
    float lengths[5];
    double animLength;
    float beta;
    float speed;
    float sigmaU;
    float sigmaV;
    float u;
    float v;
    float dir;
    float stepSize;
    float distance;
    bool moving;
    bool atDestination;
    

public:
    Ant(sf::Texture& t, RNG& rng1);
    void input();
    void nextMove();
    void update(double time, double dt);
    void updateAnim(double dt);
    void updatePos(double time, double dt);
    void setRotation(sf::Vector2f velocity);
    void setTexture(sf::Texture* texture, sf::IntRect* spriteRect);
    void setRectangle(sf::IntRect* rect);
    void setSpeed(float s);
    void updateLocation(sf::Vector2f p);
    void setRNG(RNG rng);
    void setWindow(sf::RenderWindow window);
    void setWindowSize(sf::Vector2f size);
    bool isClose(sf::Vector2f v1, sf::Vector2f v2);
    float getSpeed();
    sf::Sprite getSprite();
    sf::Vector2f getPosition();
    void levyFlight();
    
};
