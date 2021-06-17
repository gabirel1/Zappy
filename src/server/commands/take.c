/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** take
*/

#include "server/server.h"

int take(game_board_t *game, player_t *player, char *object)
{
    char **ressources = ressources_container();
    bool passed = false;

    for (int i = 0; ressources[i]; i += 1) {
        if (strcmp(object, ressources[i]) == 0) {
            passed = true;
            if (game->map[player->posy][player->posx].resources[i] == 0)
                return ERROR;
            game->map[player->posy][player->posx].resources[i] -= 1;
            player->inventory[i] += 1;
            break;
        }
    }
    if (passed == false)
        return ERROR;
    player->cooldown = 7;
    return SUCCESS;
}

int f_take(char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;
    int resource_id = 0;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0 || \
    request[0] == NULL || take(g_board, player, request[0]) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    if ((resource_id = get_resources_number_by_name(request[0])) == ERROR)
        return ERROR;
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true) {
            pgt(tmp->fd, player->player_number, resource_id, server);
        }
    }
    dprintf(client->fd, "ok\n");
    return SUCCESS;
}