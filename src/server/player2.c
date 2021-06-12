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