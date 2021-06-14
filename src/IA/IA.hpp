/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** IA
*/

#ifndef IA_HPP_
#define IA_HPP_
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Socket.hpp"

namespace IA {
    typedef enum {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        NONE
    } resources;

    typedef struct {
        int _nbPlayerPrecedents;
        int _linemate;
        int _deraumere;
        int _sibur;
        int _mendiane;
        int _phiras;
        int _thystame;
    } requirements;

    class Tile;
    class Player;
    resources getResourcesFromString(const std::string &);
}
std::ostream &operator<<(std::ostream &, const IA::resources &);

#endif /* !IA_HPP_ */
