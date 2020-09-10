#include "ant.h"

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600
#define X_BOUND 5000
#define Y_BOUND 5000
#define START_X 2500
#define START_Y 2500



Ant::Ant(sf::Texture& t, RNG& rng1) :
    speed(350),
    sigmaU(0),
    sigmaV(0),
    u(0),
    v(0),
    dir(0),
    stepSize(20),
    distance(0),
    animLength(0.015),
    moving(false),
    lengths{ 10, 20, 30, 200, 500 },
    atDestination(true),
    currentFrame{ rectangle, 0, FrameDirection::kForward },
    texture(t),
    rectangle(sf::IntRect(0, 0, 538, 759)),
    rng(rng1),
    beta(1.5f)
  {
    windowSize = sf::Vector2f(X_BOUND, Y_BOUND);
    position = sf::Vector2f(START_X, START_Y);//current position.
    previousPos = sf::Vector2f(START_X, START_Y);
    destination = sf::Vector2f(START_X, START_Y);
    velocity = sf::Vector2f(0, 0);//speed at which we are moving.
    direction = sf::Vector2f(0, 0);//direction we are moving in.
    //width 538 length 759
    double scale = rng.generateRandomDouble();
    setSpeed(150 + scale * 200);

    sprite.setScale(0.035f + scale * 0.03, 0.035f + scale * 0.03);
    sprite.setPosition(position);
    sprite.setTexture(t);
    sprite.setTextureRect(rectangle);

    sigmaU = gamma(1 + beta) * sin(M_PI * beta / 2) / (gamma((1 + beta) / 2) * (double)beta * powf(2, (beta - 1) / 2));
    sigmaU = powf(sigmaU, 1 / beta);
    sigmaV = 1;
    

}


void Ant::input() 
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        velocity.y -= speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        velocity.y += speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x -= speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
    {
        float degrees;
        cin >> degrees;
        sprite.setRotation(degrees);
        cout << "Set Rotation to " << degrees << endl;
    }
} 
void Ant::nextMove()
{

    if (isClose(position, destination))
        atDestination = true;
    


    if (atDestination)
    {
        levyFlight();
        atDestination = false;
        return;
    }

    velocity = getNormalizedVector(position, destination);
    velocity.x *= speed;
    velocity.y *= speed;

}
void Ant::update(double time, double dt)
{
    nextMove();
    updatePos(time, dt);
    updateAnim(dt);
    

}
void Ant::updateAnim(double dt)
{
    if (currentFrame.duration >= animLength)
    {
        if (moving)
        {
            if (currentFrame.Direction == FrameDirection::kForward)
            {
                /*increment col by 1
                  increasing rows*/
                currentFrame.rect.left += currentFrame.rect.width;
                if (currentFrame.rect.left > 2152)
                {
                    currentFrame.rect.left = 0;
                    currentFrame.rect.top += currentFrame.rect.height;
                    if (currentFrame.rect.top > 1518)
                    {
                        currentFrame.Direction = FrameDirection::kReverse;
                        currentFrame.rect.top = 1518;
                        currentFrame.rect.left = 2152;
                        return;
                    }
                }

            }
            else //backward.col
            {
                /*decrement col by 1;
                    decreasing rows;*/
                currentFrame.rect.left -= currentFrame.rect.width;
                if (currentFrame.rect.left < 0)
                {
                    currentFrame.rect.left = 2152;
                    currentFrame.rect.top -= currentFrame.rect.height;
                    if (currentFrame.rect.top < 0)
                    {
                        currentFrame.Direction = FrameDirection::kForward;
                        currentFrame.rect.top = 0;
                        currentFrame.rect.left = 0;
                        return;
                    }
                }

            }

            sprite.setTextureRect(currentFrame.rect);
            currentFrame.duration = 0;
            return;
        }
    }
    currentFrame.duration += dt;
}
void Ant::updatePos(double time, double dt)
{
    
    if (velocity.x != 0 && velocity.y != 0)
    {
        velocity.x /= sqrt(2.f);
        velocity.y /= sqrt(2.f);
    }
    else if (velocity.x == 0 && velocity.y == 0)
    {
        moving = false;
        return;
    }
    velocity.x *= dt;
    velocity.y *= dt;
    setRotation(velocity);
    sprite.move(velocity);
    updateLocation(sprite.getPosition());
    moving = true;
}
void Ant::setRotation(sf::Vector2f velocity)
{
    float angle = getAngle(velocity);
    sprite.setRotation(angle);
}
void Ant::setTexture(sf::Texture* t, sf::IntRect* spriteRect)
{
    rectangle = *spriteRect;
    texture = *t;
    currentFrame.rect = *spriteRect;
    sprite.setTexture(texture);
    sprite.setTextureRect(rectangle);
}
void Ant::setRectangle(sf::IntRect* rect)
{
    rectangle = *rect;
    currentFrame.rect = *rect;
}
void Ant::setSpeed(float s)
{
    speed = s;
}
void Ant::updateLocation(sf::Vector2f p)
{
    position.x = p.x;
    position.y = p.y;
}
void Ant::setRNG(RNG rng1)
{
    rng = rng1;
}
void Ant::setWindow(sf::RenderWindow window)
{
}
void Ant::setWindowSize(sf::Vector2f size)
{
    windowSize = size;
}
float Ant::getSpeed()
{
    return speed;
}
bool Ant::isClose(sf::Vector2f v1, sf::Vector2f v2)
{
    float distance = sqrt(powf(v2.x - v1.x, 2) + powf(v2.y - v1.y, 2));
    if (distance < 30)
        return true;
    else return false;
}
sf::Sprite Ant::getSprite()
{
    return sprite;
}
sf::Vector2f Ant::getPosition()
{
    return position;
}
void Ant::levyFlight()
{

    /*
    * lots of help from studying this javascript implementation.
    https://gist.github.com/dominiccooney/2f1332b49076bf1c8929
    */
    dir = uniformAngle(rng.generateRandomDouble());
    u = standardNormal(rng.generateRandomDouble() ,rng.generateRandomDouble()) * sigmaU * stepSize;
    v = standardNormal(rng.generateRandomDouble(), rng.generateRandomDouble()) * sigmaV * stepSize;
    distance = u / pow(abs(v), 1 / beta);

    float levyX = previousPos.x + cos(dir) * distance;
    float levyY = previousPos.y + sin(dir) * distance;

    if (windowSize.x < levyX)
        cout << "Levy flight produced an X value greater than max value!" << endl << "ValueX = " << levyX << endl;

    if (windowSize.y < levyY)
        cout << "Levy flight produced a Y value greater than max value!" << endl << "ValueY = " << levyY << endl;


    destination.x = clip(0, windowSize.x, levyX);
    destination.y = clip(0, windowSize.y, levyY);
    previousPos = destination;

}

