#pragma once

#include <vector>
#include "ant.h"
#include "calculations.h"

class Ant;

class Simulator
{
public:
    Simulator();
    void run();
    /// <summary>
    /// Code from stackoverflow by Mario answered Jan 22 '17 
    /// https://stackoverflow.com/questions/41788847/dragging-screen-in-sfml
    /// 
    /// </summary>
    void handleMouse(sf::Event& ev);
    /// <summary>
    /// Handle simulation time and logic.
    /// </summary>
    void simLoop();
    void draw();
    void onResize(sf::Event& ev);
    /// <summary>
    /// May end up getting rid of this function we will see. I initially had this 
    /// here to ensure the ants don't leave the window but now with resizing it 
    /// doesn't really matter anymore
    /// </summary>
    /// <param name="newSize">new window size</param>
    void updateAntsWindowSize(sf::Vector2f newSize);
    void updateAnts(double t, double dt);
    void drawAnts();
private:
    enum class State
    {
        Ready,
        Running,
        Paused,
        Finished
    } state = State::Ready;

    sf::RenderWindow window;
    RNG rng;
    vector<Ant> ants;
    vector<Ant>::iterator iter;
    sf::Texture texture;
    sf::View miniMapView;
    sf::View simView;
    sf::View windowView;
    sf::View worldView2;
    sf::RectangleShape border;
    double t = 0;
    const double dt = 0.01;
    double frameTime = 0;
    double accumulator = 0;
    float zoom;
    sf::Vector2f oldPos;
    bool moving;
    sf::Time time;
    sf::Time previous;
    sf::Time current;
    sf::Time elapsed;
    sf::Clock clock;
};
