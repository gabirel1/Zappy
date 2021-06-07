/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** utils
*/

#include "server/server.h"

char *read_from_fd(int fd, fd_set *fd_set)
{
    char *buff = NULL;
    FILE *stream = NULL;
    size_t len = 0;
    ssize_t n = 0;

    if (!FD_ISSET(fd, fd_set))
        return NULL;
    stream = fdopen(dup(fd), "r");
    n = getline(&buff, &len, stream);
    if (n < 0)
        return NULL;
    buff[n - 1] = 0;
    return buff;
}