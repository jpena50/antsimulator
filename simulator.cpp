#pragma once
#include "simulator.h"
#include "ant.h"

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
    Ant babyAnt(spriteRect,this);

    if (!texture.loadFromFile("black-ant-walk.png"))
    {
        cout << "error loading sprite" << endl << endl;
    }
    babyAnt.setTexture(&texture, &spriteRect);
    //babyAnt.setRectangle(&spriteRect);

    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) window.close();
            if (ev.type == sf::Event::Resized)
            {
                cout << "x =" << window.getSize().x << endl;
                cout << "y =" << window.getSize().y << endl << endl;
            }
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

        window.clear(sf::Color(181, 101, 29));
        window.draw(babyAnt.getSprite());
        window.display();

    }
}

sf::Vector2u Simulator::getWindowSize()
{
    return Simulator::window.getSize();
}