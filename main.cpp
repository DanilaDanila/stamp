#include <SFML/Graphics.hpp>

#define block_type           char
#define BLOCK_NAB           (0<<0)
#define BLOCK_TERMINATOR    (1<<0)
#define BLOCK_PROCESS       (1<<1)
#define BLOCK_CONDITION     (1<<2)
#define BLOCK_IO            (1<<3)

struct block
{
    unsigned pos_x;
    unsigned pos_y;
    unsigned size;
    std::string label;

    block_type type = BLOCK_NAB;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Stupid Algorithm Making Program");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        window.display();
    }
    return 0;
}