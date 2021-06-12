/*
** EPITECH PROJECT, 2021
** ppo.c
** File description:
** ppo.c
*/

#include "server/server.h"

int ppo(char *request[], server_t *server, UNSD game_board_t *g_board, \
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
    dprintf(client->fd, "ppo %d %d %d %d\n", player->player_number, \
    player->posx, player->posy, player->orientation);
    return SUCCESS;
}