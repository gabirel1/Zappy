/*
** EPITECH PROJECT, 2021
** game2.c
** File description:
** game2.c
*/

#include "server/server.h"

void fill_game_board_info(game_board_t *board, game_info_t *game_info)
{
    board->width = game_info->width;
    board->height = game_info->height;
    board->freq = game_info->freq;
    board->teams = *team_container();
}