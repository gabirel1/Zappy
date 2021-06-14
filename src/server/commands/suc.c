/*
** EPITECH PROJECT, 2021
** suc.c
** File description:
** suc.c
*/

#include "server/server.h"

int suc(int fd, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "suc\n");
    return SUCCESS;
}