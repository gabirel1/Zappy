/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** fork
*/

#include "server/server.h"

int fork_player(game_board_t *game UNSD, player_t *player)
{
    player_t *new_player = init_player(player->team_uuid, player->posx, player->posy);

    new_player->is_egg = true;
    new_player->orientation = player->orientation;
    new_player->cooldown = 600;
    player->cooldown = 42;
    add_player(new_player);
    return SUCCESS;
}