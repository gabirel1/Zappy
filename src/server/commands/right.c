/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** right
*/

#include "server/server.h"

int right(game_board_t *game UNSD, player_t *player)
{
    switch (player->orientation) {
        case NORTH :
            player->orientation = EAST;
            break;
        case SOUTH :
            player->orientation = WEST;
            break;
        case EAST :
            player->orientation = SOUTH;
            break;
        case WEST :
            player->orientation = NORTH;
            break;
    }
    player->cooldown = 7;
    return SUCCESS;
}

int move_right(UNSD char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0 || \
    right(g_board, player) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true) {
            ppo_second(tmp->fd, player, server);
        }
    }
    dprintf(client->fd, "ok\n");
    return SUCCESS;
}