/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Sbire
*/

#include "Sbire.hpp"

IA::Sbire::Sbire(int port, const std::string &addr, const std::string &teamName)  : _socket(port, addr),  _teamName(teamName), _addr(addr), _port(port),  _toStop(false)
{
    std::cout << _socket.receiveMessage(_toStop) << std::endl;
    _socket.sendMessage(_teamName);
    std::string tmp = _socket.receiveMessage(_toStop);
    if (tmp.empty() || tmp == "ko\n")
        exit(84);
    std::size_t idx = tmp.find('\n');
    _clientNum = atoi(tmp.substr(0, idx).c_str());
    _position.first = atof(tmp.substr(idx + 1, tmp.find(' ', idx + 1)).c_str());
    _position.second = atof(tmp.substr(tmp.find(' ', idx + 1), tmp.find('\n', idx + 1)).c_str());
    for (int i = 0; i < 25; i++) {
        this->take("food");
    }
    // recolté 25 food
    broadcast("here " + _teamName);
}

IA::Sbire::~Sbire()
{
}

void IA::Sbire::loop() {
    while (!_toStop) {
        std::string tmp = _socket.receiveMessage(_toStop);
        if (tmp == "dead\n" || _toStop) {
            _toStop = false;
            std::cout << "dead" << std::endl;
            break;
        }
        //  attendre le brocast
        //  Brodcaste recu == Incantation
    };
}

void IA::Sbire::broadcast(const std::string &msg)
{
    std::string tmp;

    if (_toStop)
        return;
    _socket.sendMessage("Broadcast " + msg);
    tmp = _socket.receiveMessage(_toStop);
    while (1) {
        if (tmp == "ko\n") {
            std::cout << "problem sending message" << std::endl;
            return;
        } if (tmp == "dead\n") {
            _toStop = true;
            return;
        } if (tmp == "ok\n") {
            std::cout << "message sent !!" << std::endl;
            return;
        }
        usleep(100000);
        _socket.receiveMessage(_toStop);
    }
}

void IA::Sbire::take(const std::string &res)
{
    std::string tmp;

    if (_toStop)
        return;
    _socket.sendMessage("Take " + res);
    tmp = _socket.receiveMessage(_toStop);
    while (1) {
        if (tmp == "ko\n") {
            std::cout <<  _clientNum << " didn't take " << res << std::endl;
            return;
        } if (tmp == "dead\n") {
            _toStop = true;
            return;
        } if (tmp == "ok\n") {
            std::cout << _clientNum << " took " << res << std::endl;
            return;
        }
        usleep(100000);
        _socket.receiveMessage(_toStop);
    }
}