#include <SFML/Graphics.hpp>
#include <iostream>

#define BlockType            char
#define BLOCK_UNDEFINED     (0<<0)
#define BLOCK_TERMINATOR    (1<<0)
#define BLOCK_PROCESS       (1<<1)
#define BLOCK_CONDITION     (1<<2)
#define BLOCK_IO            (1<<3)

#define elif(condition) else if ((condition))

struct Block
{
    std::string label;

    BlockType type = BLOCK_UNDEFINED;
};

void drawBlock(Block *block, sf::RenderWindow *window, unsigned pos_x, unsigned pos_y, unsigned size)
{
    if (block->type == BLOCK_UNDEFINED) return;

    if (block->type == BLOCK_TERMINATOR)
    {
        sf::CircleShape circle;
        circle.setRadius(size/2);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineThickness(1);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOrigin(sf::Vector2f(circle.getRadius(), 0));

        circle.setPosition(sf::Vector2f(pos_x - size/2, pos_y));
        window->draw(circle);

        circle.setPosition(sf::Vector2f(pos_x + size/2, pos_y));
        window->draw(circle);

        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(size, size));
        shape.setOrigin(sf::Vector2f(size/2, 0));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        shape.setPosition(sf::Vector2f(pos_x, pos_y));
        window->draw(shape);

        circle.setOutlineThickness(0);
        window->draw(circle);

        circle.setPosition(sf::Vector2f(pos_x - size/2, pos_y));
        window->draw(circle);
    }
    elif (block->type == BLOCK_PROCESS)
    {
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(2*size, size));
        shape.setOrigin(sf::Vector2f(size, 0));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        shape.setPosition(sf::Vector2f(pos_x, pos_y));

        window->draw(shape);
    }
    elif (block->type == BLOCK_CONDITION)
    {
        sf::ConvexShape shape;
        shape.setPointCount(4);
        shape.setPoint(0, sf::Vector2f(0, size/2));
        shape.setPoint(1, sf::Vector2f(size, 0));
        shape.setPoint(2, sf::Vector2f(2*size, size/2));
        shape.setPoint(3, sf::Vector2f(size, size));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOrigin(sf::Vector2f(size, 0));
        shape.setPosition(sf::Vector2f(pos_x, pos_y));

        window->draw(shape);
    }
    elif (block->type == BLOCK_IO)
    {
        sf::ConvexShape shape;
        shape.setPointCount(4);
        shape.setPoint(0, sf::Vector2f(0, size));
        shape.setPoint(1, sf::Vector2f(size, 0));
        shape.setPoint(2, sf::Vector2f(3*size, 0));
        shape.setPoint(3, sf::Vector2f(2*size, size));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOrigin(sf::Vector2f(size/2*3, 0));
        shape.setPosition(sf::Vector2f(pos_x, pos_y));

        window->draw(shape);

        size/=1.4;
    }

    unsigned text_size = size/6*3;
    sf::Text text;
    text.setCharacterSize(text_size);
    text.setString(block->label);
    text.setFillColor(sf::Color::Black);
    
    sf::Font font;
    font.loadFromFile("/home/danila/Downloads/comic_sans.ttf");
    text.setFont(font);

    text.setOrigin(sf::Vector2f(text.getLocalBounds().width/2, 2));
    text.setPosition(pos_x, pos_y + (size - text_size)/2);
    window->draw(text);
}

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