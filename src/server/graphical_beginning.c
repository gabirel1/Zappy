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

int tell_graphical_ia_is_here(server_t *server, client_t *client_ia)
{
    player_t *player = NULL;
    char *team_name = NULL;
    bool found = false;

    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true) {
            found = true;
            player = get_player_by_uuid(client_ia->uuid);
            if (player == NULL)
                continue;
            if ((team_name = get_team_name_by_uuid(player->team_uuid)) == NULL)
                continue;
            if (FD_ISSET(tmp->fd, &server->write_fd_set)) {
                dprintf(tmp->fd, "pnw %d %d %d %d %d %s\n", \
                player->player_number, player->posx, player->posy, \
                player->orientation, player->level, team_name);
            }
        }
    }
    return (found == false) ? ERROR : SUCCESS;
}

int ia_send_first_batch(game_board_t *g_board, \
client_t *client, server_t *server)
{
    player_t *player = get_player_by_uuid(client->uuid);
    team_t *team = (player != NULL) ? get_team_by_uuid(player->team_uuid) : NULL;

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
    if (tell_graphical_ia_is_here(server, client) == ERROR) {
        printf("No graphical client found\n");
        return ERROR;
    }
    return SUCCESS;
}