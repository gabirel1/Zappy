/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Main
*/

#include "Parse.hpp"
#include "Socket.hpp"

int main(int ac, char **av)
{
    Parse pars;

    if (ac == 7 || ac == 5) {
        if (pars.parsing(ac, av) == false)
            return(84);
    }
    else
        return(84);
    Socket soc(pars.getPort(), pars.getMachine());
    std::cout << pars.getMachine() << " " << pars.getPort() << std::endl;
    std::cout << soc.receiveMessage() << std::endl;
    soc.sendMessage(pars.getName());
    std::cout << soc.receiveMessage() << std::endl;
    soc.sendMessage("Forward\n");
    std::cout << soc.receiveMessage() << std::endl;

    return (0);
     
}
