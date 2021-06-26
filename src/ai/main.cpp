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

    try {
        if (ac == 7 || ac == 5) {
            if (pars.parsing(ac, av) == false)
                return(84);
        }
        else
            throw error::ErrorAI("wrong number of arguments", "main.cpp");
    } catch (const error::ErrorAI &e) {
        std::cout << e.what() << " " << e.where() << std::endl;
        return (84);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return (84);
    }

    try {
        IA::Player newPlayer(pars.getPort(), pars.getMachine(), pars.getName());
    } catch (const error::ErrorAI &e) {
        std::cout << e.what() << " " << e.where() << std::endl;
        return (0);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return (84);
    } 

    // for (int i = 0; i > -1; i++) {
    //     std::cout << newPlayer.move("Forward") << std::endl;
    //     std::cout << newPlayer.move("Right") << std::endl;
    //     std::cout << newPlayer.take("linemate") << std::endl;
    //     std::cout << newPlayer.take("deraumere") << std::endl;
    //     std::cout << newPlayer.take("sibur") << std::endl;
    //     std::cout << newPlayer.take("mendiane") << std::endl;
    //     std::cout << newPlayer.take("phiras") << std::endl;
    //     std::cout << newPlayer.take("thystame") << std::endl;
    //     std::cout << newPlayer.take("food") << std::endl;
    // }
    return (0);
     
}
