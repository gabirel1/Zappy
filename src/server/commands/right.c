/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** right
*/

#include "server/server.h"

int right(game_board_t *game UNSD, player_t *player)
{
    switch (player->orientation) {
        case NORTH :
            player->orientation = EAST;
            break;
        case SOUTH :
            player->orientation = WEST;
            break;
        case EAST :
            player->orientation = SOUTH;
            break;
        case WEST :
            player->orientation = NORTH;
            break;
    }
    player->cooldown = 7;
    return SUCCESS;
}