/*
** EPITECH PROJECT, 2021
** mct.c
** File description:
** mct.c
*/

#include "server/server.h"

int mct(UNSD char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    for (int y_index = 0; y_index < g_board->height; y_index++) {
        for (int x_index = 0; x_index < g_board->width; x_index++) {
            dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", \
            TILE_CONTENT.posx, TILE_CONTENT.posy, TILE_CONTENT_R[FOOD], \
            TILE_CONTENT_R[LINEMATE], TILE_CONTENT_R[DERAUMERE], \
            TILE_CONTENT_R[SIBUR], TILE_CONTENT_R[MENDIANE], \
            TILE_CONTENT_R[PHIRAS], TILE_CONTENT_R[THYSTAME]);
        }
    }
    return SUCCESS;
}
