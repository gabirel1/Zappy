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
    connect(this->_fd, (struct sockaddr *)&_servAdress, sizeof(_servAdress));
}

Socket::~Socket()
{
}

void Socket::sendMessage(const std::string order) const
{
    dprintf(_fd, "%s\n", order.c_str());
}

std::string Socket::receiveMessage(void)
{
    int cpy = dup(_fd);
    // FILE *file = fdopen(cpy, "r");

    std::string result;
    char buffer[4096] = {0};
    // std::size_t size = 0;
    // getline(&buffer, &size, file);

    fd_set read_fds;
    FD_ZERO(&read_fds);
    int fdmax = cpy;
    FD_SET(fdmax, &read_fds);
    memset(buffer, 0, 1048);
    struct timeval tv;
    tv.tv_usec = 10000;
    
    if (select(fdmax + 1, &read_fds, NULL, NULL, &tv) < 0)
        return ("");
    if (FD_ISSET(cpy, &read_fds)) {
        read(cpy, buffer, 1048);
        std::cout << buffer << std::endl;
        return (buffer);
    }
    return ("");
}
