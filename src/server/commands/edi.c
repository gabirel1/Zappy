/*
** EPITECH PROJECT, 2021
** edi.c
** File description:
** edi.c
*/

#include "server/server.h"

int edi(int fd, int egg_number, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "edi %d\n", egg_number);
    return SUCCESS;
}