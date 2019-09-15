#include <SFML/Graphics.hpp>
#include <iostream>

#include "block_algorithm.hpp"
#include "connections.hpp"

#define WIN_W 400

void formatString(std::string &str)
{
    for(int i=0; i<str.length(); i++)
        if((str[i] >= 'a') && (str[i] <= 'z'))
            str[i] = 'A' + (str[i] - 'a'); 
}

int main()
{   
    Algorithm *alg = NULL;
    unsigned lines_count;

    Connect *connections = NULL;
    unsigned connects_count;

    unsigned block_size = 40;

    lines_count = 3;
    alg = initAlgorithm(3);
    initAlgorithmLine(alg, 0, 1);
    initAlgorithmLine(alg, 1, 1);
    initAlgorithmLine(alg, 2, 1);

    setAlgorithmBlock(alg, 0, 0, "Start", BLOCK_TERMINATOR);
    setAlgorithmBlock(alg, 1, 0, "Output:\nHello", BLOCK_IO);
    setAlgorithmBlock(alg, 2, 0, "End", BLOCK_TERMINATOR);

    connects_count = 2;
    connections = new Connect[2];
    connections[0] = Connect(getBlockSocket(alg, 00, BOTTOM, block_size, WIN_W),
                             getBlockSocket(alg, 10, TOP, block_size, WIN_W),
                             FROM_DOWN);

    connections[1] = Connect(getBlockSocket(alg, 10, BOTTOM, block_size, WIN_W),
                             getBlockSocket(alg, 20, TOP, block_size, WIN_W),
                             FROM_DOWN);

    #ifdef ABC

    std::string command;
    std::cout<<"STAMP$> ";
    std::getline(std::cin, command);
    while (command != "DRAW")
    {
        command+=" ";
        formatString(command);

        std::string command_part = command.substr(0, command.find(" "));
        command.erase(0, command.find(" ")+1);

        if (command_part == "EXIT")
        {
            exit(0);
        }
        elif (command_part == "HELP")
        {
            std::cout<<"\tALG\n";
                std::cout<<"\t\tINIT\n";
                    std::cout<<"\t\t\tALL [N]\n";
                        std::cout<<"\t\t\t\t--init algorithm with [N] lines\n";
                    std::cout<<"\t\t\tLINE [N] [M]\n";
                        std::cout<<"\t\t\t\t--init line [N] in algorithm with [M] blocks\n";
            std::cout<<"\n\tBLOCK\n";
                std::cout<<"\t\tSET [id] [BlockType] label\n";
                    std::cout<<"\t\t\t--set to block with id=[id](line*10+pos_in_line)\n";
                    std::cout<<"\t\t\ttype=[BlockType] one of {TERMINATOR | PROCESS | CONDITION | IO}\n";
                    std::cout<<"\t\t\twith lable=[label]\n";
            std::cout<<"\n\tCON\n";
                std::cout<<"\t\tINIT [N]\n";
                    std::cout<<"\t\t\t--init [N] algorithm connections\n";
                std::cout<<"\t\tCREATE [N] [FROM] [TO] [FROM_PORT] <label>\n";
                    std::cout<<"\t\t\t--create connection num=[N]\n";
                    std::cout<<"\t\t\tfrom block with id=[FROM] to block with id=[TO]\n";
                    std::cout<<"\t\t\tfrom [FROM] block connect should exit from port=[FROM_PORT]\n";
                    std::cout<<"\t\t\tport = {BOTTOM | LEFT | RIGHT}\n";
                    std::cout<<"\t\t\t<label> - optional arg. Set label near connection\n";
                
        }
        elif (command_part == "ALG")
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

        std::cout<<"STAMP$> ";
        std::getline(std::cin, command);
    }

    #endif

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

        drawConnections(connections, connects_count, block_size, &window);

        window.display();
    }
    return 0;
}