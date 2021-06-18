/*
** EPITECH PROJECT, 2021
** f_look.c
** File description:
** f_look.c
*/

#include "server/server.h"

char *add_inventory(char *ret, char *ressources, int nb)
{
    for (int i = 0; i < nb; i += 1) {
        ret = my_strcat(ret, ressources);
        ret = my_strcat(ret, " ");
    }
    return ret;
}

char *look_tiles(tile_t *tiles, int length, char *ret, char **ressources)
{
    for (int i = 0; i < length; i += 1) {
        for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
            if (tmp->posx == tiles[i].posx && tmp->posy == tiles[i].posy) {
                ret = my_strcat(ret, "player ");
            }
        }
        for (int j = 0; j <= THYSTAME; j += 1) {
            if (tiles[i].resources[j] > 0)
                ret = add_inventory(ret, ressources[j], tiles[i].resources[j]);
        }
        if (i < length - 1)
            ret = my_strcat(ret, ",");
    }
    return ret;
}

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