#include "simulator.h"
#include "ant.h"

#define NUM_ANTS 10

using namespace std;


Simulator::Simulator():
    window(sf::VideoMode(1000, 800, 32), "Ant Simulator")
{

}


void Simulator::run()
{

    sf::Event ev;


    window.setVerticalSyncEnabled(true); // 60 fps
    
    
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
    RNG rng();
    if (!texture.loadFromFile("black-ant-walk.png"))
    {
        cout << "error loading sprite" << endl << endl;
    }

  
    //my textures are not rendering. why??
    for (int i = 0; i < NUM_ANTS; i++)
    {
        ants.push_back(Ant(this));
    }


   
    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::Resized)
            {
                sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());

                // Minimum size
                if (size.x < 800)
                    size.x = 800;
                if (size.y < 600)
                    size.y = 600;
                cout << "x =" << size.x << endl;
                cout << "y =" << size.y << endl << endl;
                window.setView(sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y)));
            }
        }
        //babyAntArray.input();
        elapsed = clock.restart();
        if (elapsed.asSeconds() > 0.25)
            frameTime = 0.25;
        else
            frameTime = elapsed.asSeconds();

        accumulator += frameTime;

        while (accumulator >= dt)
        {
            //babyAntArray.update(t, dt);
            updateAnts(t, dt);


            t += dt;
            accumulator -= dt;
        }
        //const double alpha = accumulator / dt;
        //cout << endl << "frameTime = " << frameTime << "\naccumulator = " << accumulator << endl;

        window.clear(sf::Color(181, 101, 29));
        drawAnts();
        //window.draw(babyAnt.getSprite());
        window.display();

    }
}

sf::Vector2u Simulator::getWindowSize()
{
    return Simulator::window.getSize();
}

double Simulator::getRandomDouble()
{
   return rng.generateRandomDouble();
}






//why is ants not have any elements in it?
void Simulator::updateAnts(double time, double dt)
{
    for (iter = ants.begin(); iter != ants.end(); iter++)
        iter->update(time, dt);
}

void Simulator::drawAnts()
{
    for (iter = ants.begin(); iter != ants.end(); iter++)
        window.draw(iter->getSprite());
}


