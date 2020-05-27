#include "ant.h"
using namespace std;

sf::RenderWindow mywindow(sf::VideoMode(1000, 800, 32), "Ant Simulator");
sf::Event ev;







int main()
{
    mywindow.setVerticalSyncEnabled(true); // 60 fps
    Ant babyAnt;
    double t = 0;
    const double dt = 0.01;
    double frameTime = 0;
    double accumulator = 0;
    sf::Time time;
    sf::Time previous;
    sf::Time current;
    sf::Time elapsed;
    sf::Clock clock;
    sf::Texture texture;
    sf::IntRect spriteRect(0, 0, 538, 759);

    if (!texture.loadFromFile("black-ant-walk.png"))
    {
        cout << "error loading sprite" << endl << endl;
    }
    babyAnt.setTexture(&texture, &spriteRect);
    //babyAnt.setRectangle(&spriteRect);
    
    while (mywindow.isOpen())
    {
        while (mywindow.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) mywindow.close();
        }
        babyAnt.input();
        elapsed = clock.restart();
        if (elapsed.asSeconds() > 0.25)
            frameTime = 0.25;
        else 
            frameTime = elapsed.asSeconds();

        accumulator += frameTime;

        while (accumulator >= dt)
        {
            babyAnt.update(t, dt);
            t += dt;
            accumulator -= dt;
        }
        //const double alpha = accumulator / dt;
        //cout << endl << "frameTime = " << frameTime << "\naccumulator = " << accumulator << endl;
     
        mywindow.clear(sf::Color(181, 101, 29));
        mywindow.draw(babyAnt.getSprite());
        mywindow.display();
    }
}
















/*

int ts = 50;

class character
{
public:
    character()
    {
        x = 0;
        y = 0;

        // in this case, every loop, it will walk 2 pixels.
//if u put 50 as movespeed, it will walk 1 pixel each loop
        movespeed = 100.0 / ts;

        for (int i = 0; i < 4; ++i) //initialize the all move booleans to false
            move[i] = false;

        walking = false;
        myrect.setSize(sf::Vector2f(50, 50)); //size 50 by 50, same as every tile
    }

    void input(); //keypress detection
    void moving(); //moving if "walking" boolean is true

    float x;
    float y;
    float movespeed; //sets the movespeed

    enum MOVE { UP, DOWN, LEFT, RIGHT }; //enums instead of remember numbers
    bool move[4]; //deciding if u move up/down/left/right
    bool walking;
    int nextspot; //the next tilespot of the map

    sf::RectangleShape myrect;
};

void character::input()
{
    //input() and moving() functions are working together
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (walking == false)
        {
            //if you click up, the the nextspot will of course be 50
            //pixels above yourself, so thats why nextspot = y - tilsize
            nextspot = y - ts;
            //this is gonna make sure you cant have move[UP] and move[LEFT]
            //true on the same time so u wont walk 45 degrees
            move[UP] = true;
            walking = true;

        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (walking == false)
        {
            nextspot = y + ts;
            move[DOWN] = true;
            walking = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (walking == false)
        {
            nextspot = x - ts;
            move[LEFT] = true;
            walking = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (walking == false)
        {
            nextspot = x + ts;
            move[RIGHT] = true;
            walking = true;
        }
    }
}
void character::moving()
{
    if (walking == true)
    {
        if (move[UP] == true)
        {
            y -= movespeed;

            // i do <= and not just == because maybe your movespeed has a
            //decimalpoint and then it wont become the same number as nextspot
            if (y <= nextspot)
            {
                y = nextspot;
                walking = false;
                move[UP] = false;
            }
        }

        if (move[DOWN] == true)
        {
            y += movespeed;
            if (y >= nextspot)
            {
                y = nextspot;
                walking = false;
                move[DOWN] = false;
            }
        }
        if (move[LEFT] == true)
        {
            x -= movespeed;
            if (x <= nextspot)
            {
                x = nextspot;
                walking = false;
                move[LEFT] = false;
            }
        }
        if (move[RIGHT] == true)
        {
            x += movespeed;
            if (x >= nextspot)
            {
                x = nextspot;
                walking = false;
                move[RIGHT] = false;
            }
        }
    }
}
int main()
{
    mywindow.setVerticalSyncEnabled(true); // 60 fps
    character pacman; // a squared pacman
    pacman.myrect.setFillColor(sf::Color(255, 255, 0));
    while (mywindow.isOpen())
    {
        while (mywindow.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) mywindow.close();
        }

        pacman.input();
        pacman.moving();
        pacman.myrect.setPosition(pacman.x, pacman.y);

        mywindow.clear(sf::Color(0, 200, 0));
        mywindow.draw(pacman.myrect);

        mywindow.display();
    }
}
*/