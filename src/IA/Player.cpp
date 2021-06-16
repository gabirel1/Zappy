/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Player
*/

#include "Player.hpp"

IA::Player::Player(int port, const std::string &addr, const std::string &teamName): _socket(port, addr), _level(1), _teamName(teamName), _addr(addr), _port(port)
{
    std::cout << _socket.receiveMessage() << std::endl;
    _socket.sendMessage(_teamName);
    std::string tmp = _socket.receiveMessage();
    // std::string tmp1 = _socket.receiveMessage();
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

void IA::Player::look()
{
    _tile.clear();
    _socket.sendMessage("Look\n");
    std::string tmp = _socket.receiveMessage();
    int nbr = 0;

    std::cout << tmp << std::endl;
    if (tmp == "ko")
        exit(84); // on mettra les erreurs après
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

std::string IA::Player::take(std::string ressources)
{
    _socket.sendMessage("Take " + ressources + "\n");
    return (_socket.receiveMessage());
}

void IA::Player::move(std::string dir)
{
    _socket.sendMessage(dir);
}

// std::string IA::Player::inv()
// {
//     _socket.sendMessage("Inventory\n");
//     return (_socket.receiveMessage());
// }

void IA::Player::broadcast(const std::string &msg)
{
    _socket.sendMessage("Broadcast " + msg);
    std::string tmp(_socket.receiveMessage());

    std::cout << ((tmp == "ok\n") ? "message sent!!" : "problem in sending message") << std::endl;
}

void IA::Player::loop()
{
    std::string tmp;
    for (int i = 0; i > -1 ; i++) {

        std::cout << "yolo" << std::endl;
        tmp = _socket.receiveMessage();
        if (tmp == "dead\n") {
            std::cout << "dead" << std::endl;
            break;
        }
        inventory();
        // _socket.sendMessage("Forward\n");
        // std::cout << _socket.receiveMessage() << std::endl;
        if (!tmp.empty())
            std::cout << tmp << std::endl;
        // on fait les actions ici
        // _socket.sendMessage("Left\n");
    }
    
}

void IA::Player::forkPlayer()
{
    int pid = 0;

    pid = fork();
    if (pid == 0) {
        Player newPlayer(_port, _addr, _teamName);
        exit (0);
    } else if (pid != -1)
        return;
}

void IA::Player::inventory()
{
    // _inventory.clear();
    _socket.sendMessage("Inventory\n");
    std::string tmp = _socket.receiveMessage();

    std::cout << tmp << std::endl;
    if (tmp == "ko")
        exit (84);
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