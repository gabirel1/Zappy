/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** game_player
*/

#include "server/server.h"

void player_death_next(int player_number, server_t *server)
{
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (tmp->is_graphic == true) {
            pdi(tmp->fd, player_number, server);
        }
    }
}

void player_death(player_t *player, server_t *server)
{
    team_t *team = NULL;
    int player_number = 0;

    if (player->inventory[FOOD] == 0)
        player->hp -= 1;
    else
        player->inventory[FOOD] -= 1;
    if (player->hp != 0)
        return;
    player_number = player->player_number;
    team = get_team_by_uuid(player->team_uuid);
    (team != NULL) ? team->client_max += 1 : 0;
    player_death_next(player_number, server);
    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, player->uuid) == 0) {
            dprintf(tmp->fd, "dead\n");
            // delete_player(player);
            // delete_client(tmp);
        }
    }
}

void update_player_cooldown(player_t *tmp, game_board_t *board, \
struct timeval end, server_t *server)
{
    double secs = 0;

    if (tmp->cooldown == 0) {
        gettimeofday(&(tmp->clock), NULL);
        (tmp->on_cd != NULL) ? tmp->on_cd(tmp) : 0;
    }
    gettimeofday(&end, NULL);
    secs = (double)(end.tv_usec - tmp->clock.tv_usec) / 1000000 + \
    (double)(end.tv_sec - tmp->clock.tv_sec);
    if (secs > 1 / board->freq) {
        tmp->cooldown -= (tmp->cooldown > 0) ? 1 : 0;
        gettimeofday(&(tmp->clock), NULL);
    }
    secs = (double)(end.tv_usec - tmp->life_clock.tv_usec) / 1000000 + \
    (double)(end.tv_sec - tmp->life_clock.tv_sec);
    if (secs > 126 / board->freq && tmp->is_egg == false) {
        player_death(tmp, server);
        gettimeofday(&(tmp->life_clock), NULL);
    }
}

void update_cooldown(game_board_t *board, server_t *server)
{
    struct timeval end;

    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next)
        update_player_cooldown(tmp, board, end, server);
}