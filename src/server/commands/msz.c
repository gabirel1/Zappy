/*
** EPITECH PROJECT, 2021
** msz.c
** File description:
** msz.c
*/

#include "server/server.h"

int msz(UNSD char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    dprintf(client->fd, "msz %d %d\n", g_board->width, g_board->height);
    return SUCCESS;
}