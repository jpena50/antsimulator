#include "ant.h"


Ant::Ant()
: speed(100), animLength(0.025)
{
    speed = 300;
    position = sf::Vector2f (75, 75);
    velocity = sf::Vector2f(0, 0);
    direction = sf::Vector2f(0,0);
    //width 538 length 759
    sprite.setScale(0.05,0.05);
    sprite.setPosition(position);
    currentFrame.duration = 0;
    currentFrame.RtLdirection = kForward;
    currentFrame.UtDdirection = kForward;
    currentFrame.Direction = kForward;

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
void Ant::update(double time, double dt)
{
    updatePos(time, dt);
    updateAnim(dt);


}
void Ant::updateAnim(double dt)
{
    if (currentFrame.duration >= animLength)
    {
        if (moving)
        {
            if (currentFrame.Direction == kForward)
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
                        currentFrame.Direction = kReverse;
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
                        currentFrame.Direction = kForward;
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
    moving = true;
}
void Ant::setRotation(sf::Vector2f velocity)
{
    //atan2((by - ay), (bx - ax))
    if (velocity.x == 0 && velocity.y == 0)
    {
        return;
    }
    
    double angle = 0;
    angle = atan2(velocity.y, velocity.x); // atan2 is the right function (atan is bad in this context)
    angle = angle * 180 / PI; // convert to degrees for SFML
    angle = angle + 90 % 360; // add 180 to map to SFML's drawing coordinates

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
void Ant::setPosition(sf::Vector2f p)
{
    //do i just change the position vector or actually update sprite
    //position
}
sf::Sprite Ant::getSprite()
{
    return sprite;
}
float Ant::getSpeed()
{
    return speed;
}
sf::Vector2f Ant::getPosition()
{
    return position;
}
