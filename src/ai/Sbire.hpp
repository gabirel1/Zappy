/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Sbire
*/

#ifndef SBIRE_HPP_
#define SBIRE_HPP_

#include "Player.hpp"
#include "IA.hpp"

class Sbire {
    public:
        Sbire(int port, const std::string &addr, const std::string &teamName);
        ~Sbire();

    protected:
    private:
        Socket _socket;
        std::string _teamName;
        std::string _addr;
        int _port;
        int _clientNum;
        void loop();
};

#endif /* !SBIRE_HPP_ */
