/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Player
*/

#include "Player.hpp"

IA::Player::Player(int port, const std::string &addr, const std::string &teamName): _toStop(false), _socket(port, addr), _level(1), _teamName(teamName), _addr(addr), _port(port)
{
    std::cout << _socket.receiveMessage(_toStop) << std::endl;
    _socket.sendMessage(_teamName);
    std::string tmp = _socket.receiveMessage(_toStop);
    // std::string tmp1 = _socket.receiveMessage(_toStop);
    // std::cout << tmp1 << std::endl;
    std::size_t idx = tmp.find('\n');
    _clientNum = atoi(tmp.substr(0, idx).c_str());
    _position.first = atof(tmp.substr(idx + 1, tmp.find(' ', idx +1)).c_str());
    _position.second = atof(tmp.substr(tmp.find(' ', idx + 1), tmp.find('\n', idx + 1)).c_str());
    std::cout << "client name = " << _clientNum << " team name = " << _teamName << " X = " << _position.first << " Y =" << _position.second << std::endl;
    initInventory();
    // broadcast(std::string("iam here " + std::to_string(_clientNum) + " from team " + _teamName));
    // inventory();
    loop();
}

IA::Player::~Player()
{
}

void IA::Player::loop()
{
    std::string tmp;
    for (int i = 0; !_toStop ; i++) {
        tmp = _socket.receiveMessage(_toStop);
        // std::cout << "----------------------début----------------------" << std::endl;
        // this->inventory();
        if (tmp == "dead\n" || _toStop) {
            std::cout << _clientNum << " dead" << std::endl;
            _toStop = false;
            break;
        }
        // _socket.sendMessage("Forward");
        // while (_socket.receiveMessage(_toStop) != "ok\n");
        // std::cout << "Forward ok" << std::endl;

        this->look();
        while (!_tile.empty() && _tile[0].getResources()[DFOOD].second != 0) {
            this->take("food");
        }
        if (_tile.empty() && _tile[0].getResources()[DLIMATE].second)
            this->take("limate");
        // std::cout << "----------------------fin----------------------" << std::endl;
        this->inventory();
        if (this->_inventory[DLIMATE].second == 0) {
            this->look();
            if (!_tile.empty() || _tile[1].getResources()[DLIMATE].second == 0)
        }

        usleep(1000);
    }
    if (_toStop)
        std::cout << _clientNum << " dead" << std::endl;
}

void IA::Player::look()
{
    _tile.clear();
    _socket.sendMessage("Look");
    std::string tmp = _socket.receiveMessage(_toStop);
    int nbr = 0;

    while (tmp.empty()) {
        tmp = _socket.receiveMessage(_toStop);
        // usleep(1000);
    }
    if (tmp == "dead\n") {
        _toStop = true;
        return;
    }
    // while (tmp.empty() || tmp == "ok\n")
    //     tmp = _socket.receiveMessage(_toStop);
    // std::cout << "Look = {" + tmp + "}" << std::endl;
    if (tmp == "ko\n") {
        std::cout << "no look" << std::endl;
        return;
        // exit(84); // on mettra les erreurs après
    }
    for (std::size_t idx = 1; idx != tmp.npos; idx = tmp.find(',', idx + 1), ++nbr)
        parseSpace(tmp.find(',', idx + 1), tmp, idx, nbr);
    for (const auto &e: _tile)
        for (const auto &t: e.getResources())
            std::cout << e.getCaseNbr() << " and " << t.first << " = " << t.second << std::endl;
}


void IA::Player::parseSpace(std::size_t idx, std::string tmp, std::size_t last, int nbr)
{
    Tile tile(nbr);
    for (std::size_t tmpIdx = tmp.find(' ', last); 1; tmpIdx = tmp.find(' ', tmpIdx + 1)) {
        std::size_t test = tmp.find(' ', tmpIdx + 1);
        if (tmpIdx == tmp.npos)
            break;
        if (test > idx && idx != tmp.npos) {
            tile.addResources(getResourcesFromString(tmp.substr(tmpIdx + 1, idx - (tmpIdx + 1))));
            break;
        }
        if (tmp[test + 1] == ']') {
            tile.addResources(getResourcesFromString(tmp.substr(tmpIdx + 1, test - (tmpIdx + 1) )));
            break;
        }
        tile.addResources(getResourcesFromString(tmp.substr(tmpIdx + 1, test - (tmpIdx + 1))));
    }
    _tile.push_back(tile);
}

IA::resources IA::getResourcesFromString(const std::string &tmp)
{
    if (tmp == "food")
        return FOOD;
    if (tmp == "deraumere")
        return IA::DERAUMERE;
    if (tmp == "linemate")
        return LINEMATE;
    if (tmp == "sibur")
        return SIBUR;
    if (tmp == "mendiane")
        return MENDIANE;
    if (tmp == "phiras")
        return PHIRAS;
    if (tmp == "thystame")
        return THYSTAME;
    if (tmp == "player")
        return NONE;
    return (IA::resources::FOOD);
}

