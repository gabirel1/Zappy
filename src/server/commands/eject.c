/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** eject
*/

#include "server/server.h"

void move_player(game_board_t *game, player_t *to_move)
{
    if (to_move->orientation == SOUTH) {
        to_move->posy -= 1;
        if (to_move->posy < 0)
            to_move->posy += game->height;
    }
    if (to_move->orientation == NORTH) {
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

void eject(player_t *player, server_t *server UNSD, game_board_t *game UNSD)
{
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->posx == player->posx && tmp->posy == player->posy \
        && tmp != player && player->is_egg == false)
            move_player(game, tmp);
    }
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, player->uuid) == 0)
            (FD_TMP_IS_SET) ? dprintf(tmp->fd, "ok\n") : 0;
    }
}

int f_eject(UNSD char *request[], server_t *server, game_board_t \
*g_board UNSD, client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    player->on_cd = &eject;
    player->cooldown = 7;
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true) {
            pex(tmp->fd, player->player_number, server);
        }
    }
    return SUCCESS;
}