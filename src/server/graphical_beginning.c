/*
** EPITECH PROJECT, 2021
** graphical_beginning.c
** File description:
** graphical_beginning.c
*/

#include "server/server.h"

int graphic_send_first_batch(game_board_t *g_board, \
client_t *client, server_t *server)
{
    if (!FD_ISSET(client->fd, &server->write_fd_set)) {
        printf("error on fd isset\n");
        return ERROR;
    }
    dprintf(client->fd, "msz %d %d\n", g_board->width, g_board->height);
    dprintf(client->fd, "sgt %d\n", g_board->freq);
    for (int y_index = 0; y_index < g_board->height; y_index++) {
        for (int x_index = 0; x_index < g_board->width; x_index++) {
            dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", \
            TILE_CONTENT.posx, TILE_CONTENT.posy, TILE_CONTENT_R[FOOD], \
            TILE_CONTENT_R[LINEMATE], TILE_CONTENT_R[DERAUMERE], \
            TILE_CONTENT_R[SIBUR], TILE_CONTENT_R[MENDIANE], \
            TILE_CONTENT_R[PHIRAS], TILE_CONTENT_R[THYSTAME]);
        }
    }
    for (team_t *tmp = *team_container(); tmp; tmp = tmp->next) {
        dprintf(client->fd, "tna %s\n", tmp->team_name);
    }
    return SUCCESS;
}

int ia_send_first_batch(game_board_t *g_board, \
client_t *client, server_t *server)
{
    team_t *team = get_team_by_uuid(client->uuid);

    if (team == NULL) {
        printf("no team found\n");
        return ERROR;
    }
    if (!FD_ISSET(client->fd, &server->write_fd_set)) {
        printf("error on fd isset\n");
        return ERROR;
    }
    dprintf(client->fd, "%d\n", team->client_max);
    dprintf(client->fd, "%d %d\n", g_board->width, g_board->height);
    return SUCCESS;
}