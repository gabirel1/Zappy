/*
** EPITECH PROJECT, 2021
** pdr.c
** File description:
** pdr.c
*/

#include "server/server.h"

int pdr(int fd, int player_number, int resource_number, \
server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "pdr %d %d\n", player_number, resource_number);
    return SUCCESS;
}