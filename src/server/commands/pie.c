/*
** EPITECH PROJECT, 2021
** pie.c
** File description:
** pie.c
*/

#include "server/server.h"

int pie(int fd, int pos[2], int result, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "pie %d %d %d\n", pos[0], pos[1], result);
    return SUCCESS;
}