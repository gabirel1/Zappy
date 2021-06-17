/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** eject
*/

#include "server/server.h"

void move_player(game_board_t *game, player_t *to_move)
{
    if (to_move->orientation == NORTH) {
        to_move->posy -= 1;
        if (to_move->posy < 0)
            to_move->posy += game->height;
    }
    if (to_move->orientation == SOUTH) {
        to_move->posy += 1;
        to_move->posy %= game->height;
    }
    if (to_move->orientation == EAST) {
        to_move->posx += 1;
        to_move->posx %= game->width;
    }
    if (to_move->orientation == WEST) {
        to_move->posx -= 1;
        if (to_move->posx < 0)
            to_move->posx += game->width;
    }
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next)
        CALL_MOV
}

int eject(game_board_t *game, player_t *player)
{
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->posx == player->posx && tmp->posy == player->posy \
        && tmp != player && player->is_egg == false)
            move_player(game, tmp);
    }
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
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true) {
            pex(tmp->fd, player->player_number, server);
        }
    }
    dprintf(client->fd, "ok\n");
    return SUCCESS;
}