/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** game_player
*/

#include "server/server.h"

void update_cooldown(game_board_t *board)
{
    double secs = 0;
    struct timeval end;

    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->cooldown == 0) {
            gettimeofday(&(tmp->clock), NULL);
        }
        gettimeofday(&end, NULL);
        secs = (double)(end.tv_usec - tmp->clock.tv_usec) / 1000000 + \
        (double)(end.tv_sec - tmp->clock.tv_sec);
        if (secs > 1 / board->freq) {
            tmp->cooldown -= 1;
            gettimeofday(&(tmp->clock), NULL);
        }
        secs = (double)(end.tv_usec - tmp->life_clock.tv_usec) / 1000000 + \
        (double)(end.tv_sec - tmp->life_clock.tv_sec);
        if (secs > 126 / board->freq) {
            tmp->hp -= 1;
            gettimeofday(&(tmp->life_clock), NULL);
        }
    }
}