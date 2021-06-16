/*
** EPITECH PROJECT, 2021
** connect_nbr.c
** File description:
** connect_nbr.c
*/

#include "server/server.h"

int connect_nbr(UNSD game_board_t *game, player_t *player)
{
    team_t *team = get_team_by_uuid(player->team_uuid);

    if (team == NULL) {
        printf("team not found\n");
        return ERROR;
    }
    return team->client_max;
}

int f_connect_nbr(UNSD char *request[], server_t *server, \
game_board_t *g_board, client_t *client)
{
    player_t *player = NULL;
    int response = 0;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0) {
        return ERROR;
    }
    response = connect_nbr(g_board, player);
    if (response == ERROR)
        return ERROR;
    dprintf(client->fd, "%d\n", response);
    return SUCCESS;
}