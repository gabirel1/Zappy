/*
** EPITECH PROJECT, 2021
** f_look.c
** File description:
** f_look.c
*/

#include "server/server.h"

int f_look(UNSD char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;
    char *response = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    response = look(g_board, player);
    dprintf(client->fd, "%s\n", response);
    return SUCCESS;
}