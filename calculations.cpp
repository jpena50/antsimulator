
#include "calculations.h"


void calcCircle(sf::CircleShape* circle, float windowXEdge, float windowYEdge)
{
    float xPos = (*circle).getPosition().x;
    float yPos = (*circle).getPosition().y;
    bool xFlag = false;
    bool yFlag = false;

    std::cout << "xPos = " << xPos << std::endl;
    std::cout << "yPos = " << yPos << std::endl;
    if (xPos >= windowXEdge)
        xFlag = true;
    else if (xPos <= 5)
        xFlag = false;

    if (yPos >= windowYEdge)
        yFlag = true;
    else if (yPos <= 5)
        yFlag = false;

    if (xFlag)
        xPos = xPos - 0.2f;
    else
        xPos = xPos + 0.2f;

    if (yFlag)
        yPos = yPos - 0.1f;
    else
        yPos = yPos + 0.1f;

    (*circle).setPosition(xPos, yPos);
}

/*converting and angle x degrees to radians is 2*pi * (x / 360)*/
float degToRad(float angle)
{
    return 2 * (float)PI * (angle / 360.f);
}

float vecLength(sf::Vector2f vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}
/*// Get absolute value of each vector
ax = abs(x);
ay = abs(y);

// Create a ratio
ratio = 1 / max(ax, ay)
ratio = ratio * (1.29289 - (ax + ay) * ratio * 0.29289)

// Multiply by ratio
x = x * ratio
y = y * ratio*/
sf::Vector2f vecNormalize(sf::Vector2f vector)
{
    float x = vector.x;
    float y = vector.y;
    float ax = abs(vector.x);
    float ay = abs(vector.y);

    float ratio = 1 / std::max(ax, ay);
    ratio = ratio * (1.29289f - ((float)ax + ay) * ratio * 0.29289f);

    vector.x = x * ratio;
    vector.y = y * ratio;

    return vector;

}

/*
//first get the direction the entity is pointed
direction.x = (float) Math.cos(Math.toRadians(rotation));
direction.y = (float) Math.sin(Math.toRadians(rotation));
if (direction.length() > 0) {
    direction = direction.normalise();
}
//Then scale it by the current speed to get the velocity
velocity.x = direction.x * speed;
velocity.y = direction.y * speed;


//Update the position based on our current speed
//This is basic s = vt physics
position.x += velocity.x * timeElapsed;
position.y += velocity.y * timeElapsed;

*/
sf::Vector2f calcRectPos(sf::RectangleShape rect, sf::Vector2f velocity, float windowXEdge, float windowYEdge)
{
    sf::Vector2f direction;
    direction.x = cos(degToRad(rect.getRotation()));
    direction.y = cos(degToRad(rect.getRotation()));

    /*
    if (vecLength(direction) > 0)
    {
        direction = vecNormalize(direction);
    }
    */



    return direction;


}

void moveRectangle(sf::RectangleShape* rectangle, sf::Vector2f velocity, sf::Vector2f direction)
{
    sf::Vector2f dir(0.01f, 0.01f);
    
    (*rectangle).move(direction);
}
