/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** inventory
*/

#include "server/server.h"

char *inventory(game_board_t *game UNSD, player_t *player)
{
    char *ret = my_strdup("[");
    char **ressources = ressources_container();

    for (int i = 0; i <= THYSTAME; i += 1) {
        my_strcat(ret, ressources[i]);
        my_strcat(ret, my_itoa(player->inventory[i]));
        if (i != THYSTAME)
            my_strcat(ret, ",");
    }
    my_strcat(ret, "]");
    player->cooldown = 1;
    return ret;
}