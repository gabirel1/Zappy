/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** player3
*/

#include "server/server.h"

bool is_player_on_tile(int x, int y)
{
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (tmp->posx == x && tmp->posy == y)
            return true;
    }
    return false;
}