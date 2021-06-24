/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** set_obj
*/

#include "server/server.h"

void set(player_t *player, server_t *server UNSD, \
game_board_t *game UNSD)
{
    char **ressources = ressources_container();
    char *object = player->params[0];
    bool ok = false;
    int resource_id = get_resources_number_by_name(object);

    for (int i = 0; ressources[i]; i += 1) {
        if (strcmp(object, ressources[i]) == 0) {
            if (player->inventory[i] == 0)
                break;
            game->map[player->posy][player->posx].resources[i] += 1;
            player->inventory[i] -= 1;
            ok = true;
            break;
        }
    }
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true)
            pdr(tmp->fd, player->player_number, resource_id, server);
        if (strcmp(tmp->uuid, player->uuid) == 0)
            dprintf(tmp->fd, (ok == true) ? "ok\n" : "ko\n");
    }
    free_tab(player->params);
    player->params = NULL;
}

int f_set(char *request[], server_t *server, game_board_t *g_board UNSD, \
client_t *client)
{
    player_t *player = NULL;
    int resource_id = 0;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || request[0] == NULL) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    if ((resource_id = get_resources_number_by_name(request[0])) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    player->cooldown = 7;
    player->params = copy_tab(player->params, request);
    player->on_cd = &set;
    return SUCCESS;
}