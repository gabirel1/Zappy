/*
** EPITECH PROJECT, 2021
** bct.c
** File description:
** bct.c
*/

#include "server/server.h"

int bct(char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    tile_t *tile = NULL;
    int pos_x = atoi((request[0]) ? request[0] : "-1");
    int pos_y = atoi((request[1]) ? request[1] : "-1");

    tile = get_tile_by_pos(g_board->map, pos_x, pos_y, g_board);
    if (tile == NULL) {
        printf("Error : tile not found\n");
        return ERROR;
    }
    if (!FD_ISSET(client->fd, &server->write_fd_set)) {
        return ERROR;
    }
    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", tile->posx, \
    tile->posy, tile->resources[FOOD], tile->resources[LINEMATE], \
    tile->resources[DERAUMERE], tile->resources[SIBUR], \
    tile->resources[MENDIANE], tile->resources[PHIRAS], \
    tile->resources[THYSTAME]);

    return SUCCESS;
}