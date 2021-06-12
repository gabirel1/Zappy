/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** game
*/

#include "server/server.h"

tile_t create_tile(int posx, int posy)
{
    return (tile_t) {.posy = posy, .posx = posx, .resources = { 0 }};
}

int *generate_resources(int width, int height)
{
    int *resources = my_malloc(sizeof(int) * (THYSTAME + 1));
    float densities[] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};

    for (int i = 0; i < THYSTAME + 1; i += 1)
        resources[i] = width * height * densities[i];
    return resources;
}

void update_resources(game_board_t *board, int *resources)
{
    for (int i = 0; i < THYSTAME; i += 1) {
        for (int j = 0; j < resources[i]; j += 1) {
            int x = rand() % board->width;
            int y = rand() % board->height;
            board->map[y][x].resources[i] += 1;
        }
    }
}

game_board_t *create_game_board(game_info_t *game_info)
{
    game_board_t *board = my_malloc(sizeof(game_board_t));
    int *resources = generate_resources(game_info->width, game_info->height);

    board->width = game_info->width;
    board->height = game_info->height;
    board->freq = game_info->freq;
    board->teams = *team_container();
    board->map = my_malloc(sizeof(tile_t *) * (board->height + 1));
    for (int i = 0; i < board->height; i += 1) {
        board->map[i] = my_malloc(sizeof(tile_t) * (board->width));
        board->map[i + 1] = NULL;
        for (int j = 0; j < board->width; j += 1)
            board->map[i][j] = create_tile(j, i);
    }
    update_resources(board, resources);
    return board;
}

int game_loop(struct timeval *start, game_board_t *game)
{
    struct timeval end;
    double secs = 0;
    int *ressources = generate_resources(game->width, game->height);

    gettimeofday(&end, NULL);
    secs = (double)(end.tv_usec - start->tv_usec) / 1000000 + \
    (double)(end.tv_sec - start->tv_sec);
    if (secs > 20 / game->freq) {
        update_resources(game, ressources);
        gettimeofday(start, NULL);
        return SUCCESS;
    }
    return SUCCESS;
}