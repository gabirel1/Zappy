/*
** EPITECH PROJECT, 2021
** sgt.c
** File description:
** sgt.c
*/

#include "server/server.h"

int sgt(UNSD char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    dprintf(client->fd, "sgt %d\n", g_board->freq);
    return SUCCESS;
}