/*
** EPITECH PROJECT, 2021
** tna.c
** File description:
** tna.c
*/

#include "server/server.h"

int tna(UNSD char *request[], server_t *server, UNSD game_board_t *g_board, \
client_t *client)
{
    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    for (team_t *tmp = *team_container(); tmp; tmp = tmp->next) {
        dprintf(client->fd, "tna %s\n", tmp->team_name);
    }
    return SUCCESS;
}