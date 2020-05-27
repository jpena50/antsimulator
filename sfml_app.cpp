
#include "calculations.h"


int main3()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::Vector2f rVec(50.f,100.f);
    sf::Vector2f velocity(0.001f, 0.002f);
    sf::Vector2f direction(0,0);
    sf::CircleShape circle(100.f);
    sf::RectangleShape rect(rVec);
    rect.setFillColor(sf::Color::Blue);
    circle.setFillColor(sf::Color::Green);

    sf::CircleShape* circlePtr = &circle;
    sf::RectangleShape* rectPtr = &rect;

    float xPos, yPos, windowXEdge, windowYEdge, diameter;
    unsigned int windowX, windowY;
    bool xFlag = false;
    bool yFlag = false;
    
    diameter = circle.getRadius();
    windowX = window.getSize().x;
    windowY = window.getSize().y;
    windowXEdge = windowX - diameter * 2;
    windowYEdge = windowY - diameter * 2;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                
                diameter = circle.getRadius();
                windowX = window.getSize().x;
                windowY = window.getSize().y;
                windowXEdge = windowX - diameter * 2;
                windowYEdge = windowY - diameter * 2;
                std::cout << "I'm resized!"<< std::endl;
                std::cout << "diameter = " << diameter << std::endl;
                std::cout << "windowX = " << windowX << std::endl;
                std::cout << "windowY = " << windowY << std::endl;
                std::cout << "windowXEdge = " << windowXEdge << std::endl;
                std::cout << "windowYEdge = " << windowYEdge << std::endl;
            }
        }
        
       rect.rotate(0.1f);
       direction = calcRectPos(rect, velocity, windowXEdge, windowYEdge);

       moveRectangle(rectPtr, velocity, direction);



        calcCircle(circlePtr, windowXEdge, windowYEdge);
        window.clear();
        window.draw(circle);
        window.draw(rect);
        window.display();
    }

    return 0;
}



