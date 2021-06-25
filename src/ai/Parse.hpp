/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Parse
*/

#ifndef PARSE_HPP_
#define PARSE_HPP_
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
#include <regex>
#include "Error.hpp"
#define UNSD __attribute__((unused))

class Parse {
    public:
        Parse();
        ~Parse();

        bool parsing(int ac, char **av);
        int getPort() const;
        std::string getName() const;
        std::string getMachine() const;


    protected:
    private:
        int _port;
        std::string _name;
        std::string _machine;
};

#endif /* !PARSE_HPP_ */
