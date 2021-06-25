/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Parse
*/

#include "Parse.hpp"

Parse::Parse()
{
    _name = "";
    _port = 0;
    _machine = "localhost";
}

Parse::~Parse()
{
}

bool Parse::parsing(UNSD int ac, char **av)
{
    std::regex nb("^\\d+$");
    std::regex word("^\\w+$");
    std::smatch match;

    for (int i = 1; av[i] && av[i + 1]; i++)
    {
        std::string line(av[i]);
        std::string nextLine(av[i + 1]);

        if (line == "-p" && _port == 0) {
            if (std::regex_match(nextLine, match, nb))
            {
                _port = std::stoi(nextLine);
                i += 1;
            }
            else
                throw error::ErrorAI("Port arg is wrong", "-p");
        } else if (line == "-n" && _name.length() == 0) {
            std::cout << "2" << std::endl;
            if (std::regex_match(nextLine, match, word))
            {
                _name = nextLine;
                i += 1;
            }
            else
                throw error::ErrorAI("Name arg is wrong", "-p");
        } else if (line == "-h" && _machine == "localhost") {
            std::cout << "3" << std::endl;
            if (std::regex_match(nextLine, match, word))
            {
                _machine = nextLine;
                i += 1;
            }
            else
                throw error::ErrorAI("Machine arg is missing", "-p");
        } else
                throw error::ErrorAI("wrong arg", line);
    }
    if (_port == 0)
        throw error::ErrorAI("wrong port", "-p");
    if (_name.length() == 0)
        throw error::ErrorAI("wrong name", "-n");
    std::cout << _port << " " << _name << " " << _machine << std::endl;
    return (true);
}

int Parse::getPort() const {
    return(_port);
}

std::string Parse::getName() const {
    return(_name);
}

std::string Parse::getMachine() const {
    return(_machine);
}
