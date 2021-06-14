/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include "IA.hpp"
#include "Tile.hpp"

class IA::Player {
    public:
        Player(int port, const std::string &addr, const std::string &teamName);
        ~Player();

        void look();
    private:
        Socket _socket;
        int _level;
        std::string _teamName;
        std::string _addr;
        int _port;
        int _clientNum;
        std::pair<float, float> _position;
        std::unordered_map<std::string, requirements> _levels;
        std::vector <Tile> _tile;
        void parseSpace(std::size_t idx, std::string tmp, std::size_t last, int nbr);
};

// std::ostream &operator<<(std::ostream &, const IA::resources &);

#endif /* !PLAYER_HPP_ */