std::ostream &operator<<(std::ostream &os, const IA::resources &res)
{
    if (res == IA::FOOD)
        os << "food";
    if (res == IA::DERAUMERE)
        os << "deraumere";
    if (res == IA::LINEMATE)
        os << "linemate";
    if (res == IA::SIBUR)
        os << "sibur";
    if (res == IA::MENDIANE)
        os << "mendiane";
    if (res == IA::PHIRAS)
        os << "phiras";
    if (res == IA::THYSTAME)
        os << "thystame";
    return (os);
}

void IA::Player::take(std::string res)
{
    std::string tmp;

    if (_toStop)
        return;
    _socket.sendMessage("Take " + res);
    tmp = _socket.receiveMessage(_toStop);
    while (tmp != "ok\n") {
        if (tmp == "dead\n") {
            _toStop = true;
            return;
        }
        if (tmp == "ko\n") {
            std::cout << _clientNum << " didn't take " + res << std::endl;
            return;
        }
        tmp = _socket.receiveMessage(_toStop);
        usleep(1000);
    }
    std::cout << _clientNum << " took " + res << std::endl;
}

void IA::Player::move(std::string dir)
{
    std::string tmp;

    if (_toStop)
        return;
    // std::cout << "----------------------début forward----------------------" << std::endl;
    _socket.sendMessage(dir);
    tmp = _socket.receiveMessage(_toStop);
    while (tmp != "ok\n") {
        if (tmp == "dead\n") {
            _toStop = true;
            return;
        }
        if (tmp == "ko\n") {
            std::cout << _clientNum << " didn't go forward " << std::endl;
            return;
        }
        tmp = _socket.receiveMessage(_toStop);
        // std::cout << "----------------------fin forward = " + tmp + "----------------------" << std::endl;
        usleep(1000);
    }
    std::cout << _clientNum << " went forward" << std::endl;
}

void IA::Player::broadcast(const std::string &msg)
{
    if (_toStop)
        return;
    _socket.sendMessage("Broadcast " + msg);
    std::string tmp(_socket.receiveMessage(_toStop));

    while (tmp.empty())
        usleep(1000);
    if (tmp == "dead\n") {
        _toStop = true;
        return;
    }
    std::cout << ((tmp == "ok\n") ? "message sent!!" : "problem in sending message") << std::endl;
}

void IA::Player::forkPlayer()
{
    int pid = 0;

    if (_toStop)
        return;
    pid = fork();
    if (pid == 0) {
        Player newPlayer(_port, _addr, _teamName);
        exit (0);
    } else if (pid != -1)
        return;
}

void IA::Player::inventory()
{
    if (_toStop)
        return;
    clearInventory();
    _socket.sendMessage("Inventory");
    std::string tmp;

    while (tmp.empty()) {
        tmp = _socket.receiveMessage(_toStop);
        // usleep(1000);
    }
    if (tmp == "dead\n") {
        _toStop = true;
        return;
    }
    // std::cout << tmp << std::endl;
    // while (tmp == "ok\n")
    //     tmp = _socket.receiveMessage(_toStop);
    if (tmp == "ko\n" || tmp.empty()) {
        std::cout << "no inventory" << std::endl;
        return;
    }
    for (std::size_t idx = 1; idx != tmp.npos; idx = tmp.find(',', idx + 1))
        parseInventory(tmp.find(',', idx + 1), tmp, idx);
    for (const auto &i: _inventory)
        std::cout << i.first << " = " + std::to_string(i.second) << std::endl;
}

void IA::Player::addToInventory(resources res, int nb)
{
    for (auto &i: _inventory)
        if (i.first == res)
            i.second = nb;
}

void IA::Player::parseInventory(std::size_t idx, std::string tmp, std::size_t last)
{
    if (tmp[last] == ' ')
        last += 1;
    else if (tmp[last] == ',')
        last += 2;
    std::size_t idxTest = tmp.find(' ', last + 1);
    if (idx != tmp.npos)
        addToInventory(getResourcesFromString(tmp.substr(last, idxTest - last)), atoi(tmp.substr(idxTest, idx - idxTest).c_str()));
    else
        addToInventory(getResourcesFromString(tmp.substr(last, idxTest - last)), atoi(tmp.substr(idxTest, tmp.find(']') - idxTest).c_str()));
}

void IA::Player::clearInventory()
{
    for (auto &i: _inventory)
        i.second = 0;
}

void IA::Player::initInventory()
{
    _inventory.push_back(std::make_pair(FOOD, 0));
    _inventory.push_back(std::make_pair(DERAUMERE, 0));
    _inventory.push_back(std::make_pair(LINEMATE, 0));
    _inventory.push_back(std::make_pair(SIBUR, 0));
    _inventory.push_back(std::make_pair(MENDIANE, 0));
    _inventory.push_back(std::make_pair(PHIRAS, 0));
    _inventory.push_back(std::make_pair(THYSTAME, 0));
}