/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Player
*/

#include "Player.hpp"

IA::Player::Player(int port, const std::string &addr, const std::string &teamName) : _nbTeam(1), _toStop(false), _socket(port, addr), _level(1), _teamName(teamName), _addr(addr), _port(port)
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
    // std::cout << "client name = " << _clientNum << " team name = " << _teamName << " X = " << _position.first << " Y =" << _position.second << std::endl;
    initInventory();
    state =     0;
    // broadcast(std::string("iam here " + std::to_string(_clientNum) + " from team " + _teamName));
    // usleep(100000);
    // broadcast("team");
    loop();
}

IA::Player::~Player()
{
}

void IA::Player::loop()
{
    std::string tmp;

    for (int i = 0; _toStop != true; i++)
    {
        tmp = _socket.receiveMessage(_toStop);
        if (tmp == "dead\n" || _toStop)
        {
            std::cout << _clientNum << " dead" << std::endl;
            _toStop = false;
            break;
        }
        // if (!tmp.empty())
        // {
        //     treatMessageBroadcast(tmp);
        // }

        // std::cout << "=======================================" << _clientNum << "there is " << _nbTeam << " in " << _teamName << "=======================================   " << _level << std::endl;
        if (_level == 1)
            this->levelOne();
        else if (_level == 2)
            this->levelTwo();
        else if (_level == 3)
            this->levelTree();
        else if (_level == 4)
            this->levelFour();
        else if (_level == 5)
            this->levelFive();
        else if (_level == 6)
            this->levelSix();
        else if (_level == 7)
            this->levelSeven();
        else
        {
            std::cout << "lvl pb" << std::endl;
            if (!tmp.empty())
            {
                bool test = treatMessageBroadcast(tmp);
                if (test)
                    std::cerr << "===============================finished team from loop ===============================" << std::endl;
            }

            //     std::cout << "=======================================" << _clientNum << "there is " << _nbTeam << " in " << _teamName << "=======================================   " << _level << std::endl;
            //     if (_level == 1) {
            //         this->look();
            //         for (int f = _tile[0].getResources()[DFOOD].second; f > 0; f--)
            //         {
            //             std::cout << "food has been taken" << std::endl;
            //             this->take("food");
            //         }
            //         if (_tile[0].getResources()[DLINEMATE].second != 0)
            //             this->take("linemate");
            //         this->inventory();
            //         if (this->_inventory[DLINEMATE].second == 0)
            //         {
            //             this->look();
            //             if ((_tile[1].getResources()[DLINEMATE].second == 0 && _tile[2].getResources()[DLINEMATE].second == 0 && _tile[3].getResources()[DLINEMATE].second == 0))
            //             {
            //                 if (i % 4 == 0)
            //                     this->move("Left");
            //                 if (i % 6 == 0)
            //                     this->move("Right");
            //                 this->move("Forward");
            //             }
            //             else if (_tile[2].getResources()[DLINEMATE].second != 0)
            //                 this->move("Forward");
            //             else if (_tile[1].getResources()[DLINEMATE].second != 0)
            //             {
            //                 this->move("Forward");
            //                 this->move("Left");
            //                 this->move("Forward");
            //             }
            //             else if (_tile[3].getResources()[DLINEMATE].second != 0)
            //             {
            //                 this->move("Forward");
            //                 this->move("Right");
            //                 this->move("Forward");
            //             }
            //         }
            //         else
            //         {
            //             setObject("linemate");
            //             std::cout << _clientNum << "-----------------incantation--------------------" << std::endl;
            //             for (int f = _tile[0].getResources()[DLINEMATE].second - 1; f > 0; f--)
            //             {
            //                 std::cout << "linemate has been taken" << std::endl;
            //                 this->take("linemate");
            //             }
            //             for (int f = _tile[0].getResources()[DDERAUMERE].second; f > 0; f--)
            //             {
            //                 std::cout << "deraumere has been taken" << std::endl;
            //                 this->take("deraumere");
            //             }
            //             for (int f = _tile[0].getResources()[DSIBUR].second; f > 0; f--)
            //             {
            //                 std::cout << "sibur has been taken" << std::endl;
            //                 this->take("sibur");
            //             }
            //             for (int f = _tile[0].getResources()[DMENDIANE].second; f > 0; f--)
            //             {
            //                 std::cout << "mendiane has been taken" << std::endl;
            //                 this->take("mendiane");
            //             }
            //             for (int f = _tile[0].getResources()[DPHIRAS].second; f > 0; f--)
            //             {
            //                 std::cout << "phiras has been taken" << std::endl;
            //                 this->take("phiras");
            //             }
            //             for (int f = _tile[0].getResources()[DTHYSTAME].second; f > 0; f--)
            //             {
            //                 std::cout << "thystame has been taken" << std::endl;
            //                 this->take("thystame");
            //             }
            //             this->incantation();
            //             (_level != 1) ? this->forkPlayer() : (void)0;
            //         }
            //         usleep(1000);
            //     }
            //     else
            //     {
            //         this->look();
            //         for (int f = _tile[0].getResources()[DFOOD].second; f > 0; f--)
            //         {
            //             std::cout << "food has been taken" << std::endl;
            //             this->take("food");
            //         }
            //         if ((_tile[1].getResources()[FOOD].second == 0 && _tile[2].getResources()[FOOD].second == 0 && _tile[3].getResources()[FOOD].second == 0))
            //         {
            //             int r = rand() % 3 + 0;
            //             if (r == 0)
            //                 this->move("Left");
            //             else if (r == 1)
            //                 this->move("Right");
            //             this->move("Forward");
            //         }
            //         else if (_tile[2].getResources()[FOOD].second != 0)
            //             this->move("Forward");
            //         else if (_tile[1].getResources()[FOOD].second != 0)
            //         {
            //             this->move("Forward");
            //             this->move("Left");
            //             this->move("Forward");
            //         }
            //         else if (_tile[3].getResources()[FOOD].second != 0)
            //         {
            //             this->move("Forward");
            //             this->move("Right");
            //             this->move("Forward");
            //         }
            //         std::cout << _clientNum << " LVL 2" << std::endl;
            //     }
            // }
            if (_toStop)
                std::cout << _clientNum << " dead" << std::endl;
        }
    }
}

