/*
** EPITECH PROJECT, 2021
** eht.c
** File description:
** eht.c
*/

#include "server/server.h"

int eht(int fd, int egg_number, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "eht %d\n", egg_number);
    return SUCCESS;
}