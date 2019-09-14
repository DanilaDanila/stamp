#include <SFML/Graphics.hpp>
#include <iostream>

#include "block.hpp"
#include "block_renderer.hpp"

void drawAlgorithm(Block ***alg, unsigned lines_count, unsigned size, sf::RenderWindow *window, unsigned line=0, unsigned left_border=0, unsigned right_border=0)
{
    if (lines_count == 0) return;

    if (right_border == 0)
        right_border = window->getSize().x;

    unsigned block_count = 0;
    while(alg[line][block_count] != NULL)
        block_count++;

    #define padding_top 10
    #define padding 20
    unsigned pos_y = (padding + size)*line + padding_top;

    for(unsigned i=0; i<block_count; i++)
    {
        unsigned pos_x = (right_border - left_border)/float(block_count+1)*(i+1);
        drawBlock(alg[line][i], window, pos_x, pos_y, size);
    }

    drawAlgorithm(alg, lines_count-1, size, window, line+1, left_border, right_border);
}

int main()
{   
    #define depth 5
    Block ***algorithm = new Block**[depth];
    algorithm[0] = new Block*[1];
        algorithm[0][0] = new Block;
        algorithm[0][0]->label = "Start";
        algorithm[0][0]->type = BLOCK_TERMINATOR;

    algorithm[1] = new Block*[1];
        algorithm[1][0] = new Block;
        algorithm[1][0]->label = "Input:\n  A";
        algorithm[1][0]->type = BLOCK_IO;

    algorithm[2] = new Block*[1];
        algorithm[2][0] = new Block;
        algorithm[2][0]->label = "A+=1";
        algorithm[2][0]->type = BLOCK_PROCESS;

    algorithm[3] = new Block*[1];
        algorithm[3][0] = new Block;
        algorithm[3][0]->label = "Output:\n  A";
        algorithm[3][0]->type = BLOCK_IO;

    algorithm[4] = new Block*[2];
        algorithm[4][0] = new Block;
        algorithm[4][0]->label = "Return";
        algorithm[4][0]->type = BLOCK_TERMINATOR;

        algorithm[4][1] = new Block;
        algorithm[4][1]->label = "nullptr";
        algorithm[4][1]->type = BLOCK_TERMINATOR;


    sf::RenderWindow window(sf::VideoMode(400, 400), "Stupid Algorithm Making Program");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::White);

        drawAlgorithm(algorithm, depth, 40, &window);

        window.display();
    }
    return 0;
}