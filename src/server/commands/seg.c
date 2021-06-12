/*
** EPITECH PROJECT, 2021
** seg.c
** File description:
** seg.c
*/

#include "server/server.h"

int seg(char *team_name, int fd, server_t *server)
{
    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    dprintf(fd, "seg %s\n", team_name);
    return SUCCESS;
}