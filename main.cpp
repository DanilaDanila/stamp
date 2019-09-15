#include <SFML/Graphics.hpp>
#include <iostream>

#include "block_algorithm.hpp"
#include "connections.hpp"

#define WIN_W 400

int main()
{   
    Algorithm *alg = NULL;
    unsigned lines_count;

    Connect *connections = NULL;
    unsigned connects_count;

    unsigned block_size = 40;

    std::string command;
    std::cout<<"STAMP $> ";
    std::getline(std::cin, command);
    while (command != "DRAW")
    {
        command+=" ";
        std::string command_part = command.substr(0, command.find(" "));
        command.erase(0, command.find(" ")+1);
        if (command_part == "ALG")
        {
            command_part = command.substr(0, command.find(" "));
            command.erase(0, command.find(" ")+1);
            if (command_part == "INIT")
            {
                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);
                if (command_part == "ALL")
                {
                    command_part = command.substr(0, command.find(" "));
                    command.erase(0, command.find(" ")+1);
                    lines_count = std::stoi(command_part);

                    alg = initAlgorithm(lines_count);
                }
                elif (command_part == "LINE")
                {
                    command_part = command.substr(0, command.find(" "));
                    command.erase(0, command.find(" ")+1);

                    unsigned line = std::stoi(command_part);

                    command_part = command.substr(0, command.find(" "));
                    command.erase(0, command.find(" ")+1);

                    unsigned block_count = std::stoi(command_part);

                    initAlgorithmLine(alg, line, block_count);
                }
                else
                    std::cout<<"UNDEFINED COMMAND:\n\t"<<command_part<<"\n";
            }
            else
                std::cout<<"UNDEFINED COMMAND:\n\t"<<command_part<<"\n";
        }
        elif (command_part == "BLOCK")
        {
            command_part = command.substr(0, command.find(" "));
            command.erase(0, command.find(" ")+1);

            if(command_part == "SET")
            {
                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);

                unsigned block_id = std::stoi(command_part);

                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);

                BlockType bt;
                if (command_part == "TERMINATOR")
                    bt = BLOCK_TERMINATOR;
                elif (command_part == "PROCESS")
                    bt = BLOCK_PROCESS;
                elif (command_part == "CONDITION")
                    bt = BLOCK_CONDITION;
                elif (command_part == "IO")
                    bt = BLOCK_IO;
                else
                    std::cout<<"UNDEFINED COMMAND:\n\t"<<command_part<<"\n";

                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);

                //command_part.replace(command_part.find("~"), 1, "\n");

                setAlgorithmBlock(alg, block_id/10, block_id%10, command_part, bt);
            }
            else
                std::cout<<"UNDEFINED COMMAND:\n\t"<<command_part<<"\n";
        }
        elif (command_part == "CON")
        {
            command_part = command.substr(0, command.find(" "));
            command.erase(0, command.find(" ")+1);

            if (command_part == "INIT")
            {
                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);

                connects_count = std::stoi(command_part);

                connections = new Connect[connects_count];
            }
            elif (command_part == "CREATE")
            {
                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);
                unsigned c_num = std::stoi(command_part);

                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);
                unsigned id_from = std::stoi(command_part);

                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);
                unsigned id_to = std::stoi(command_part);

                command_part = command.substr(0, command.find(" "));
                command.erase(0, command.find(" ")+1);

                Port p;

                if (command_part == "BOTTOM")
                    p = BOTTOM;
                elif (command_part == "LEFT")
                    p = LEFT;
                elif (command_part == "RIGHT")
                    p = RIGHT;
                else
                    std::cout<<"UNDEFINED COMMAND:\n\t"<<command_part<<"\n";

                std::string label;
                if (command != "")
                {
                    command_part = command.substr(0, command.find(" "));
                    command.erase(0, command.find(" ")+1);
                    label = command_part;
                }

                connections[c_num] = Connect(getBlockSocket(alg, id_from, p, block_size, WIN_W),
                                             getBlockSocket(alg, id_to, TOP, block_size, WIN_W),
                                             p, label);
            }
            else
                std::cout<<"UNDEFINED COMMAND:\n\t"<<command_part<<"\n";
        }
        else
            std::cout<<"UNDEFINED COMMAND:\n\t"<<command_part<<"\n";

        std::cout<<"STAMP $> ";
        std::getline(std::cin, command);
    }

    sf::RenderWindow window(sf::VideoMode(400, WIN_W), "Stupid Algorithm Making Program");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::White);

        drawAlgorithm(alg, lines_count, block_size, &window);

        //drawConnections(connections, connects_count, block_size, &window);

        window.display();
    }
    return 0;
}