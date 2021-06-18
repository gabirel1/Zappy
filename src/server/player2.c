/*
** EPITECH PROJECT, 2021
** player2.c
** File description:
** player2.c
*/

#include "server/server.h"

player_t *get_player_by_number(int player_id)
{
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->player_number == player_id)
            return tmp;
    }
    return NULL;
}

int get_number_of_players(void)
{
    int count = 0;

    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        count++;
    }

    return count;
}

int *get_player_numbers(int to_skip)
{
    int total = get_number_of_players();
    int index = 0;
    int *to_ret = malloc(sizeof(int) * ((total > 0) ? total : 1));

    memset(to_ret, -15, (((total > 0) ? total : 1) * sizeof(int)));
    for (player_t *tmp; tmp; tmp = tmp->next) {
        if (tmp->player_number == to_skip)
            continue;
        to_ret[index++] = tmp->player_number;
    }
    return to_ret;
}