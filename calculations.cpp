#include "calculations.h"

using namespace std;



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
    v3.x = v2.x - v1.x;
    v3.y = v2.y - v1.y;
    v3 = vectorNormalize(v3);

    return v3;
}
float uniformAngle(double randomNum)
{
    return 2 * M_PI * randomNum;
}
float clip(float minV, float maxV, float value)
{
    float val = std::max(minV, std::min(maxV, value));
    
        return val;
}
float standardNormal(float u, double rand)
{

   /*standardNormalGenerate = !standardNormalGenerate;
    if (standardNormalGenerate)
    {
        return standardNormal.y;
    }*/

    float v = uniformAngle(rand);
    float factor = sqrt(-2 * log(u));
    float x = factor * cos(v);

    return x;

}
float gamma(float z)
{
    return sqrt(2 * M_PI / z) * powf((1 / M_E) * (z + 1. / (12 * z - 1 / (10 * z))), z);
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

