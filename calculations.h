/*Copyright Javier Pena*/
#pragma once
# define PI 3.14159265358979323846
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>


sf::Vector2f calcRectPos(sf::RectangleShape rect, sf::Vector2f velocity, float windowXEdge, float windowYEdge);
void moveRectangle(sf::RectangleShape* rectangle, sf::Vector2f velocity, sf::Vector2f direction);
void calcCircle(sf::CircleShape* circle, float windowXEdge, float windowYEdge);