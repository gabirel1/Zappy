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

    Socket soc(pars.getPort(), pars.getMachine());
    std::cout << soc.receiveMessage() << std::endl;
    soc.sendMessage(pars.getName());
    std::cout << soc.receiveMessage() << std::endl;

    IA::Player newPlayer(pars.getPort(), pars.getMachine(), pars.getName());

    for (int i = 0; i > -1; i++) {
        std::cout << newPlayer.move("Forward") << std::endl;
        std::cout << newPlayer.move("Right") << std::endl;
        std::cout << newPlayer.take("linemate") << std::endl;
        std::cout << newPlayer.take("deraumere") << std::endl;
        std::cout << newPlayer.take("sibur") << std::endl;
        std::cout << newPlayer.take("mendiane") << std::endl;
        std::cout << newPlayer.take("phiras") << std::endl;
        std::cout << newPlayer.take("thystame") << std::endl;
        std::cout << newPlayer.take("food") << std::endl;
        
        newPlayer.look();

        // soc.sendMessage("Forward\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // if (i%4 == 0) {
        //     soc.sendMessage("Right\n");
        //     std::cout << soc.receiveMessage() << std::endl;
        // }

        // soc.sendMessage("Right\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // soc.sendMessage("Take food\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // soc.sendMessage("Take linemate\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // soc.sendMessage("Take deraumere\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // soc.sendMessage("Take sibur\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // soc.sendMessage("Take mendiane\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // soc.sendMessage("Take phiras\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // soc.sendMessage("Take thystame\n");
        // std::cout << soc.receiveMessage() << std::endl;

        // soc.sendMessage("Inventory\n");
        // std::cout << soc.receiveMessage() << std::endl;
    }


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
