/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Main
*/

#include "Parse.hpp"
#include "Socket.hpp"
#include "Player.hpp"

int main(int ac, char **av)
{
    Parse pars;

    if (ac == 7 || ac == 5) {
        if (pars.parsing(ac, av) == false)
            return(84);
    }
    else
        return(84);
    IA::Player newPlayer(pars.getPort(), pars.getMachine(), pars.getName());
    // Socket soc(pars.getPort(), pars.getMachine());
    // std::cout << pars.getMachine() << " " << pars.getPort() << std::endl;
    // std::cout << soc.receiveMessage() << std::endl;
    // soc.sendMessage(pars.getName());
    // std::cout << soc.receiveMessage() << std::endl;
    // while (1) {
    //     soc.sendMessage("Forward\n");
    //     std::cout << soc.receiveMessage() << std::endl;

    //     soc.sendMessage("Right\n");
    //     std::cout << soc.receiveMessage() << std::endl;
    // }

    return (0);
     
}
