/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** broadcast
*/

#include "server/server.h"

int f_broadcast_text(char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set) || request[0] == NULL)
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_ia == true)
            dprintf(tmp->fd, "message %d, %s\n", \
            player->posy * g_board->width + player->posx, request[0]);
        else if (tmp->is_graphic == true)
            pbc(tmp->fd, player->player_number, request[0], server);
    }
    player->cooldown = 7;
    return SUCCESS;
}