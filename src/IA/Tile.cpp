/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Tile
*/

#include "Tile.hpp"

IA::Tile::Tile(int nbr): _caseNbr(nbr)
{
    _resourcesReal.push_back(std::make_pair(FOOD, 0));
    _resourcesReal.push_back(std::make_pair(LINEMATE, 0));
    _resourcesReal.push_back(std::make_pair(DERAUMERE, 0));
    _resourcesReal.push_back(std::make_pair(SIBUR, 0));
    _resourcesReal.push_back(std::make_pair(MENDIANE, 0));
    _resourcesReal.push_back(std::make_pair(PHIRAS, 0));
    _resourcesReal.push_back(std::make_pair(THYSTAME, 0));
}

IA::Tile::~Tile()
{
}

const std::vector<std::pair<IA::resources, int>> &IA::Tile::getResources() const
{
    return (_resourcesReal);
}

int IA::Tile::getCaseNbr() const
{
    return (_caseNbr);
}

void IA::Tile::addResources(resources res)
{
    for (auto &t: _resourcesReal)
        if (t.first == res)
            t.second += 1;
    // _resources.push_back(res);
}