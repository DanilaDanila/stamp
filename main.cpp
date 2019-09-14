#include <SFML/Graphics.hpp>
#include <iostream>

#include "block_algorithm.hpp"
#include "line_renderer.hpp"

int main()
{   
    Algorithm *test_alg = initAlgorithm(3);
    initAlgorithmLine(test_alg, 0, 1);
        setAlgorithmBlock(test_alg, 0, 0, "Start", BLOCK_TERMINATOR);
    initAlgorithmLine(test_alg, 1, 1);
        setAlgorithmBlock(test_alg, 1, 0, "Input\n  A", BLOCK_IO);
    initAlgorithmLine(test_alg, 2, 1);
        setAlgorithmBlock(test_alg, 2, 0, "Return", BLOCK_TERMINATOR);

    sf::RenderWindow window(sf::VideoMode(400, 400), "Stupid Algorithm Making Program");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::White);

        drawAlgorithm(test_alg, 3, 40, &window);

        drawLine(40, 40, 300, 300, FROM_LEFT, 10, 20, 40, &window);

        window.display();
    }
    return 0;
}