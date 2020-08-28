#include "ant.h"


Ant::Ant():
speed(350),
sigmaU(0),
sigmaV(0),
u(0),
v(0),
stepSize(20),
animLength(0.005),
moving(false),
lengths{ 10, 20, 30, 200, 500 },
atDestination(true),
currentFrame{ rectangle, 0, FrameDirection::kForward }

{
    position = sf::Vector2f(75, 75);//current position.
    destination = sf::Vector2f(75, 75);
    velocity = sf::Vector2f(0, 0);//speed at which we are moving.
    direction = sf::Vector2f(0, 0);//direction we are moving in.
    //width 538 length 759
    // sprite.setScale(0.025f,0.025f);// target scale 0.05; stream scale 0.1;
    sprite.setScale(0.08f, 0.08f);
    sprite.setPosition(position);
    sf::Texture texture;
    sf::IntRect spriteRect(0, 0, 538, 759);
    if (!texture.loadFromFile("black-ant-walk.png"))
    {
        cout << "error loading sprite" << endl << endl;
    }
    setTexture(&texture, &spriteRect);
}

Ant::Ant(Simulator* simulator):
speed(350),
sigmaU(0),
sigmaV(0),
u(0),
v(0),
stepSize(20),
animLength(0.005),
moving(false),
lengths{ 10, 20, 30, 200, 500 },
atDestination(true),
currentFrame{ rectangle, 0, FrameDirection::kForward },
sim(simulator)
{
    position = sf::Vector2f(75, 75);//current position.
    destination = sf::Vector2f(75, 75);
    velocity = sf::Vector2f(0, 0);//speed at which we are moving.
    direction = sf::Vector2f(0, 0);//direction we are moving in.
    //width 538 length 759
    // sprite.setScale(0.025f,0.025f);// target scale 0.05; stream scale 0.1;
    sprite.setScale(0.08f, 0.08f);
    sprite.setPosition(position);
    sf::IntRect spriteRect(0, 0, 538, 759);
    if (!texture.loadFromFile("black-ant-walk.png"))
    {
        cout << "error loading sprite" << endl << endl;
    }
    setTexture(&texture, &spriteRect);
}

Ant::Ant(sf::IntRect rectangle, Simulator *simulator):
speed(350),
sigmaU(0),
sigmaV(0),
u(0),
v(0),
stepSize(20),
animLength(0.005), 
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
    // sprite.setScale(0.025f,0.025f);// target scale 0.05; stream scale 0.1;
    sprite.setScale(0.08f, 0.08f);
    sprite.setPosition(position);
    if (!texture.loadFromFile("black-ant-walk.png"))
    {
        cout << "error loading sprite" << endl << endl;
    }
    setTexture(texture, rectangle);
}

Ant::Ant(sf::Texture* texture, sf::IntRect* spriteRect, Simulator* simulator):
speed(350),
sigmaU(0),
sigmaV(0),
u(0),
v(0),
stepSize(20),
animLength(0.005),
moving(false),
lengths{ 10, 20, 30, 200, 500 },
atDestination(true),
currentFrame{ rectangle, 0, FrameDirection::kForward },
sim(simulator)

{
    position = sf::Vector2f(75, 75);//current position.
    destination = sf::Vector2f(75, 75);
    velocity = sf::Vector2f(0, 0);//speed at which we are moving.
    direction = sf::Vector2f(0, 0);//direction we are moving in.
    //width 538 length 759
    // sprite.setScale(0.025f,0.025f);// target scale 0.05; stream scale 0.1;
    sprite.setScale(0.08f, 0.08f);
    sprite.setPosition(position);
    setTexture(texture, spriteRect);
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
        double number = sim->getRandomDouble();
        destination.x = number * sim->getWindowSize().x;
        number = sim->getRandomDouble();
        destination.y = number * sim->getWindowSize().y;
        

        //cout << "destination (x,y) = ";
        //printVector(destination);
        
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
    setPosition(sprite.getPosition());
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
void Ant::setTexture(sf::Texture t, sf::IntRect spriteRect)
{
    currentFrame.rect = spriteRect;
    sprite.setTexture(t);
    sprite.setTextureRect(spriteRect);
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
sf::Vector2f Ant::levyFlight()
{

    /*
    need function to generate a random number uniformly distributed between 0 and n-1.
        in example this is used to fill an array of x points and y points that is then manipulated for something.
    need function to generate a random angle uniformly distributed in radians
        angle for direction of levy flight
    epsilon is used.
        1e-16
    gamma function to calculate sigmaU
    sigmaV initially = 1

    */

    float beta = 3 / 2;
    sigmaU = gamma(1 + beta) * sin(M_PI * beta / 2) / (gamma((1 + beta) / 2) * beta * powf(2, (beta - 1) / 2));
    sigmaU = powf(sigmaU, 1 / beta);
    sigmaV = 1;

    /*
    Levy flight function
    Need a step size.
    beta = 3/2;
    gamma(z)
    return Math.sqrt(2 * Math.PI / z) * Math.pow((1 / Math.E) * (z + 1 / (12 * z - 1 / (10 * z))), z); 
      https://stackoverflow.com/questions/15454183/how-to-make-a-function-that-computes-the-factorial-for-numbers-with-decimals

    */

    /*
    Levy flight step may need to be separate function
    direction = uniformAngle();
    u = standardNormal() * sigmaU * stepSize;
    v = standardNormal() * sigmaV * stepSize;
    distance = u / powf(abs(v), 1 / beta);

    width/height is the window width/height or the available area for the ant to travel too.

    push.xs(clip(0, width, xs[xs.length-1] + cos(direction) * distance));
    push.ys(clip(0, height, ys[ys.length-1] + sin(direction) * distance));

    this seems to be the final calculation that will give us our destination.
    xs[xs.length-1] + cos(direction) * distance
    */


    //u = standardNormal() * sigmaU * stepSize;
    //v = standardNormal() * sigmaV * stepSize;


    /*
    OTHER FUNCTIONS
    https://gist.github.com/dominiccooney/2f1332b49076bf1c8929
standardNormal() 
{
      sstandardNormal.generate = !standardNormal.generate;
  if (standardNormal.generate) {
    // There's a cached result.
    return standardNormal.y;
  }

  do {
   var u = Math.random();
   var v = uniformAngle();
  } while (u < Number.MIN_VALUE);

  let factor = Math.sqrt(-2 * Math.log(u));
  let x = factor * Math.cos(v);
  standardNormal.y = factor * Math.sin(v);
  return x;tandardNormal	
}
//////////////////////////////////////////////////////////////////////

clip(min, max, value)
{
  return Math.max(min, Math.min(max, value));
}





    */


    return sf::Vector2f();
}

