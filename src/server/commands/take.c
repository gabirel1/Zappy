/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** take
*/

#include "server/server.h"

int take(game_board_t *game, player_t *player, char *object)
{
    char **ressources = ressources_container();
    bool passed = false;

    for (int i = 0; ressources[i]; i += 1) {
        if (strcmp(object, ressources[i]) == 0) {
            passed = true;
            if (game->map[player->posy][player->posx].resources[i] == 0)
                return ERROR;
            game->map[player->posy][player->posx].resources[i] -= 1;
            player->inventory[i] += 1;
            break;
        }
    }
    if (passed == false)
        return ERROR;
    player->cooldown = 7;
    return SUCCESS;
}