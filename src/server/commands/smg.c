/*
** EPITECH PROJECT, 2021
** smg.c
** File description:
** smg.c
*/

#include "server/server.h"

int smg(char *message, int fd, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set)) {
        return ERROR;
    }
    dprintf(fd, "smg %s\n", message);
    return SUCCESS;
}