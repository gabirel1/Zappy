/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Player
*/

#include "Player.hpp"

IA::Player::Player(int port, const std::string &addr, const std::string &teamName) : _nbTeam(1), _toStop(false), _socket(port, addr), _level(1), _teamName(teamName), _addr(addr), _port(port), _hasFork(false)
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
    }
    std::size_t idx = tmp.find('\n');
    _clientNum = atoi(tmp.substr(0, idx).c_str());
    _position.first = atof(tmp.substr(idx + 1, tmp.find(' ', idx + 1)).c_str());
    _position.second = atof(tmp.substr(tmp.find(' ', idx + 1), tmp.find('\n', idx + 1)).c_str());
    initInventory();
    state = 0;
    try {
        loop();
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

IA::Player::~Player()
{
}

void IA::Player::loop()
{
    std::string tmp;

    try {
        for (int i = 0; _toStop != true && _level != 8; i++)
        {
            tmp = _socket.receiveMessage(_toStop, _clientNum);
            if (tmp == "dead\n" || _toStop)
            {
                std::cout << _clientNum << " dead" << std::endl;
                _toStop = false;
                break;
            }
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
            else if (_level == 8)
                levelHeigt();
            if (!_hasFork) {
                look();
                if (_tile[0].getResources()[DPLAYER].second != 0)
                    eject();
            }
        }
        if (_toStop)
            std::cout << _clientNum << " dead" << std::endl;
        if (_level == 8)
            levelHeigt();
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::look()
{
    _socket.sendMessage("Look");
    std::string tmp;
    int nbr = 0;

    try {
        waitResponse(tmp);
        if (tmp == "dead\n") {
            std::cout << "dead waitResponse" << std::endl;
            return;
        }
        if (tmp == "ko\n")
        {
            std::cout << "no look" << std::endl;
            return;
        }
        _tile.clear();
        for (std::size_t idx = 1; idx != tmp.npos; idx = tmp.find(',', idx + 1), ++nbr)
            parseSpace(tmp.find(',', idx + 1), tmp, idx, nbr);
        for (const auto &e : _tile)
            for (const auto &t : e.getResources())
                std::cout << e.getCaseNbr() << " and " << t.first << " = " << t.second << std::endl;
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
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
    if (tmp.find("food") != tmp.npos)
        return FOOD;
    if (tmp.find("deraumere") != tmp.npos)
        return IA::DERAUMERE;
    if (tmp.find("linemate") != tmp.npos)
        return LINEMATE;
    if (tmp.find("sibur") != tmp.npos)
        return SIBUR;
    if (tmp.find("mendiane") != tmp.npos)
        return MENDIANE;
    if (tmp.find("phiras") != tmp.npos)
        return PHIRAS;
    if (tmp.find("thystame") != tmp.npos)
        return THYSTAME;
    if (tmp.find("player") != tmp.npos)
        return PLAYER;
    return (IA::resources::NONE);
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

    try {
        if (_toStop)
            return;
        _socket.sendMessage("Take " + res);
        waitResponse(tmp);
        if (tmp == "dead\n") {
            std::cout << " dead take" << std::endl;
            return;
        }
        if (tmp == "ko\n")
        {
            std::cout << _clientNum << " didn't take " + res << std::endl;
            return;
        }
        std::cout << _clientNum << " took " + res << std::endl;
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::move(std::string dir)
{
    std::string tmp;

    try {
        if (_toStop)
            return;
        _socket.sendMessage(dir);
        waitResponse(tmp);
        if (tmp == "dead\n")
        {
            _toStop = true;
            std::cout << " dead move" << std::endl;
            return;
        }
        if (tmp == "ko\n")
        {
            std::cout << _clientNum << " didn't go forward " << std::endl;
            return;
        }
        std::cout << _clientNum << " went " << dir << std::endl;
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

bool IA::Player::treatMessageBroadcast(const std::string &msg)
{
    std::string tmp;

    if (msg.find("message") != msg.npos) {
        tmp = msg.substr(msg.find(',') + 2);
        std::reverse(tmp.begin(), tmp.end());
    }
    else
        tmp = msg;

    if (tmp.find("win") != tmp.npos && _level != 8) {
        std::cout << "we lose" << std::endl;
        throw error::ErrorAI(_teamName + " lose: ", " another team got level 8");
    }
    if (tmp.find("here") != tmp.npos && tmp.find(_teamName) != tmp.npos)
    {
        std::cerr << "####################################################team nb = " << _nbTeam<< "####################################################"<< std::endl;
        _nbTeam += 1;
        return (true);
    }
    std::cout << "message from server: [" << tmp << "]" << std::endl;
    return (false);
}

void IA::Player::broadcast(const std::string &msg)
{
    try {
        if (_toStop)
            return;
        _socket.sendMessage("Broadcast " + msg);
        std::string tmp;

        waitResponse(tmp);
        if (tmp == "dead\n")
        {
            _toStop = true;
            std::cout << " dead move" << std::endl;
            return;
        }
        if (tmp == "ko\n")
        {
            std::cout << "klskldlksdproblem in sending message" << std::endl;
            return;
        }
        std::cout << "message sent !!" << std::endl;
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::forkPlayer()
{
    try {    
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
        _hasFork = true;
        std::cout << "forking new trentorian " << tmp << std::endl;
        pid = fork();
        if (pid == 0)
        {
            Sbire newPlayer(_port, _addr, _teamName);
            exit(0);
        }
        else if (pid != -1)
        {
            return;
        } else if (pid == -1) {
            std::cout << "Error on fork" << std::endl;
            throw error::ErrorAI("can't fork", "forkPlayer");
        }
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
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
    try {
        std::string save;
        static int tmpTest  = 0;
        bool test = false;
        bool toAppend = false;
        tmp = _socket.receiveMessage(_toStop, _clientNum);
        while (1)
        {
            test = false;
            if (toAppend) {
                tmp.append(save);
                toAppend = false;
            }
            if (tmp.find('\n') == tmp.npos || (tmp.find('[') != tmp.npos && tmp.find(']') == tmp.npos)) {
                toAppend = true;
                save = tmp;
                tmp = _socket.receiveMessage(_toStop, _clientNum);
                continue;
            }
            std::cerr << tmpTest++ << " ++++++++++++++++++++++++++++++++++++" << tmp << "++++++++++++++++++++++++++++++++++++" << std::endl;
            if (tmp == "ok\n" || tmp == "ko\n")
                break;
            if (tmp == "dead\n")
            {
                _toStop = true;
                tmp = "dead\n";
                std::cout << "dead main" << std::endl;
                return;
            }
            if (!tmp.empty())
            {
                test = treatMessageBroadcast(tmp);
                if (test)
                    getOtherInput(tmp);
            }
            if (!tmp.empty()) {
                std::cerr << "tmp = " << tmp << std::endl;
                std::cerr << "okay" << std::endl;
                return;
            }
            tmp = _socket.receiveMessage(_toStop, _clientNum);
        }
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::inventory()
{
    try {
        if (_toStop)
            return;
        _socket.sendMessage("Inventory");
        std::string tmp;

        waitResponse(tmp);
        if (tmp == "dead\n") {
            std::cout << "inventory dead" << std::endl;
            return;
        }
        if (tmp == "ko\n" || tmp.empty())
        {
            std::cout << "no inventory" << std::endl;
            return;
        }
        if (tmp.find(']') == tmp.npos)
            return;
        clearInventory();
        for (std::size_t idx = 1; idx != tmp.npos; idx = tmp.find(',', idx + 1))
            parseInventory(tmp.find(',', idx + 1), tmp, idx);
        for (const auto &i : _inventory)
            std::cout << i.first << " = " + std::to_string(i.second) << std::endl;
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
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
        last += 2;
    std::size_t idxTest = tmp.find(' ', last + 1);
    if (idx != tmp.npos) {
        auto test1 = getResourcesFromString(tmp.substr(last, idxTest - last));
        auto test2 = atoi(tmp.substr(idxTest, idx - idxTest).c_str());
        addToInventory(test1, test2);
    }
    else {
        auto test1 = getResourcesFromString(tmp.substr(last, idxTest - last));
        std::string tmpCrash = tmp.substr(idxTest, tmp.find(']') - idxTest);
        std::cout << tmpCrash << std::endl;
        auto test2 = atoi(tmpCrash.c_str());
        addToInventory(test1, test2);
    }
}

void IA::Player::clearInventory()
{
    for (auto &i : _inventory)
        i.second = 0;
}

void IA::Player::incantation()
{
    try {
        std::string tmp;

        if (_toStop)
            return;
        _socket.sendMessage("Incantation");
        waitResponse(tmp);
        if (tmp == "dead\n") {
            std::cout << "dead incantation" << std::endl;
            return;
        }
        if (tmp == "ko\n")
        {
            std::cout << _clientNum << " didn't lvl up " << std::endl;
            return;
        }
        _level += 1;
        std::cout << tmp << std::endl;
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
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
    try {
        std::string tmp;

        if (_toStop)
            return;
        _socket.sendMessage("Set " + res);
        waitResponse(tmp);
        if (tmp == "dead\n") {
            std::cout << "dead setObject" << std::endl;
            return;
        }
        if (tmp == "ko\n")
        {
            std::cout << _clientNum << " didn't took down " + res << std::endl;
            return; 
        }
        std::cout << res << " was taken down" << std::endl;
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::levelOne(void)
{
    try {

        srand(time(NULL));

        this->look();
        if (_tile.size() < 4)
            return;
        this->inventory();
        if (state == 1)
        {
            if (_nbTeam == 6)
            {
                this->clearTile();
                this->setObject("linemate");
                this->broadcast("evolve");
                this->incantation();
                this->state = 2;
            }
            return;
        }
        if (state == 2) {
            return;
        }

        if (this->_inventory[DTHYSTAME].second >= 1 && this->_inventory[DPHIRAS].second >= 5 && this->_inventory[DMENDIANE].second >= 5 && this->_inventory[DSIBUR].second >= 10 && this->_inventory[DDERAUMERE].second >= 8 && this->_inventory[DLINEMATE].second >= 9 && this->_inventory[DFOOD].second >= 160)
        {
            if (state == 0)
            {
                for (int i = 0; i < 125; i++)
                {
                    this->setObject("food");
                }
                for (int i = 0; i < 5; i++)
                {
                    this->forkPlayer();
                    state = 1;
                }
            }

            return;
        }
        if (this->_inventory[DTHYSTAME].second >= 1 && this->_inventory[DPHIRAS].second >= 5 && this->_inventory[DMENDIANE].second >= 5 && this->_inventory[DSIBUR].second >= 10 && this->_inventory[DDERAUMERE].second >= 8 && this->_inventory[DLINEMATE].second >= 9)
        {
            std::cout << "all value has been aquire" << std::endl;

            this->look();
            if (_tile.size() < 4)
                return;
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
                this->move("Forward");
            }
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
            for (int f = _tile[0].getResources()[DFOOD].second; f > 0 && f < 100; f--)
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

                                    this->move("Forward");
                                }
                            }
                        }
                    }
                }
            }
        }
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}
void IA::Player::levelTwo(void)
{
    try {
        std::cout << _clientNum << " LVL 2" << std::endl;

        this->clearTile();
        this->setObject("linemate");
        this->setObject("deraumere");
        this->setObject("sibur");
        this->broadcast("evolve");
        this->incantation();
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::levelTree(void)
{
    try {
        std::cout << _clientNum << " LVL 3" << std::endl;
        this->clearTile();
        this->setObject("linemate");
        this->setObject("linemate");
        this->setObject("sibur");
        this->setObject("phiras");
        this->setObject("phiras");
        this->broadcast("evolve");
        this->incantation();
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}   

void IA::Player::levelFour(void)
{
    try {
        std::cout << _clientNum << " LVL 4" << std::endl;
        this->clearTile();
        this->setObject("linemate");

        this->setObject("deraumere");

        this->setObject("sibur");
        this->setObject("sibur");

        this->setObject("phiras");

        this->broadcast("evolve");
        this->incantation();
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::levelFive(void)
{
    try {
        std::cout << _clientNum << " LVL 5" << std::endl;
        this->clearTile();
        this->setObject("linemate");

        this->setObject("deraumere");
        this->setObject("deraumere");

        this->setObject("sibur");

        this->setObject("mendiane");
        this->setObject("mendiane");
        this->setObject("mendiane");

        this->broadcast("evolve");
        this->incantation();
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::levelSix(void)
{
    try {
        std::cout << _clientNum << " LVL 6" << std::endl;
        this->clearTile();
        this->setObject("linemate");

        this->setObject("deraumere");
        this->setObject("deraumere");

        this->setObject("sibur");
        this->setObject("sibur");
        this->setObject("sibur");

        this->setObject("phiras");

        this->broadcast("evolve");
        this->incantation();
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::levelSeven(void)
{
    try {
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

        this->setObject("phiras");
        this->setObject("phiras");

        this->setObject("thystame");

        this->broadcast("evolve");
        this->incantation();
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::levelHeigt(void)
{
    std::cout << _clientNum << "WINNNNNNN" << std::endl;

}

void IA::Player::clearTile(void)
{
    try {
        this->look();
        std::cerr << "-------------------------- look finished " << _level << " --------------------------" << std::endl;
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
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}

void IA::Player::eject()
{
    try {
        std::string tmp;

        if (_toStop)
            return;
        _socket.sendMessage("Eject");
        waitResponse(tmp);
        if (tmp == "dead\n") {
            _toStop = true;
            return;
        } if (tmp == "ko\n") {
            std::cout << _clientNum << " didn't ejected players" << std::endl;
            return;
        }
        std::cout << "ejecting player: " << tmp << std::endl;
    } catch (const error::ErrorAI &e) {
        throw e;
    } catch (const std::exception &e) {
        throw e;
    }
}