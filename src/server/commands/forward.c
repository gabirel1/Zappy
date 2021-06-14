/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** forward
*/

#include "server/server.h"

int forward_next(game_board_t *game, player_t *player)
{
    switch (player->orientation) {
        case EAST :
            if (player->posx < game->width - 1)
                player->posx += 1;
            else
                player->posx = 0;
            break;
        case WEST :
            if (player->posx > 0)
                player->posx -= 1;
            else
                player->posx = game->width - 1;
            break;
        default :
            return ERROR;
    }
    return SUCCESS;
}

int forward(game_board_t *game, player_t *player)
{
    switch (player->orientation) {
        case NORTH :
            if (player->posy > 0)
                player->posy -= 1;
            else
                player->posy = game->height - 1;
            break;
        case SOUTH :
            if (player->posy < game->height - 1)
                player->posy += 1;
            else
                player->posy = 0;
            break;
        default :
            if (forward_next(game, player) == ERROR)
                return ERROR;
    }
    player->cooldown = 7;
    return SUCCESS;
}

int move_forward(char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0 || \
    forward(g_board, player) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    dprintf(client->fd, "ok\n");
    return SUCCESS;
}