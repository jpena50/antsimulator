#include "calculations.h"

using namespace std;

Calculator::Calculator()
{

}

Calculator::Calculator(RNG rng2) :
rng(rng2)
{

}

double Calculator::getRandomDouble()
{

    return rng.generateRandomDouble();
}

void Calculator::setRNG(RNG rng)
{
    this->rng = rng;
}



float degToRad(float angle)
{
    return 2 * (float)M_PI * (angle / 360.f);
}
float vectorLength(sf::Vector2f vector)
{
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}
sf::Vector2f vectorNormalize(sf::Vector2f vector)
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
sf::Vector2f getNormalizedVector(sf::Vector2f v1, sf::Vector2f v2)
{
    sf::Vector2f v3, v4;
    float magnitude;
    v3.x = v2.x - v1.x;
    v3.y = v2.y - v1.y;
    v3 = vectorNormalize(v3);
    //magnitude = vectorLength(v3);
    //v3.x /= magnitude;
    //v3.y /= magnitude;

    //cout << "v3 = ";
    //printVector(v3);

    //cout << "v4 = ";
    //printVector(v4);

    return v3;
}
float uniformAngle(double randomNum)
{
    return 2 * M_PI * randomNum;
}
float standardNormal()
{

   /*standardNormalGenerate = !standardNormalGenerate;
    if (standardNormalGenerate)
    {
        return standardNormal.y;
    }*/

    /*while (float u < FLT_EPSILON)
    {
        float u = rng->(generator);
    }*/
    
    return 0.f;

}
float gamma(float z)
{
    return sqrt(2 * M_PI / z) * powf((1 / M_E) * (z + 1 / (12 * z - 1 / (10 * z))), z);
}
float getAngle(sf::Vector2f vector)
{
    if (vector.x == 0 && vector.y == 0)
    {
        return 0.f;
    }

    float angle = 0;
    angle = atan2(vector.y, vector.x);
    angle = angle * 180.f / (float) M_PI; // convert to degrees for SFML
    angle = angle + 90;
    return angle;
}
void printVector(sf::Vector2f vector)
{
    cout << "(" << vector.x << ", " << vector.y << ")" << endl;
    return;
}





/*

scratch notes.


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

