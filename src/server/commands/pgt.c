/*
** EPITECH PROJECT, 2021
** pgt.c
** File description:
** pgt.c
*/

#include "server/server.h"

int pgt(int fd, int player_number, int resource_number, \
server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "pgt %d %d\n", player_number, resource_number);
    return SUCCESS;
}