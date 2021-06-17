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
            std::cout << "1" << std::endl;
            if (std::regex_match(nextLine, match, nb))
            {
                _port = std::stoi(nextLine);
                i += 1;
            }
            else
            {
                std::cout << "Bad port" << std::endl;
                return (false);
            }
        } else if (line == "-n" && _name.length() == 0) {
            std::cout << "2" << std::endl;
            if (std::regex_match(nextLine, match, word))
            {
                _name = nextLine;
                i += 1;
            }
            else
            {
                std::cout << "Bad name 1" << std::endl;
                return (false);
            }
        } else if (line == "-h" && _machine == "localhost") {
            std::cout << "3" << std::endl;
            if (std::regex_match(nextLine, match, word))
            {
                _machine = nextLine;
                i += 1;
            }
            else
            {
                std::cout << "Bad machine" << std::endl;
                return (false);
            }
        
        } else {
            std::cout << "Bad arg" << std::endl;
            return (false);
        }
    }
    if (_port == 0 || _name.length() == 0)
        return (false);
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
