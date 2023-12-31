/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** right
*/

#include "server/server.h"

void right(player_t *player, UNSD server_t *server, \
game_board_t *g_board UNSD)
{
    switch (player->orientation) {
        case NORTH :
            player->orientation = EAST;
            break;
        case SOUTH :
            player->orientation = WEST;
            break;
        case EAST :
            player->orientation = SOUTH;
            break;
        case WEST :
            player->orientation = NORTH;
            break;
    }
}

void send_right(player_t *player, server_t *server, \
UNSD game_board_t *g_board)
{
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, player->uuid) == 0)
            (FD_TMP_IS_SET) ? dprintf(tmp->fd, "ok\n") : 0;
    }
}

int move_right(UNSD char *request[], server_t *server, game_board_t \
*g_board UNSD, client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    player->on_cd = &send_right;
    player->cooldown = 7;
    right(player, server, g_board);
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true)
            ppo_second(tmp->fd, player, server);
    }
    return SUCCESS;
}