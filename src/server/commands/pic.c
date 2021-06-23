/*
** EPITECH PROJECT, 2021
** pic.c
** File description:
** pic.c
*/

#include "server/server.h"

int pic(int fd, int first_player, int *player_numbers, server_t *server)
{
    player_t *player = NULL;

    if (!FD_ISSET(fd, &server->write_fd_set)) {
        free(player_numbers);
        return ERROR;
    }
    player = get_player_by_number(first_player);
    if (player == NULL) {
        printf("player not found\n");
        free(player_numbers);
        return ERROR;
    }
    dprintf(fd, "pic %d %d %d %d", player->posx, player->posy, player->level, \
    first_player);
    for (int index = 0; index < get_number_of_players(); index++) {
        dprintf(fd, " %d", player_numbers[index]);
    }
    dprintf(fd, "\n");
    free(player_numbers);
    return SUCCESS;
}