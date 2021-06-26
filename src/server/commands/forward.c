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

void send_moved(player_t *player, server_t *server UNSD, game_board_t *game UNSD)
{
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, player->uuid) == 0)
            (FD_TMP_IS_SET) ? dprintf(tmp->fd, "ok\n") : 0;
    }
}

void forward(player_t *player, server_t *server, game_board_t *game)
{
    switch (player->orientation) {
        case SOUTH :
            if (player->posy > 0)
                player->posy -= 1;
            else
                player->posy = game->height - 1;
            break;
        case NORTH :
            if (player->posy < game->height - 1)
                player->posy += 1;
            else
                player->posy = 0;
            break;
        default :
            if (forward_next(game, player) == ERROR)
                return;
    }
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true)
            ppo_second(tmp->fd, player, server);
    }
}

int move_forward(UNSD char *request[], server_t *server, \
game_board_t *g_board UNSD, client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL) {
        (FD_IS_SET) ? dprintf(client->fd, "ko\n") : 0;
        return ERROR;
    }
    player->on_cd = &send_moved;
    player->cooldown = 7;
    forward(player, server, g_board);
    return SUCCESS;
}