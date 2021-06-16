/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** eject
*/

#include "server/server.h"

player_t *is_ennemy(player_t *player)
{
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->posx == player->posx && tmp->posy == player->posy \
        && strcmp(tmp->team_uuid, player->team_uuid) != 0)
            return tmp;
    }
    return NULL;
}

void move_player(game_board_t *game, player_t *player, player_t *to_move)
{
    if (player->orientation == NORTH) {
        to_move->posy -= 1;
        if (to_move->posy < 0)
            to_move->posy += game->height;
    }
    if (player->orientation == SOUTH) {
        to_move->posy += 1;
        to_move->posy %= game->height;
    }
    if (player->orientation == EAST) {
        to_move->posx += 1;
        to_move->posx %= game->width;
    }
    if (player->orientation == WEST) {
        to_move->posx -= 1;
        if (to_move->posx < 0)
            to_move->posx += game->width;
    }
}

int eject(game_board_t *game, player_t *player)
{
    player_t *to_move = is_ennemy(player);

    if (to_move == NULL)
        return ERROR;
    move_player(game, player, to_move);
    player->cooldown = 7;
    return SUCCESS;
}

int f_eject(UNSD char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0 || \
    eject(g_board, player) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    dprintf(client->fd, "ok\n");
    return SUCCESS;
}