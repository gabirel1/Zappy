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
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->player_number == to_skip)
            continue;
        to_ret[index++] = tmp->player_number;
    }
    return to_ret;
}

player_t *get_free_egg_player(char *team_uuid)
{
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (strcmp(team_uuid, tmp->team_uuid) == 0 && tmp->is_egg == true && \
        tmp->is_egg_used == false) {
            tmp->is_egg_used = true;
            return tmp;
        }
    }
    return NULL;
}

player_t *get_free_player(char *team_uuid)
{
    bool to_return = false;

    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        to_return = true;
        for (client_t *c_tmp = *client_container(); c_tmp; c_tmp = c_tmp->next) {
            if (strcmp(tmp->team_uuid, team_uuid) != 0 || \
            strcmp(c_tmp->uuid, tmp->uuid) == 0)
                to_return = false;
        }
        if (to_return == true)
            return tmp;
    }
    return NULL;
}