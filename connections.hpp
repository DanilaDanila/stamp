#ifndef CONNECTIONS_HPP
#define CONNECTIONS_HPP

#include <SFML/Graphics.hpp>
#include "line_renderer.hpp"
#include "block_algorithm.hpp"

#define Port   char
#define BOTTOM  0
#define LEFT    1
#define RIGHT   2
#define TOP     3

struct Connect
{
    unsigned p0_x;
    unsigned p0_y;
    unsigned p1_x;
    unsigned p1_y;

    std::string label="";

    DirectionFrom dir;

    Connect() {}

    Connect(unsigned _p0_x, unsigned _p0_y, unsigned _p1_x, unsigned _p1_y, DirectionFrom _dir, std::string _label=""):
        p0_x(_p0_x),
        p0_y(_p0_y),
        p1_x(_p1_x),
        p1_y(_p1_y),
        dir(_dir),
        label(_label)
        {}

    Connect(sf::Vector2f p0, sf::Vector2f p1, DirectionFrom _dir, std::string _label=""):
        p0_x(p0.x),
        p0_y(p0.y),
        p1_x(p1.x),
        p1_y(p1.y),
        dir(_dir),
        label(_label)
        {}

    ~Connect() {}
};

sf::Vector2f getBlockSocket(Algorithm *alg, unsigned block_id, Port p, unsigned block_size, unsigned window_size)
{
    unsigned block_line = block_id/10;

    unsigned block_count = 0;
    while(alg[block_line][block_count] != NULL)
        block_count++;

    unsigned pos_x = window_size/float(block_count+1)*(block_id%10+1);
    unsigned pos_y = (block_size/2 + block_size)*block_line + block_size/4;

    switch (p)
    {
        case TOP:       return sf::Vector2f(pos_x, pos_y);
        case BOTTOM:    return sf::Vector2f(pos_x, pos_y+block_size);
        case LEFT:      return sf::Vector2f(pos_x-block_size, pos_y+block_size/2);
        case RIGHT:     return sf::Vector2f(pos_x+block_size, pos_y+block_size/2);
        default:        return sf::Vector2f();
    }
}

void drawConnections(Connect *lines, unsigned connects_count, unsigned block_size, sf::RenderWindow *window)
{
    if (lines == NULL) return;
    for(int i=0; i<connects_count; i++)
        drawLine(lines[i].p0_x, lines[i].p0_y, lines[i].p1_x, lines[i].p1_y, lines[i].dir, block_size, lines[i].label, window);
}

#endif