/*
** EPITECH PROJECT, 2021
** sst.c
** File description:
** sst.c
*/

#include "server/server.h"

int sst(char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    if (!FD_ISSET(client->fd, &server->write_fd_set) || request[0] == NULL)
        return ERROR;
    g_board->freq = atoi(request[0]);
    dprintf(client->fd, "sst %d\n", g_board->freq);
    return SUCCESS;
}