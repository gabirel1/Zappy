/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** game_player
*/

#include "server/server.h"

void update_cooldown(game_board_t *board)
{
    static struct timeval start = { 0 };
    static bool is_first = true;
    double secs = 0;
    struct timeval end;

    if (is_first) {
        gettimeofday(&start, NULL);
        is_first = false;
    }
    gettimeofday(&end, NULL);
    secs = (double)(end.tv_usec - start.tv_usec) / 1000000 + \
    (double)(end.tv_sec - start.tv_sec);
    if (secs > 1 / board->freq) {
        for (player_t *tmp = *player_container(); tmp; tmp = tmp->next)
            tmp->cooldown -= (tmp->cooldown > 0) ? 1 : 0;
        gettimeofday(&start, NULL);
    }
}