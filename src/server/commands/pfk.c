/*
** EPITECH PROJECT, 2021
** pfk.c
** File description:
** pfk.c
*/

#include "server/server.h"

int pfk(int fd, int player_number, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "pfk %d\n", player_number);
    return SUCCESS;
}