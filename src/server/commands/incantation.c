/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** incantation
*/

#include "server/server.h"

static const int requirements[7][7] = {
    {1, 2, 2, 4, 4, 6, 6},
    {1, 1, 2, 1, 1, 1, 2},
    {0, 1, 0, 1, 2, 2, 2},
    {0, 1, 1, 2, 1, 3, 2},
    {0, 0, 0, 0, 3, 0, 2},
    {0, 0, 2, 1, 0, 1, 2},
    {0, 0, 0, 0, 0, 0, 1},
};

int get_players_tile(player_t *player)
{
    int number = 0;

    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->posx == player->posx && tmp->posy == player->posy && \
        tmp->level == player->level && \
        tmp->is_egg == false)
            number += 1;
    }
    return number;
}

void level_up(player_t *player, server_t *server, game_board_t *g UNSD)
{
    if (player->level < 8)
        player->level += 1;
    player->on_cd = NULL;
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true) {
            pie(tmp->fd, (int [2]) {player->posx, player->posy}, \
            player->level, server);
        }
    }
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true) {
            pic(tmp->fd, player->player_number, \
            get_player_numbers(player->player_number), server);
        }
        if (strcmp(tmp->uuid, player->uuid) == 0)
            dprintf(tmp->fd, "%d\n", player->level);
    }
}

int incantation(game_board_t *game UNSD, player_t *player)
{
    for (int i = 0; i < 7; i += 1) {
        if (i == 0 && get_players_tile(player) < \
        requirements[i][player->level - 1])
            return ERROR;
        if (i != 0 && game->map[player->posy][player->posx].resources[i] \
        != requirements[i][player->level - 1])
            return ERROR;
    }
    for (int i = 0; i < 7; i += 1)
        if (i != 0)
            game->map[player->posy][player->posx].resources[i] = 0;
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->posx == player->posx && tmp->posy == player->posy && \
        tmp->level == player->level && tmp->is_egg == false) {
            tmp->cooldown = 300;
            tmp->on_cd = &level_up;
        }
    }
    return SUCCESS;
}

int f_incantation(UNSD char *req[], server_t *server, game_board_t *g_board, \
client_t *client)
{
    player_t *player = NULL;

    if (!FD_ISSET(client->fd, &server->write_fd_set))
        return ERROR;
    player = get_player_by_uuid(client->uuid);
    if (player == NULL || player->cooldown != 0 || \
    incantation(g_board, player) == ERROR) {
        dprintf(client->fd, "ko\n");
        return ERROR;
    }
    return SUCCESS;
}