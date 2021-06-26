/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** inventory
*/

#include "server/server.h"

char *inventory(game_board_t *game UNSD, player_t *player)
{
    char *ret = strdup("[ ");
    char **ressources = ressources_container();

    for (int i = 0; i <= THYSTAME; i += 1) {
        ret = my_strcat_m(ret, ressources[i], true);
        ret = my_strcat_m(ret, " ", true);
        ret = my_strcat_m(ret, my_itoa(player->inventory[i]), true);
        if (i != THYSTAME)
            ret = my_strcat_m(ret, ", ", true);
    }
    ret = my_strcat_m(ret, " ]", true);
    player->cooldown = 1;
    return ret;
}

void send_inventory(player_t *player, server_t *server UNSD, \
game_board_t *g_board UNSD)
{
    char *response = inventory(g_board, player);

    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, player->uuid) == 0)
            (FD_TMP_IS_SET) ? dprintf(tmp->fd, "%s\n", response) : 0;
    }
    free(response);
}

int f_inventory(UNSD char *request[], server_t *server, \
game_board_t *g_board UNSD, client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    player->on_cd = &send_inventory;
    player->cooldown = 1;
    return SUCCESS;
}