void IA::Player::look()
{
    _tile.clear();
    _socket.sendMessage("Look");
    std::string tmp;
    int nbr = 0;

    waitResponse(tmp);
    if (tmp == "dead\n")
        return;
    if (tmp == "ko\n")
    {
        std::cout << "no look" << std::endl;
        return;
    }
    for (std::size_t idx = 1; idx != tmp.npos; idx = tmp.find(',', idx + 1), ++nbr)
        parseSpace(tmp.find(',', idx + 1), tmp, idx, nbr);
    for (const auto &e : _tile)
        for (const auto &t : e.getResources())
            std::cout << e.getCaseNbr() << " and " << t.first << " = " << t.second << std::endl;
}

void IA::Player::parseSpace(std::size_t idx, std::string tmp, std::size_t last, int nbr)
{
    Tile tile(nbr);
    for (std::size_t tmpIdx = tmp.find(' ', last); 1; tmpIdx = tmp.find(' ', tmpIdx + 1))
    {
        std::size_t test = tmp.find(' ', tmpIdx + 1);
        if (tmpIdx == tmp.npos)
            break;
        if (test > idx && idx != tmp.npos)
        {
            tile.addResources(getResourcesFromString(tmp.substr(tmpIdx + 1, idx - (tmpIdx + 1))));
            break;
        }
        if (tmp[test + 1] == ']')
        {
            tile.addResources(getResourcesFromString(tmp.substr(tmpIdx + 1, test - (tmpIdx + 1))));
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
    waitResponse(tmp);
    if (tmp == "dead\n")
        return;
    if (tmp == "ko\n")
    {
        std::cout << _clientNum << " didn't take " + res << std::endl;
        return;
    }
    std::cout << _clientNum << " took " + res << std::endl;
}

void IA::Player::move(std::string dir)
{
    std::string tmp;

    if (_toStop)
        return;
    _socket.sendMessage(dir);
    waitResponse(tmp);
    if (tmp == "dead\n")
    {
        _toStop = true;
        return;
    }
    if (tmp == "ko\n")
    {
        std::cout << _clientNum << " didn't go forward " << std::endl;
        return;
    }
    std::cout << _clientNum << " went " << dir << std::endl;
}

bool IA::Player::treatMessageBroadcast(const std::string &msg)
{
    std::string tmp;

    if (msg.find("message") != msg.npos)
        tmp = msg.substr(msg.find(',') + 2);
    else
        tmp = msg;
    // if (tmp.find("team") != tmp.npos) {
    //     // usleep(10000);
    //     broadcast("mytm:" + _teamName);
    //     std::cerr << "##########################endsending " << _teamName << " ##########################" << std::endl;
    //     return (true);
    // }
    // else if (tmp.find("mytm") != tmp.npos)
    // {
    //     if (tmp.substr(tmp.find(':') + 1, tmp.find('\n') - tmp.find(':') - 1) == _teamName)
    //         _nbTeam += 1;
    //     // std::cout << "{" << tmp.substr(tmp.find(':') + 1, tmp.find('\n') - tmp.find(':') - 1) << "}" << std::endl;
    //     return (true);
    // } else
    if (tmp.find("here") != tmp.npos)
    {
        _nbTeam += 1;
        return (true);
    }
    std::cout << "message from server: [" << tmp << "]" << std::endl;
    return (false);
}

void IA::Player::broadcast(const std::string &msg)
{
    if (_toStop)
        return;
    std::cerr << "-------------------------" << msg << " debut-------------------------" << std::endl;
    _socket.sendMessage("Broadcast " + msg);
    std::string tmp;

    waitResponse(tmp);
    if (tmp == "dead\n")
    {
        _toStop = true;
        std::cerr << "-------------------------" << msg << " end dead -------------------------" << std::endl;
        return;
    }
    if (tmp == "ko\n")
    {
        std::cout << "klskldlksdproblem in sending message" << std::endl;
        std::cerr << "-------------------------" << msg << " end ko-------------------------" << std::endl;
        return;
    }
    std::cout << "message sent !!" << std::endl;
    std::cerr << "-------------------------" << msg << " end -------------------------" << std::endl;
}

void IA::Player::forkPlayer()
{
    int pid = 0;
    std::string tmp;

    if (_toStop)
        return;
    _socket.sendMessage("Fork");
    waitResponse(tmp);
    if (tmp == "ko\n")
    {
        std::cout << "can't fork" << std::endl;
        return;
    }
    std::cout << "forking new trentorian " << tmp << std::endl;
    pid = fork();
    if (pid == 0)
    {
        Player newPlayer(_port, _addr, _teamName);
        exit(0);
    }
    else if (pid != -1)
    {
        // broadcast("team");
        return;
    }
}

void IA::Player::getOtherInput(std::string &tmp)
{
    int nb = 0;

    for (std::size_t idx = tmp.find('\n'); idx != tmp.npos; idx = tmp.find('\n', idx + 1), ++nb)
        ;
    if (nb > 1 && tmp.find("message") == 0)
        tmp = tmp.substr(tmp.find('\n') + 1);
    else if (nb > 1 && tmp.find("message") != 0)
        tmp = tmp.substr(0, tmp.find('\n'));
    else
        tmp.clear();
}

void IA::Player::waitResponse(std::string &tmp)
{
    std::string other;
    bool test = false;
    tmp = _socket.receiveMessage(_toStop);
    while (1)
    {
        if (tmp == "ok\n" || tmp == "ko\n")
            break;
        if (tmp == "dead\n")
        {
            _toStop = true;
            tmp = "dead\n";
            return;
        }
        if (!tmp.empty())
        {
            if (!(test = treatMessageBroadcast(tmp)))
                break;
            else
            {
                std::cerr << "===============================finished team from waitResponse" << _clientNum << " ===============================" << std::endl;
                getOtherInput(tmp);
            }
        }
        if (test)
        {
            std::cerr << "tmp = " << tmp << std::endl;
            if (!tmp.empty())
                return;
        }
        tmp = _socket.receiveMessage(_toStop);
        usleep(100000);
    }
}

void IA::Player::inventory()
{
    if (_toStop)
        return;
    clearInventory();
    _socket.sendMessage("Inventory");
    std::string tmp;

    waitResponse(tmp);
    if (tmp == "dead\n")
        return;
    if (tmp == "ko\n" || tmp.empty())
    {
        std::cout << "no inventory" << std::endl;
        return;
    }
    for (std::size_t idx = 1; idx != tmp.npos; idx = tmp.find(',', idx + 1))
        parseInventory(tmp.find(',', idx + 1), tmp, idx);
    for (const auto &i : _inventory)
        std::cout << i.first << " = " + std::to_string(i.second) << std::endl;
}

void IA::Player::addToInventory(resources res, int nb)
{
    for (auto &i : _inventory)
        if (i.first == res)
            i.second = nb;
}

void IA::Player::parseInventory(std::size_t idx, std::string tmp, std::size_t last)
{
    if (tmp[last] == ' ')
        last += 1;
    else if (tmp[last] == ',')
        last += 1;
    std::size_t idxTest = tmp.find(' ', last + 1);
    if (idx != tmp.npos)
        addToInventory(getResourcesFromString(tmp.substr(last, idxTest - last)), atoi(tmp.substr(idxTest, idx - idxTest).c_str()));
    else
        addToInventory(getResourcesFromString(tmp.substr(last, idxTest - last)), atoi(tmp.substr(idxTest, tmp.find(']') - idxTest).c_str()));
}

void IA::Player::clearInventory()
{
    for (auto &i : _inventory)
        i.second = 0;
}

void IA::Player::incantation()
{
    std::string tmp;

    if (_toStop)
        return;
    _socket.sendMessage("Incantation");
    tmp = _socket.receiveMessage(_toStop);
    waitResponse(tmp);
    if (tmp == "dead\n")
        return;
    if (tmp == "ko\n")
    {
        std::cout << _clientNum << " didn't lvl up " << std::endl;
        return;
    }
    std::cout << tmp << std::endl;
    _level += 1;
}

void IA::Player::initInventory()
{
    _inventory.push_back(std::make_pair(FOOD, 0));
    _inventory.push_back(std::make_pair(LINEMATE, 0));
    _inventory.push_back(std::make_pair(DERAUMERE, 0));
    _inventory.push_back(std::make_pair(SIBUR, 0));
    _inventory.push_back(std::make_pair(MENDIANE, 0));
    _inventory.push_back(std::make_pair(PHIRAS, 0));
    _inventory.push_back(std::make_pair(THYSTAME, 0));
}

void IA::Player::setObject(const std::string &res)
{
    std::string tmp;

    if (_toStop)
        return;
    _socket.sendMessage("Set " + res);
    waitResponse(tmp);
    if (tmp == "dead\n")
        return;
    if (tmp == "ko\n")
    {
        std::cout << _clientNum << " didn't took down " + res << std::endl;
        return;
    }
    std::cout << res << " was taken down" << std::endl;
}

// void IA::Player::levelOne(void)
// {
//     std::cout << _clientNum << " LVL 1" << std::endl;

//     this->look();
//     for (int f = _tile[0].getResources()[DFOOD].second; f > 0; f--)
//     {
//         std::cout << "food has been taken" << std::endl;
//         this->take("food");
//     }
//     if (_tile[0].getResources()[DLINEMATE].second != 0)
//         this->take("linemate");
//     this->inventory();
//     if (this->_inventory[DLINEMATE].second == 0)
//     {
//         this->look();
//         if ((_tile[1].getResources()[DLINEMATE].second == 0 && _tile[2].getResources()[DLINEMATE].second == 0 && _tile[3].getResources()[DLINEMATE].second == 0))
//         {
//             int r = rand() % 3 + 0;
//             if (r == 0)
//                 this->move("Left");
//             else if (r == 1)
//                 this->move("Right");
//             this->move("Forward");
//         }
//         else if (_tile[2].getResources()[DLINEMATE].second != 0)
//             this->move("Forward");
//         else if (_tile[1].getResources()[DLINEMATE].second != 0)
//         {
//             this->move("Forward");
//             this->move("Left");
//             this->move("Forward");
//         }
//         else if (_tile[3].getResources()[DLINEMATE].second != 0)
//         {
//             this->move("Forward");
//             this->move("Right");
//             this->move("Forward");
//         }
//     }
//     else
//     {
//         setObject("linemate");
//         std::cout << _clientNum << "-----------------incantation--------------------" << std::endl;
//         this->clearTile();
//         this->incantation();
//         if (_nbTeam < 2)
//             this->forkPlayer();
//     }

//     usleep(1000);
// }
void IA::Player::levelOne(void)
{
    srand(time(NULL));

    this->look();
    this->inventory();
    if (this->_inventory[DTHYSTAME].second >= 1 && this->_inventory[DPHIRAS].second >= 5 && this->_inventory[DMENDIANE].second >= 5 && this->_inventory[DSIBUR].second >= 10 && this->_inventory[DDERAUMERE].second >= 8 && this->_inventory[DLINEMATE].second >= 9 && this->_inventory[DFOOD].second >= 160)
    {
        if (state == 0)
        {
            for (int i = 0; i < 6; i++)
            {
                this->forkPlayer();
                state = 1;
            }
        }
        // for (int i = 0; i <= 125; i++) {
        //     this->setObject("food");
        // }

        return;
    }
    if (this->_inventory[DTHYSTAME].second >= 1 && this->_inventory[DPHIRAS].second >= 5 && this->_inventory[DMENDIANE].second >= 5 && this->_inventory[DSIBUR].second >= 10 && this->_inventory[DDERAUMERE].second >= 8 && this->_inventory[DLINEMATE].second >= 9)
    {
        std::cout << "all value has been aquire" << std::endl;

        if (_nbTeam == 6)
        {
            this->clearTile();
            this->setObject("linemate");
            this->broadcast("evolve");
            this->incantation();
        }
        if (state == 1)
        {
            return;
        }

        this->look();
        if (_tile[2].getResources()[DFOOD].second != 0)
        {
            this->move("Forward");
        }
        else if (_tile[1].getResources()[DFOOD].second != 0)
        {
            this->move("Forward");
            this->move("Left");
            this->move("Forward");
        }
        else if (_tile[3].getResources()[DFOOD].second != 0)
        {
            this->move("Forward");
            this->move("Right");
            this->move("Forward");
        }
        else
        {
            std::cout << "-------------" << std::endl;
            int r = rand() % 2 + 0;
            std::cout << "-------------" << r << std::endl;
            if (r == 0)
                this->move("Left");
            else if (r == 1)
                this->move("Right");
            this->move("Forward");
        }
        // while (1 < -1)
        // {
        // }
    }
    if (this->_inventory[DTHYSTAME].second == 0 && _tile[0].getResources()[DTHYSTAME].second != 0)
        this->take("thystame");
    if ((this->_inventory[DPHIRAS].second < 5 && _tile[0].getResources()[DPHIRAS].second != 0))
    {
        for (int f = _tile[0].getResources()[DPHIRAS].second; f > 0; f--)
        {
            std::cout << "phiras has been taken" << std::endl;
            this->take("phiras");
        }
    }
    if ((this->_inventory[DMENDIANE].second < 5 && _tile[0].getResources()[DMENDIANE].second != 0))
    {
        for (int f = _tile[0].getResources()[DMENDIANE].second; f > 0; f--)
        {
            std::cout << "mendiane has been taken" << std::endl;
            this->take("mendiane");
        }
    }
    if ((this->_inventory[DSIBUR].second < 10 && _tile[0].getResources()[DSIBUR].second != 0))
    {
        for (int f = _tile[0].getResources()[DSIBUR].second; f > 0; f--)
        {
            std::cout << "sibur has been taken" << std::endl;
            this->take("sibur");
        }
    }
    if ((this->_inventory[DDERAUMERE].second < 8 && _tile[0].getResources()[DDERAUMERE].second != 0))
    {
        for (int f = _tile[0].getResources()[DDERAUMERE].second; f > 0; f--)
        {
            std::cout << "deraumere has been taken" << std::endl;
            this->take("deraumere");
        }
    }
    if ((this->_inventory[DLINEMATE].second < 9 && _tile[0].getResources()[DLINEMATE].second != 0))
    {
        for (int f = _tile[0].getResources()[DLINEMATE].second; f > 0; f--)
        {
            std::cout << "linemate has been taken" << std::endl;
            this->take("linemate");
        }
    }
    if (_tile[0].getResources()[DFOOD].second != 0)
    {
        for (int f = _tile[0].getResources()[DFOOD].second; f > 0; f--)
        {
            std::cout << "food has been taken" << std::endl;
            this->take("food");
        }
    }
    this->inventory();
    if (this->_inventory[DTHYSTAME].second < 1 && _tile[2].getResources()[DTHYSTAME].second != 0)
    {
        this->move("Forward");
    }
    else if (this->_inventory[DTHYSTAME].second < 1 && _tile[1].getResources()[DTHYSTAME].second != 0)
    {
        this->move("Forward");
        this->move("Left");
        this->move("Forward");
    }
    else if (this->_inventory[DTHYSTAME].second < 1 && _tile[3].getResources()[DTHYSTAME].second != 0)
    {
        this->move("Forward");
        this->move("Right");
        this->move("Forward");
    }
    else
    {
        if (this->_inventory[DPHIRAS].second < 5 && _tile[2].getResources()[DPHIRAS].second != 0)
        {
            this->move("Forward");
        }
        else if (this->_inventory[DPHIRAS].second < 5 && _tile[1].getResources()[DPHIRAS].second != 0)
        {
            this->move("Forward");
            this->move("Left");
            this->move("Forward");
        }
        else if (this->_inventory[DPHIRAS].second < 5 && _tile[3].getResources()[DPHIRAS].second != 0)
        {
            this->move("Forward");
            this->move("Right");
            this->move("Forward");
        }
        else
        {
            if (this->_inventory[DMENDIANE].second < 5 && _tile[2].getResources()[DMENDIANE].second != 0)
            {
                this->move("Forward");
            }
            else if (this->_inventory[DMENDIANE].second < 5 && _tile[1].getResources()[DMENDIANE].second != 0)
            {
                this->move("Forward");
                this->move("Left");
                this->move("Forward");
            }
            else if (this->_inventory[DMENDIANE].second < 5 && _tile[3].getResources()[DMENDIANE].second != 0)
            {
                this->move("Forward");
                this->move("Right");
                this->move("Forward");
            }
            else
            {
                if (this->_inventory[DSIBUR].second < 10 && _tile[2].getResources()[DSIBUR].second != 0)
                {
                    this->move("Forward");
                }
                else if (this->_inventory[DSIBUR].second < 10 && _tile[1].getResources()[DSIBUR].second != 0)
                {
                    this->move("Forward");
                    this->move("Left");
                    this->move("Forward");
                }
                else if (this->_inventory[DSIBUR].second < 10 && _tile[3].getResources()[DSIBUR].second != 0)
                {
                    this->move("Forward");
                    this->move("Right");
                    this->move("Forward");
                }
                else
                {
                    if (this->_inventory[DDERAUMERE].second < 8 && _tile[2].getResources()[DDERAUMERE].second != 0)
                    {
                        this->move("Forward");
                    }
                    else if (this->_inventory[DDERAUMERE].second < 8 && _tile[1].getResources()[DDERAUMERE].second != 0)
                    {
                        this->move("Forward");
                        this->move("Left");
                        this->move("Forward");
                    }
                    else if (this->_inventory[DDERAUMERE].second < 8 && _tile[3].getResources()[DDERAUMERE].second != 0)
                    {
                        this->move("Forward");
                        this->move("Right");
                        this->move("Forward");
                    }
                    else
                    {
                        if (this->_inventory[DLINEMATE].second < 9 && _tile[2].getResources()[DLINEMATE].second != 0)
                        {
                            this->move("Forward");
                        }
                        else if (this->_inventory[DLINEMATE].second < 9 && _tile[1].getResources()[DLINEMATE].second != 0)
                        {
                            this->move("Forward");
                            this->move("Left");
                            this->move("Forward");
                        }
                        else if (this->_inventory[DLINEMATE].second < 9 && _tile[3].getResources()[DLINEMATE].second != 0)
                        {
                            this->move("Forward");
                            this->move("Right");
                            this->move("Forward");
                        }
                        else
                        {
                            if (_tile[2].getResources()[DFOOD].second != 0)
                            {
                                this->move("Forward");
                            }
                            else if (_tile[1].getResources()[DFOOD].second != 0)
                            {
                                this->move("Forward");
                                this->move("Left");
                                this->move("Forward");
                            }
                            else if (_tile[3].getResources()[DFOOD].second != 0)
                            {
                                this->move("Forward");
                                this->move("Right");
                                this->move("Forward");
                            }
                            else
                            {
                                int r = rand() % 2 + 0;
                                std::cout << "-------------" << r << std::endl;

                                if (r == 0)
                                    this->move("Left");
                                else if (r == 1)
                                    this->move("Right");
                                this->move("Forward");
                            }
                        }
                    }
                }
            }
        }
    }
}
void IA::Player::levelTwo(void)
{
    std::cout << _clientNum << " LVL 2" << std::endl;

    this->clearTile();
    this->setObject("linemate");
    this->setObject("deraumere");
    this->setObject("sibur");
    // brodcast incantation
    this->incantation();
}

// void IA::Player::levelTwo(void)
// {
//     std::cout << _clientNum << " LVL 2" << std::endl;

//     this->look();
//     for (int f = _tile[0].getResources()[DFOOD].second; f > 0; f--)
//     {
//         std::cout << "food has been taken" << std::endl;
//         this->take("food");
//     }
//     if ((_tile[1].getResources()[FOOD].second == 0 && _tile[2].getResources()[FOOD].second == 0 && _tile[3].getResources()[FOOD].second == 0))
//     {
//         int r = rand() % 3 + 0;
//         if (r == 0)
//             this->move("Left");
//         else if (r == 1)
//             this->move("Right");
//         this->move("Forward");
//     }
//     else if (_tile[2].getResources()[FOOD].second != 0)
//         this->move("Forward");
//     else if (_tile[1].getResources()[FOOD].second != 0)
//     {
//         this->move("Forward");
//         this->move("Left");
//         this->move("Forward");
//     }
//     else if (_tile[3].getResources()[FOOD].second != 0)
//     {
//         this->move("Forward");
//         this->move("Right");
//         this->move("Forward");
//     }
// }

void IA::Player::levelTree(void)
{
    std::cout << _clientNum << " LVL 3" << std::endl;
    this->clearTile();
    this->setObject("linemate");
    this->setObject("linemate");

    this->setObject("sibur");

    this->setObject("pĥiras");
    this->setObject("pĥiras");

    // brodcast incantation
    this->incantation();
}

void IA::Player::levelFour(void)
{
    std::cout << _clientNum << " LVL 4" << std::endl;
    this->clearTile();
    this->setObject("linemate");

    this->setObject("deraumere");

    this->setObject("sibur");
    this->setObject("sibur");

    this->setObject("pĥiras");

    // brodcast incantation
    this->incantation();
}

void IA::Player::levelFive(void)
{
    std::cout << _clientNum << " LVL 5" << std::endl;
    this->clearTile();
    this->setObject("linemate");

    this->setObject("deraumere");
    this->setObject("deraumere");

    this->setObject("sibur");

    this->setObject("mendiane");
    this->setObject("mendiane");
    this->setObject("mendiane");

    // brodcast incantation
    this->incantation();
}

void IA::Player::levelSix(void)
{
    std::cout << _clientNum << " LVL 6" << std::endl;
    this->clearTile();
    this->setObject("linemate");

    this->setObject("deraumere");
    this->setObject("deraumere");

    this->setObject("sibur");
    this->setObject("sibur");
    this->setObject("sibur");

    this->setObject("pĥiras");

    // brodcast incantation
    this->incantation();
}

void IA::Player::levelSeven(void)
{
    std::cout << _clientNum << " LVL 7" << std::endl;

    this->clearTile();
    this->setObject("linemate");
    this->setObject("linemate");

    this->setObject("deraumere");
    this->setObject("deraumere");

    this->setObject("sibur");
    this->setObject("sibur");

    this->setObject("mendiane");
    this->setObject("mendiane");

    this->setObject("pĥiras");
    this->setObject("pĥiras");

    this->setObject("thystame");

    // brodcast incantation
    this->incantation();
}

void IA::Player::levelHeigt(void)
{
    std::cout << _clientNum << "WINNNNNNN" << std::endl;
}

void IA::Player::clearTile(void)
{
    this->look();
    for (int f = _tile[0].getResources()[DFOOD].second; f > 0; f--)
    {
        std::cout << "food has been taken" << std::endl;
        this->take("food");
    }
    for (int f = _tile[0].getResources()[DLINEMATE].second; f > 0; f--)
    {
        std::cout << "linemate has been taken" << std::endl;
        this->take("linemate");
    }
    for (int f = _tile[0].getResources()[DDERAUMERE].second; f > 0; f--)
    {
        std::cout << "deraumere has been taken" << std::endl;
        this->take("deraumere");
    }
    for (int f = _tile[0].getResources()[DSIBUR].second; f > 0; f--)
    {
        std::cout << "sibur has been taken" << std::endl;
        this->take("sibur");
    }
    for (int f = _tile[0].getResources()[DMENDIANE].second; f > 0; f--)
    {
        std::cout << "mendiane has been taken" << std::endl;
        this->take("mendiane");
    }
    for (int f = _tile[0].getResources()[DPHIRAS].second; f > 0; f--)
    {
        std::cout << "phiras has been taken" << std::endl;
        this->take("phiras");
    }
    for (int f = _tile[0].getResources()[DTHYSTAME].second; f > 0; f--)
    {
        std::cout << "thystame has been taken" << std::endl;
        this->take("thystame");
    }
}