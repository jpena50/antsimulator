#include "ant.h"
#include "simulator.h"


Ant::Ant(sf::IntRect rectangle, Simulator *simulator):
speed(150), 
animLength(0.025), 
moving(false), 
lengths{10, 20, 30, 200, 500}, 
atDestination(true),
currentFrame{ rectangle, 0, FrameDirection::kForward },
sim(simulator)

{
    position = sf::Vector2f (75, 75);//current position.
    destination = sf::Vector2f(75, 75);
    velocity = sf::Vector2f(0, 0);//speed at which we are moving.
    direction = sf::Vector2f(0,0);//direction we are moving in.
    //width 538 length 759
    sprite.setScale(0.025f,0.025f);// target scale 0.05; stream scale 0.1;
    sprite.setPosition(position);
    std::mt19937_64 generator(time(0));
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

sf::Vector2f getNormalizedVector(sf::Vector2f v1, sf::Vector2f v2)
{
    sf::Vector2f v3;
    float magnitude;
    v3.x = v2.x - v1.x;
    v3.y = v2.y - v1.y;
    magnitude = sqrt(v3.x * v3.x + v3.y * v3.y);
    v3.x /= magnitude;
    v3.y /= magnitude;

    return v3;
}

bool isClose(sf::Vector2f v1, sf::Vector2f v2)
{
    float distance = sqrt(powf(v2.x - v1.x, 2) + powf(v2.y - v1.y, 2));
    if (distance < 30)
        return true;
    else return false;
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

    if (isClose(position, destination))
        atDestination = true;
    


    if (atDestination)
    {
        double number = distribution(generator);
        destination.x = number * sim->getWindowSize().x;
        number = distribution(generator);
        destination.y = number * sim->getWindowSize().y;

        cout << "destination x = " << destination.x << endl;
        cout << "destination y = " << destination.y << endl << endl;
        atDestination = false;
        return;
    }
    velocity = getNormalizedVector(position, destination);
    velocity.x *= speed;
    velocity.y *= speed;

}

void Ant::update(double time, double dt)
{
    //makeMove(dt);
    nextMove();
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
    setPosition(sprite.getPosition());
    moving = true;
}
void Ant::setRotation(sf::Vector2f velocity)
{
    //atan2((by - ay), (bx - ax))
    if (velocity.x == 0 && velocity.y == 0)
    {
        return;
    }
    
    float angle = 0;
    angle = atan2(velocity.y, velocity.x); // atan2 is the right function (atan is bad in this context)
    angle = angle * 180.f / PI; // convert to degrees for SFML
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
    position.x = p.x;
    position.y = p.y;
}
void Ant::setSimulator(Simulator *simulator)
{
    sim = simulator;
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
