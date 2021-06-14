/*
** EPITECH PROJECT, 2021
** pex.c
** File description:
** pex.c
*/

#include "server/server.h"

int pex(int fd, int player_number, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "pex %d\n", player_number);
    return SUCCESS;
}