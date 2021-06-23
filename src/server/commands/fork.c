/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** fork
*/

#include "server/server.h"

void hatch(player_t *player, server_t *server, game_board_t *g UNSD)
{
    player->is_egg = false;
    player->on_cd = NULL;
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true)
            edi(tmp->fd, player->player_number, server);
        if (strcmp(tmp->uuid, player->uuid) == 0)
            dprintf(tmp->fd, "ok\n");
    }
}

void send_ok(player_t *player, server_t *server UNSD, \
game_board_t *g_board UNSD)
{
    player_t *new_player = init_player(player->team_uuid, \
    player->posx, player->posy);

    new_player->is_egg = true;
    new_player->orientation = player->orientation;
    new_player->cooldown = 600;
    new_player->on_cd = &hatch;
    add_player(new_player);
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, player->uuid) == 0)
            dprintf(tmp->fd, "ok\n");
        if (tmp->is_graphic == true) {
            pfk(tmp->fd, player->player_number, server);
            enw(tmp->fd, new_player->player_number, \
            player->player_number, server);
            eht(tmp->fd, new_player->player_number, \
            server);
        }
    }
}

int fork_player(game_board_t *game UNSD, player_t *player, \
server_t *server UNSD)
{
    player->cooldown = 42;
    player->on_cd = &send_ok;
    return SUCCESS;
}

int f_fork(UNSD char *request[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0 || \
    fork_player(g_board, player, server) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    return SUCCESS;
}