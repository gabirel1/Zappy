/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** set_obj
*/

#include "server/server.h"

int set(game_board_t *game, player_t *player, char *object)
{
    char **ressources = ressources_container();
    bool passed = false;

    for (int i = 0; ressources[i]; i += 1) {
        if (strcmp(object, ressources[i]) == 0) {
            passed = true;
            if (player->inventory[i] == 0)
                return ERROR;
            game->map[player->posy][player->posx].resources[i] += 1;
            player->inventory[i] -= 1;
            break;
        }
    }
    if (passed == false)
        return ERROR;
    player->cooldown = 7;
    return SUCCESS;
}

int f_set(char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0 || \
    request[0] == NULL || set(g_board, player, request[0]) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    dprintf(client->fd, "ok\n");
    return SUCCESS;
}