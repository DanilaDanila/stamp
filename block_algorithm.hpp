#ifndef BLOCK_ALGORITHM_HPP
#define BLOCK_ALGORITHM_HPP

#include "block.hpp"
#include "block_renderer.hpp"

typedef Block** Algorithm;

Algorithm *initAlgorithm(unsigned lines_count)
{
    Algorithm *result = new Block**[lines_count];

    return result;
}

void initAlgorithmLine(Algorithm *alg, unsigned line_num, unsigned block_count)
{
    alg[line_num] = new Block*[block_count];
}

void setAlgorithmBlock(Algorithm *alg, unsigned line_num, unsigned block_num, std::string blabel, BlockType btype)
{
    alg[line_num][block_num] = new Block;
    alg[line_num][block_num]->id = line_num*10 + block_num;
    alg[line_num][block_num]->type = btype;
    alg[line_num][block_num]->label = blabel;
}

void deleteAlgorithm(Algorithm *alg)
{
    // TODO:
}

void drawAlgorithm(Algorithm *alg, unsigned lines_count, unsigned size, sf::RenderWindow *window, unsigned line=0, unsigned left_border=0, unsigned right_border=0)
{
    if (lines_count == 0) return;

    if (right_border == 0)
        right_border = window->getSize().x;

    unsigned block_count = 0;
    while(alg[line][block_count] != NULL)
        block_count++;

    const int padding_top = 10;
    const int padding = 20;
    unsigned pos_y = (padding + size)*line + padding_top;

    for(unsigned i=0; i<block_count; i++)
    {
        unsigned pos_x = (right_border - left_border)/float(block_count+1)*(i+1);
        drawBlock(alg[line][i], window, pos_x, pos_y, size);
    }

    drawAlgorithm(alg, lines_count-1, size, window, line+1, left_border, right_border);
}


#endif