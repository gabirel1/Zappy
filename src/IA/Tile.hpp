/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Tile
*/

#ifndef TILE_HPP_
#define TILE_HPP_
#include "IA.hpp"

class IA::Tile {
    public:
        Tile(int tileNbr);
        ~Tile();

        int getCaseNbr(void) const;
        const std::vector<std::pair<resources, int>> &getResources(void) const;
        void addResources(resources resources);
    private:
        int _caseNbr;
        std::vector <resources> _resources;
        std::vector <std::pair<resources, int>> _resourcesReal;
};

#endif /* !TILE_HPP_ */
