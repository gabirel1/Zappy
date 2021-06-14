/*
** EPITECH PROJECT, 2021
** ebo.c
** File description:
** ebo.c
*/

#include "server/server.h"

int ebo(int fd, int egg_number, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "ebo %d\n", egg_number);
    return SUCCESS;
}