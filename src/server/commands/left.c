/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** left
*/

#include "server/server.h"

int left(game_board_t *game UNSD, player_t *player)
{
    switch (player->orientation) {
        case NORTH :
            player->orientation = WEST;
            break;
        case SOUTH :
            player->orientation = EAST;
            break;
        case EAST :
            player->orientation = NORTH;
            break;
        case WEST :
            player->orientation = SOUTH;
            break;
    }
    player->cooldown = 7;
    return SUCCESS;
}

int move_left(UNSD char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0 || \
    left(g_board, player) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    dprintf(client->fd, "ok\n");
    return SUCCESS;
}