/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** forward
*/

#include "server/server.h"

int forward_next(game_board_t *game, player_t *player)
{
    switch (player->orientation) {
        case EAST :
            if (player->posx < game->width - 1)
                player->posx += 1;
            else
                return ERROR;
            break;
        case WEST :
            if (player->posx > 0)
                player->posx -= 1;
            else
                return ERROR;
            break;
        default :
            return ERROR;
    }
    return SUCCESS;
}

int forward(game_board_t *game, player_t *player)
{
    switch (player->orientation) {
        case NORTH :
            if (player->posy > 0)
                player->posy -= 1;
            else
                return ERROR;
            break;
        case SOUTH :
            if (player->posy < game->height - 1)
                player->posy += 1;
            else
                return ERROR;
            break;
        default :
            if (forward_next(game, player) == ERROR)
                return ERROR;
    }
    player->cooldown = 7;
    return SUCCESS;
}