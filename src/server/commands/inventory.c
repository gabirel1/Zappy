/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** inventory
*/

#include "server/server.h"

char *inventory(game_board_t *game UNSD, player_t *player)
{
    char *ret = my_strdup("[ ");
    char **ressources = ressources_container();

    for (int i = 0; i <= THYSTAME; i += 1) {
        ret = my_strcat(ret, ressources[i]);
        ret = my_strcat(ret, " ");
        ret = my_strcat(ret, my_itoa(player->inventory[i]));
        if (i != THYSTAME)
            ret = my_strcat(ret, ", ");
    }
    ret = my_strcat(ret, " ]");
    player->cooldown = 1;
    return ret;
}

int f_inventory(UNSD char *request[], server_t *server, game_board_t *g_board, \
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
    response = inventory(g_board, player);
    dprintf(client->fd, "%s\n", response);
    return SUCCESS;
}