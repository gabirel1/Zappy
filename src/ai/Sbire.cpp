/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Sbire
*/

#include "Sbire.hpp"

IA::Sbire::Sbire(int port, const std::string &addr, const std::string &teamName)  : _socket(port, addr),  _teamName(teamName), _addr(addr), _port(port),  _toStop(false)
{
    std::cout << _socket.receiveMessage(_toStop, _clientNum) << std::endl;
    _socket.sendMessage(_teamName);
    std::string tmp = _socket.receiveMessage(_toStop, _clientNum);
    if (tmp.empty() || tmp == "ko\n")
        exit(84);
    std::size_t idx = tmp.find('\n');
    _clientNum = atoi(tmp.substr(0, idx).c_str());
    _position.first = atof(tmp.substr(idx + 1, tmp.find(' ', idx + 1)).c_str());
    _position.second = atof(tmp.substr(tmp.find(' ', idx + 1), tmp.find('\n', idx + 1)).c_str());
    // tmp = _socket.receiveMessage();
    while (tmp != "ok\n") {
        usleep(1000);
        tmp = _socket.receiveMessage(_toStop, _clientNum);
    }
    for (int i = 0; i < 25; i++) {
        // std::cout << "-----------------------took foood-----------------------" << std::endl;
        this->take("food");
    }
    broadcast("here " + _teamName);
    // recolté 25 food
}

IA::Sbire::~Sbire()
{
}

void IA::Sbire::loop() {
    while (!_toStop) {
        std::string tmp = _socket.receiveMessage(_toStop, _clientNum);
        if (tmp == "dead\n" || _toStop) {
            _toStop = false;
            std::cout << _clientNum << "dead" << std::endl;
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
    tmp = _socket.receiveMessage(_toStop, _clientNum);
    while (1) {
        if (tmp == "ko\n") {
            std::cout << "problem sending message" << std::endl;
            return;
        } else if (tmp == "dead\n") {
            _toStop = true;
            return;
        } else if (tmp == "ok\n") {
            std::cout << "message sent !!" << std::endl;
            return;
        }
        tmp = _socket.receiveMessage(_toStop, _clientNum);
        usleep(100000);
    }
}

void IA::Sbire::take(const std::string &res)
{
    std::string tmp;

    if (_toStop)
        return;
    _socket.sendMessage("Take " + res);
    tmp = _socket.receiveMessage(_toStop, _clientNum);
    while (1) {
        if (tmp == "ko\n") {
            std::cout <<  _clientNum << " didn't take " << res << std::endl;
            return;
        }else if (tmp == "dead\n") {
            _toStop = true;
            return;
        }else if (tmp == "ok\n") {
            std::cout << _clientNum << " took " << res << std::endl;
            return;
        }
        // std::cout << _clientNum << " " << std::endl;
        tmp = _socket.receiveMessage(_toStop, _clientNum);
        usleep(100000);
    }
}