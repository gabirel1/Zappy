/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** player3
*/

#include "server/server.h"

bool is_player_on_tile(int x, int y)
{
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->posx == x && tmp->posy == y)
            return true;
    }
    return false;
}

void del_user_on_close(client_t *client, server_t *server)
{
    player_t *player = NULL;
    int useless = 0;

    if (client == NULL)
        return;
    if ((player = get_player_by_uuid(client->uuid)) == NULL)
        return;
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true)
            pdi(tmp->fd, player->player_number, server);
    }
    stop_client(client->fd, server, &useless);
    delete_client_from_list(client);
    delete_player(player);
}