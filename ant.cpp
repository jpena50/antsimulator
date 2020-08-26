#include "ant.h"
#include "simulator.h"


Ant::Ant():
speed(300), 
animLength(0.025), 
moving(false), 
lengths{10, 20, 30, 200, 500}, 
atDestination(true)
{
    position = sf::Vector2f (75, 75);//current position.
    destination = sf::Vector2f(75, 75);
    velocity = sf::Vector2f(0, 0);//speed at which we are moving.
    direction = sf::Vector2f(0,0);//direction we are moving in.
    //width 538 length 759
    sprite.setScale(0.1,0.1);// target scale 0.05; stream scale 0.1;
    sprite.setPosition(position);
    currentFrame.duration = 0;
    currentFrame.Direction = kForward;
    distribution = uniform_real_distribution<double>(0.0, 1.0);
 
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

/*need to make move by adding speed to velocity vector
  how can i simplify levy flight? create 5 lengths and randomly
  choose between them with given probability. lengths 1-3 80% and lengths 4-5 20%
  lengths 1-3 are varying degrees of short length. 4-5 are varying degrees of long length
  As for direction I shall create a probability of choosing an angle between [-120, 120]
  with a probability of 90% and 10% for angles between [-180, -120] and [120, 180] 
  to calculate next point. Afterwards update direction vector and
  make sure it is normalized to desired speed.*/
void Ant::nextMove()
{

    //choose next point.
    //check if within bounds.
    ////how to get window size.
    //set destination.
    //where to check if we are at our destination? beginning?


    if (atDestination)//when do modify this variable?
    {
        return;
    }


    double number = distribution(generator);














    //double number = distribution(generator);
    ////cout << number << endl << endl;

    //if (number >= 0 && number <= 0.2666)
    //{
    //    cout << "length 1" << endl << endl;
    //    velocity.x += speed;

    //}
    //else if (number > 0.2666 && number <= 0.5333)
    //{
    //    cout << "length 2" << endl << endl;
    //    velocity.x -= speed;
    //}
    //else if (number > 0.5333 && number <= 0.80)
    //{
    //    cout << "length 3" << endl << endl;
    //    velocity.y += speed;
    //}
    //else if (number > 0.80 && number <= 0.90)
    //{
    //    cout << "length 4" << endl << endl;
    //    velocity.y -= speed;
    //}
    //else if (number > 0.90 && number <= 1)
    //{
    //    cout << "length 5" << endl << endl;
    //    velocity.x += speed;
    //    velocity.y += speed;
    //}
}

void Ant::update(double time, double dt)
{
    //makeMove(dt);
    //nextMove();
    updatePos(time, dt);
    updateAnim(dt);
}
/*update the animation of the ant.
  dt = change in time*/
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
