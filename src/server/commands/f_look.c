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
        ret = my_strcat_m(ret, ressources, true);
        ret = my_strcat_m(ret, " ", true);
    }
    return ret;
}

char *look_tiles(tile_t *tiles, int length, char *ret, char **ressources)
{
    for (int i = 0; i < length; i += 1) {
        for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
            if (tmp->posx == tiles[i].posx && tmp->posy == tiles[i].posy) {
                ret = my_strcat_m(ret, "player ", true);
            }
        }
        for (int j = 0; j <= THYSTAME; j += 1) {
            if (tiles[i].resources[j] > 0)
                ret = add_inventory(ret, ressources[j], tiles[i].resources[j]);
        }
        if (i < length - 1)
            ret = my_strcat_m(ret, ",", true);
    }
    return ret;
}

void send_look(player_t *player, server_t *server UNSD, \
game_board_t *g_board UNSD)
{
    char *response = look(g_board, player);

    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, player->uuid) == 0)
            (FD_TMP_IS_SET) ? dprintf(tmp->fd, "%s\n", response) : 0;
    }
    free(response);
}

int f_look(UNSD char *request[], server_t *server, game_board_t *g_board UNSD, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    player->on_cd = &send_look;
    player->cooldown = 7;
    return SUCCESS;
}