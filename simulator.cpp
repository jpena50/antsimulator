#include "simulator.h"
#define NUM_ANTS 100
#define WIN_SIZE_X 1280
#define WIN_SIZE_Y 720
#define X_BOUND 5000
#define Y_BOUND 5000
#define START_X 2500
#define START_Y 2500

using namespace std;


Simulator::Simulator() :
    window(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y, 32), "Ant Simulator"),
    simView(sf::View(sf::FloatRect(0, 0, X_BOUND, Y_BOUND))),
    windowView(sf::View(sf::FloatRect(0,0,WIN_SIZE_X, WIN_SIZE_Y))),
    miniMapView(sf::View(sf::FloatRect(0, 0, X_BOUND, Y_BOUND))),
    t(0),
    dt(0.01),
    frameTime(0),
    accumulator(0),
    moving(false),
    zoom(1)
{
    /*miniMapView = window.getDefaultView();
    miniMapView.zoom(2.5f);*/
    //worldView1.setViewport(sf::FloatRect(0,0,1,1));
    //worldView2.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.27f));
    windowView.setViewport(sf::FloatRect(0, 0, 1, 1));
       
    border.setOutlineThickness(25.f);
    border.setOutlineColor(sf::Color::Black);
    border.setFillColor(sf::Color::Transparent);
    sf::Vector2f borderSize = simView.getSize();
    printVector(borderSize);
    printVector(sf::Vector2f(simView.getSize().x, simView.getSize().y));
    border.setSize(borderSize);
    window.setView(simView);
}


void Simulator::run()
{
    sf::Event ev;
    sf::Vector2f oldPos;
    bool moving = false;

    float zoom = 1;

    window.setVerticalSyncEnabled(true); // 60 fps
    
    
    if (!texture.loadFromFile("black-ant-walk.png"))
    {
        cout << "error loading sprite" << endl << endl;
    }
    sf::Texture& ref = texture;

    for (int i = 0; i < NUM_ANTS; i++)
    {
        Ant baby(ref,rng); 
        ants.push_back(baby);
    }

    //onResize();

   
    
    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) window.close();

            if (ev.type == sf::Event::Resized)
            {
                onResize(ev);
            }
            handleMouse(ev);
        }
        simLoop();
        draw();
    }
}

void Simulator::handleMouse(sf::Event& ev)
{
    switch (ev.type) {
    case sf::Event::Closed:
        window.close();
        break;
    case sf::Event::MouseButtonPressed:
        // Mouse button is pressed, get the position and set moving as active
        if (ev.mouseButton.button == 0) {
            moving = true;
            oldPos = window.mapPixelToCoords(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y), simView);
        }
        break;
    case  sf::Event::MouseButtonReleased:
        // Mouse button is released, no longer move
        if (ev.mouseButton.button == 0) {
            moving = false;
        }
        break;
    case sf::Event::MouseMoved:
    {
        // Ignore mouse movement unless a button is pressed (see above)
        if (!moving)
            break;
        // Determine the new position in world coordinates
        const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y), simView);
        // Determine how the cursor has moved
        // Swap these to invert the movement direction
        const sf::Vector2f deltaPos = oldPos - newPos;

        //printVector(deltaPos);

        // Move our view accordingly and update the window
        simView.setCenter(simView.getCenter() + deltaPos);
        window.setView(simView);

        // Save the new position as the old one
        // We're recalculating this, since we've changed the view
        oldPos = window.mapPixelToCoords(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y), simView);
        break;
    }
    case sf::Event::MouseWheelScrolled:
        // Ignore the mouse wheel unless we're not moving
        if (moving)
            break;

        // Determine the scroll direction and adjust the zoom level
        // Again, you can swap these to invert the direction
        if (ev.mouseWheelScroll.delta <= -1)
            zoom = std::min(200.f, zoom + .1f);
        else if (ev.mouseWheelScroll.delta >= 1)
            zoom = std::max(.01f, zoom - .1f);

        // Update our view
        sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());
        simView.setSize(size); // Reset the size
        simView.zoom(zoom); // Apply the zoom level (this transforms the view)
        window.setView(simView);



        break;
    }
}

void Simulator::simLoop()
{
    elapsed = clock.restart();
    if (elapsed.asSeconds() > 0.25)
        frameTime = 0.25;
    else
        frameTime = elapsed.asSeconds();

    accumulator += frameTime;

    while (accumulator >= dt)
    {
        updateAnts(t, dt);
        t += dt;
        accumulator -= dt;
    }
    //const double alpha = accumulator / dt;
    //cout << endl << "frameTime = " << frameTime << "\naccumulator = " << accumulator << endl;
}

void Simulator::draw()
{
    window.clear(sf::Color(181, 101, 29));
    window.setView(simView);
    drawAnts();
    window.draw(border);
    window.setView(windowView);
    drawAnts();
    window.draw(border);
    window.display();
}

void Simulator::onResize(sf::Event& ev)
{
    sf::Vector2f size = static_cast<sf::Vector2f>(window.getSize());

    if (size.x < 100)
        size.x = 100;
    if (size.y < 100)
        size.y = 100;

    window.setSize(static_cast<sf::Vector2u>(size));
    simView.setSize(size);
}

void Simulator::updateAntsWindowSize(sf::Vector2f newSize)
{
    for (iter = ants.begin(); iter != ants.end(); iter++)
        iter->setWindowSize(newSize);
}

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


