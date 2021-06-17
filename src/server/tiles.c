/*
** EPITECH PROJECT, 2021
** tiles.c
** File description:
** tiles.c
*/

#include "server/server.h"

tile_t *get_tile_by_pos(tile_t **tiles, int pos_x, int pos_y, \
game_board_t *game_board)
{
    if (pos_x < 0 || pos_y < 0 || pos_x > game_board->width || \
    pos_y > game_board->height) {
        return NULL;
    }
    for (int y = 0; y < game_board->height; y++) {
        for (int x = 0; x < game_board->width; x++) {
            if (tiles[y][x].posx == pos_x && tiles[y][x].posy == pos_y) {
                printf("y == %d x == %d posy == %d posx == %d\n", y, x, \
                tiles[y][x].posy, tiles[y][x].posx);
                return &tiles[y][x];
            }
        }
    }
    return NULL;
}