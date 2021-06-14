/*
** EPITECH PROJECT, 2021
** pbc.c
** File description:
** pbc.c
*/

#include "server/server.h"

int pbc(int fd, int player_number, char *message, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "pbc %d %s\n", player_number, message);
    return SUCCESS;
}