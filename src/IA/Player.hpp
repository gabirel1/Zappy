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

    private:
        Socket _socket;
        int _level;
        std::string _teamName;
        std::string _addr;
        int _port;
        int _clientNum;
        std::pair<float, float> _position;
        std::vector <std::pair<resources, int>> _inventory;
        std::unordered_map<std::string, requirements> _levels;
        std::vector <Tile> _tile;
        void forkPlayer();
        void loop();
        void look();
        void inventory();
        void broadcast(const std::string &msg);
        void parseSpace(std::size_t idx, std::string tmp, std::size_t last, int nbr);
        void parseInventory(std::size_t idx, std::string tmp, std::size_t last);
        void clearInventory();
        void initInventory();
        void addToInventory(resources res, int nb);
        std::string move(std::string move);
        std::string take(std::string ressources);
};

// std::ostream &operator<<(std::ostream &, const IA::resources &);

#endif /* !PLAYER_HPP_ */
