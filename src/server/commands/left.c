/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** left
*/

#include "server/server.h"

int left(game_board_t *game UNSD, player_t *player)
{
    switch (player->orientation) {
        case NORTH :
            player->orientation = WEST;
            break;
        case SOUTH :
            player->orientation = EAST;
            break;
        case EAST :
            player->orientation = NORTH;
            break;
        case WEST :
            player->orientation = SOUTH;
            break;
    }
    player->cooldown = 7;
    return SUCCESS;
}