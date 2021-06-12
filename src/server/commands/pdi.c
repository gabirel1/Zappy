/*
** EPITECH PROJECT, 2021
** pdi.c
** File description:
** pdi.c
*/

#include "server/server.h"

int pdi(int fd, int player_number, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "pdi %d\n", player_number);
    return SUCCESS;
}