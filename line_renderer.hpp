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
    float angle = -atan2(p1.x-p0.x, p1.y-p0.y)/M_PI*180;
    line.setRotation(angle);

    win->draw(line);
}

void drawLine(unsigned from_x, unsigned from_y, unsigned to_x, unsigned to_y, DirectionFrom dir, unsigned block_size, std::string label, sf::RenderWindow *window)
{
    unsigned text_size = block_size/6*3;
    sf::Text text;
    text.setCharacterSize(text_size/1.8);
    text.setString(label);
    text.setFillColor(sf::Color::Black);
    
    sf::Font font;
    font.loadFromFile(font_adr);
    text.setFont(font);

    if (dir == FROM_DOWN)
    {
        _line(sf::Vector2f(from_x, from_y), sf::Vector2f(from_x, from_y+block_size/4), window);
        from_y += block_size/4;

        text.setOrigin(sf::Vector2f(0, text.getLocalBounds().height/2));
        text.setPosition(sf::Vector2f(from_x+4, from_y - block_size/4));
        window->draw(text);
    }
    elif (dir == FROM_LEFT)
    {
        _line(sf::Vector2f(from_x, from_y), sf::Vector2f(from_x-block_size, from_y), window);
        from_x -= block_size;
        _line(sf::Vector2f(from_x, from_y), sf::Vector2f(from_x, from_y+block_size*3/4), window);
        from_y += block_size*3/4;

        text.setOrigin(sf::Vector2f(text.getLocalBounds().width/2, text.getLocalBounds().height));
        text.setPosition(sf::Vector2f(from_x + block_size/2, from_y - block_size*3/4-text.getLocalBounds().height));
        window->draw(text);
    }
    elif (dir == FROM_RIHGT)
    {
        _line(sf::Vector2f(from_x, from_y), sf::Vector2f(from_x+block_size, from_y), window);
        from_x += block_size;
        _line(sf::Vector2f(from_x, from_y), sf::Vector2f(from_x, from_y+block_size*3/4), window);
        from_y += block_size*3/4;

        text.setOrigin(sf::Vector2f(text.getLocalBounds().width/2, text.getLocalBounds().height));
        text.setPosition(sf::Vector2f(from_x - block_size/2, from_y - block_size*3/4-text.getLocalBounds().height));
        window->draw(text);
    }

    _line(sf::Vector2f(from_x, from_y), sf::Vector2f(to_x, from_y), window);
    _line(sf::Vector2f(to_x, from_y), sf::Vector2f(to_x, to_y), window);
}

#endif