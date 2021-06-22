/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <uuid/uuid.h>
#include <signal.h>

class Socket {
    public:
        Socket(int port, std::string addr);
        ~Socket();

        void sendMessage(const std::string) const;
        std::string receiveMessage(bool &, int);

    protected:
    private:
        struct sockaddr_in _servAdress;
        int _port;
        int _fd;
        std::string _addr;
        fd_set _read_fds;
};

#endif /* !SOCKET_HPP_ */
