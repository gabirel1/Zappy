/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** game
*/

#include "server/server.h"

tile_t create_tile(int posx, int posy)
{
    return (tile_t) {.posy = posy, .posx = posx, .ressources = { 0 }};
}

int *generate_ressources(int width, int height)
{
    int *ressources = my_malloc(sizeof(int) * (THYSTAME + 1));
    float densities[] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};

    for (int i = 0; i < THYSTAME + 1; i += 1)
        ressources[i] = width * height * densities[i];
    return ressources;
}

game_board_t *create_game_board(game_info_t *game_info)
{
    game_board_t *board = my_malloc(sizeof(game_board_t));
    int *ressources = generate_ressources(game_info->width, game_info->height);

    board->width = game_info->width;
    board->height = game_info->height;
    board->freq = game_info->freq;
    board->team_names = game_info->team_names;
    board->map = my_malloc(sizeof(tile_t *) * (board->height + 1));
    for (int i = 0; i < board->height; i += 1) {
        board->map[i] = my_malloc(sizeof(tile_t) * (board->width));
        board->map[i + 1] = NULL;
        for (int j = 0; j < board->width; j += 1)
            board->map[i][j] = create_tile(j, i);
    }
    for (int i = 0; i < THYSTAME; i += 1) {
        for (int j = 0; j < ressources[i]; j += 1) {
            int x = rand() % board->width;
            int y = rand() % board->height;
            board->map[y][x].ressources[i] += 1;
        }
    }
    return board;
}