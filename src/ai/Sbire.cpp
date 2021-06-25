/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Sbire
*/

#include "Sbire.hpp"

IA::Sbire::Sbire(int port, const std::string &addr, const std::string &teamName)  : _socket(port, addr),  _teamName(teamName), _addr(addr), _port(port),  _toStop(false)
{
    std::string tmp = _socket.receiveMessage(_toStop, _clientNum);
    while (tmp.empty())
        tmp = _socket.receiveMessage(_toStop, _clientNum);
    std::cout << tmp << std::endl;
    _socket.sendMessage(_teamName);
    tmp = _socket.receiveMessage(_toStop, _clientNum);
    std::cerr << "[" << tmp << "]" << std::endl;
    while (tmp.empty() || std::count(tmp.begin(), tmp.end(), '\n') != 2) {
        tmp += _socket.receiveMessage(_toStop, _clientNum);
        usleep(100000);
    }
    std::size_t idx = tmp.find('\n');
    _clientNum = atoi(tmp.substr(0, idx).c_str());
    _position.first = atof(tmp.substr(idx + 1, tmp.find(' ', idx + 1)).c_str());
    _position.second = atof(tmp.substr(tmp.find(' ', idx + 1), tmp.find('\n', idx + 1)).c_str());
    // std::cerr <<"=============================================[tmp = " << tmp << "]============================================="  << std::endl;
    tmp = _socket.receiveMessage(_toStop, _clientNum);
    while (tmp.find("ok") == tmp.npos) {
        // std::cerr <<"=============================================[tmp = " << tmp << "]============================================="  << std::endl;
        tmp = _socket.receiveMessage(_toStop, _clientNum);
        usleep(100000);
    }
    // std::cerr <<"=============================================[tmp = " << tmp << "]============================================="  << std::endl;
    for (int i = 0; i < 25; i++) {
        // std::cout << _clientNum << "-----------------------took foood-----------------------" << std::endl;
        this->take("food");
    }
    std::cerr << "sjkdddddddddddddddddddddddddddflhjsdfhkjhsdjkhsdjkhfskdjhfsdjhkjsdhjksdjfhkjshdfkjhdskjfhkjsdhksdhfjksdhfjksdfhksdjhfsdjhkdsf" << std::endl;
    broadcast("here " + _teamName);
    loop();
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
            std ::cout << _clientNum << "dead" << std::endl;
            break;
        }
        //  attendre le brocast
        //  Brodcaste recu == Incantation
    };
}

void IA::Sbire::broadcast(const std::string &msg)
{
    std::string tmp;

    std::cerr << "'''''''''''''''''''''''''''''''''''''''''broadcast " << msg << std::endl;
    if (_toStop)
        return;
    _socket.sendMessage("Broadcast " + msg);
    tmp = _socket.receiveMessage(_toStop, _clientNum);
    while (1) {
        if (tmp.find("ko") != tmp.npos) {
            std::cout << "problem sending message" << std::endl;
            return;
        } else if (tmp.find("dead") != tmp.npos) {
            _toStop = true;
            return;
        } else if (tmp.find("ok") != tmp.npos) {
            std::cout << "message sent !!" << std::endl;
            return;
        }
        usleep(100000);
        tmp = _socket.receiveMessage(_toStop, _clientNum);
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
        if (tmp.find("ko") != tmp.npos) {
            std::cout <<  _clientNum << " didn't take " << res << std::endl;
            return;
        }else if (tmp.find("dead") != tmp.npos) {
            _toStop = true;
            return;
        }else if (tmp.find("ok") != tmp.npos) {
            std::cout << _clientNum << " took " << res << std::endl;
            return;
        }
        // std::cout << _clientNum << " " << std::endl;
        usleep(100000); 
        tmp = _socket.receiveMessage(_toStop, _clientNum);
    }
}