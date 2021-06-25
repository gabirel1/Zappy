/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** left
*/

#include "server/server.h"

void left(player_t *player, server_t *server, \
game_board_t *g_board UNSD)
{
    switch (player->orientation) {
        case NORTH :
            player->orientation = WEST;
            break;
        case SOUTH :
            player->orientation = EAST;
            break;
        case EAST :
            player->orientation = NORTH;
            break;
        case WEST :
            player->orientation = SOUTH;
            break;
    }
}

void send_left(player_t *player, server_t *server, \
game_board_t *g_board UNSD)
{
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, player->uuid) == 0)
            (FD_TMP_IS_SET) ? dprintf(tmp->fd, "ok\n") : 0;
    }
}

int move_left(UNSD char *request[], server_t *server, \
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
    player->on_cd = &send_left;
    player->cooldown = 7;
    left(player, server, g_board);
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true)
            ppo_second(tmp->fd, player, server);
    }
    return SUCCESS;
}