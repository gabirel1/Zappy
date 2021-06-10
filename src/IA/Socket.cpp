/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket(int port, std::string addr): _port(port), _addr(addr)
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
    FILE *stream = fdopen(cpy, "r");
    char *buffer = NULL;
    std::size_t n = 0;
    getline(&buffer, &n, stream);
    fclose(stream);
    return (std::string(buffer));
}
