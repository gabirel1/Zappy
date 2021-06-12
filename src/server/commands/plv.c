/*
** EPITECH PROJECT, 2021
** plv.c
** File description:
** plv.c
*/

#include "server/server.h"

int plv(char *request[], server_t *server, UNSD game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set) || request[0] == NULL)
        return ERROR;
    player = get_player_by_number(atoi(request[0]));
    if (player == NULL) {
        printf("player not found\n");
        return ERROR;
    }
    dprintf(client->fd, "plv %d %d\n", player->player_number, \
    player->level);
    return SUCCESS;
}