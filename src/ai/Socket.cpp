/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket(int port, std::string addr) : _port(port), _addr(addr)
{
    this->_fd = socket(AF_INET, SOCK_STREAM, 0);
    _servAdress.sin_family = AF_INET;
    _servAdress.sin_port = htons(port);
    if (_addr == "localhost")
        _addr = "127.0.0.1";
    _servAdress.sin_addr.s_addr = inet_addr(_addr.c_str());
    if (connect(this->_fd, (struct sockaddr *)&_servAdress, sizeof(_servAdress)) < 0)
        perror("connect");
}

Socket::~Socket()
{
}

void Socket::sendMessage(const std::string order) const
{
    dprintf(_fd, "%s\n", order.c_str());
    usleep(10000);
}

std::string Socket::receiveMessage(bool &ts)
{
    if (ts) {
        std::cout << "dude you're dead" << std::endl; 
    }
    int cpy = dup(_fd);
    std::string result;
    char buffer[4096] = {0};
    usleep(10000);

    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(cpy, &read_fds);
    struct timeval tv{0, 100};
    // // tv.tv_usec = 10000;
    
    if (select(cpy + 1, &read_fds, NULL, NULL, &tv) < 0) {
        perror("select");
        return ("");
    }
    if (FD_ISSET(cpy, &read_fds)) {
        read(cpy, buffer, 1048);
        close(cpy);
        if (std::string(buffer) == "dead\n")
            ts = true;
        // std::cout << buffer << std::endl;
        return (buffer);
    }
    return ("");
}
