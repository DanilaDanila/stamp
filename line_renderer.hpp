#ifndef LINE_RENDERER_HPP
#define LINE_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define DirectionFrom  char
#define FROM_DOWN  0
#define FROM_LEFT  1
#define FROM_RIHGT 2

void _line(sf::Vector2f p0, sf::Vector2f p1, sf::RenderWindow *win)
{
    float len = sqrt((p0.x-p1.x)*(p0.x-p1.x) + (p0.y-p1.y)*(p0.y-p1.y));

    sf::RectangleShape line;
    line.setSize(sf::Vector2f(1, len));
    line.setFillColor(sf::Color::Black);
    line.setPosition(p0);
    float angle = -atan2(p1.y-p0.y, p1.x-p0.x)/M_PI*180;
    line.setRotation(angle);

    win->draw(line);
}

void drawLine(unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, DirectionFrom dir, unsigned padding_top, unsigned pudding, unsigned block_size, sf::RenderWindow *window)
{

}

#endif