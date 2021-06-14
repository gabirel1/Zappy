/*
** EPITECH PROJECT, 2021
** enw.c
** File description:
** enw.c
*/

#include "server/server.h"

int enw(int fd, int egg_number, int player_number, server_t *server)
{
    player_t *player = NULL;

    if (!FD_ISSET(fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_number(player_number);
    if (player == NULL) {
        printf("player not found\n");
        return ERROR;
    }
    dprintf(fd, "enw %d %d %d %d\n", egg_number, player_number, \
    player->posx, player->posy);

    return SUCCESS;
}