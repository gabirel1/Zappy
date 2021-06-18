/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Sbire
*/

#include "Sbire.hpp"

Sbire::Sbire(int port, const std::string &addr, const std::string &teamName)  : _socket(port, addr),  _teamName(teamName), _addr(addr), _port(port)
{

    // recolté 25 food

}

Sbire::~Sbire()
{
}

void Sbire::loop() {
    // while {
    //      attendre le brocast
    //      Brodcaste recu == Incantation
    // };
}