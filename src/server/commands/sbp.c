/*
** EPITECH PROJECT, 2021
** sbp.c
** File description:
** sbp.c
*/

#include "server/server.h"

int sbp(int fd, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "sbp\n");
    return SUCCESS;
}