#include <SFML/Graphics.hpp>

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

void renderBlock(Block *block, sf::RenderWindow *window, unsigned pos_x, unsigned pos_y, unsigned size)
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
        shape.setPoint(1, sf::Vector2f(size/2, 0));
        shape.setPoint(2, sf::Vector2f(2*size, 0));
        shape.setPoint(3, sf::Vector2f(3*size/2, size));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOrigin(sf::Vector2f(size, 0));
        shape.setPosition(sf::Vector2f(pos_x, pos_y));

        window->draw(shape);
    }

    unsigned text_size = size/5*3;
    sf::Text text;
    text.setCharacterSize(text_size);
    text.setString(block->label);
    text.setFillColor(sf::Color::Black);
    
    sf::Font font;
    font.loadFromFile("/home/danila/Downloads/comic_sans.ttf");
    text.setFont(font);

    text.setOrigin(sf::Vector2f(text.getLocalBounds().width/2 + 1.5, (size - text_size)/2 - 2));
    text.setPosition(pos_x, pos_y + (size - text_size)/2);
    window->draw(text);
}

int main()
{
    Block process0;
    process0.label = "A=0";
    process0.type = BLOCK_IO;

    sf::RenderWindow window(sf::VideoMode(400, 400), "Stupid Algorithm Making Program");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::White);

        renderBlock(&process0, &window, 100, 0, 20);

        window.display();
    }
    return 0;
}