/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** broadcast
*/

#include "server/server.h"

void broadcast_message(player_t *player, server_t *server, \
game_board_t *g_board UNSD)
{
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_ia == true)
            dprintf(tmp->fd, "message %d, %s\n", \
            player->posy * g_board->width + player->posx, player->params[0]);
        else if (tmp->is_graphic == true)
            pbc(tmp->fd, player->player_number, player->params[0], server);
    }
}

int f_broadcast_text(char *request[], server_t *server, game_board_t *g_board UNSD, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set) || request[0] == NULL)
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    player->params = request;
    player->on_cd = &broadcast_message;
    player->cooldown = 7;
    return SUCCESS;
}