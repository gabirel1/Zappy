/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** look
*/

#include "server/server.h"

tile_t *look_south(game_board_t *game, player_t *player)
{
    tile_t *ret = my_malloc_m(sizeof(tile_t) * ((player->level + 1) * \
    (player->level + 1)));
    int posx = 0;
    int posy = 0;
    int index = 0;

    for (int i = 0; i < player->level + 1; i += 1) {
        for (int j = player->posx - i; j <= player->posx + i; j += 1) {
            posy = player->posy - i;
            while (posy < 0)
                posy += game->height;
            posy %= game->height;
            posx = j;
            while (posx < 0)
                posx += game->width;
            posx %= game->width;
            ret[index] = game->map[posy][posx];
        }
    }
    return ret;
}

tile_t *look_north(game_board_t *game, player_t *player)
{
    tile_t *ret = my_malloc_m(sizeof(tile_t) * ((player->level + 1) * \
    (player->level + 1)));
    int posx = 0;
    int posy = 0;
    int index = 0;

    for (int i = 0; i < player->level + 1; i += 1) {
        for (int j = player->posx + i; j >= player->posx - i; j -= 1) {
            posy = player->posy + i;
            while (posy < 0)
                posy += game->height;
            posy %= game->height;
            posx = j;
            while (posx < 0)
                posx += game->width;
            posx %= game->width;
            ret[index] = game->map[posy][posx];
            index += 1;
        }
    }
    return ret;
}

tile_t *look_east(game_board_t *game, player_t *player)
{
    tile_t *ret = my_malloc_m(sizeof(tile_t) * ((player->level + 1) * \
    (player->level + 1)));
    int posx = 0;
    int posy = 0;
    int index = 0;

    for (int i = 0; i < player->level + 1; i += 1) {
        for (int j = player->posy - i; j <= player->posy + i; j += 1) {
            posy = j;
            while (posy < 0)
                posy += game->height;
            posy %= game->height;
            posx = player->posx + i;
            while (posx < 0)
                posx += game->width;
            posx %= game->width;
            ret[index] = game->map[posy][posx];
            index += 1;
        }
    }
    return ret;
}

tile_t *look_west(game_board_t *game, player_t *player)
{
    tile_t *ret = my_malloc_m(sizeof(tile_t) * ((player->level + 1) * \
    (player->level + 1)));
    int posx = 0;
    int posy = 0;
    int index = 0;

    for (int i = 0; i < player->level + 1; i += 1) {
        for (int j = player->posy + i; j <= player->posy - i; j += 1) {
            posy = j;
            while (posy < 0)
                posy += game->height;
            posy %= game->height;
            posx = player->posx - i;
            while (posx < 0)
                posx += game->width;
            posx %= game->width;
            ret[index] = game->map[posy][posx];
            index += 1;
        }
    }
    return ret;
}

char *look(game_board_t *game, player_t *player)
{
    tile_t *tiles = NULL;
    int length = (player->level + 1) * (player->level + 1);
    char *ret = strdup("[ ");
    char **ressources = ressources_container();

    if (player->orientation == SOUTH)
        tiles = look_south(game, player);
    if (player->orientation == NORTH)
        tiles = look_north(game, player);
    if (player->orientation == EAST)
        tiles = look_east(game, player);
    if (player->orientation == WEST)
        tiles = look_west(game, player);
    ret = look_tiles(tiles, length, ret, ressources);
    if (ret[strlen(ret) - 1] != ' ')
        ret = my_strcat_m(ret, " ", true);
    ret = my_strcat_m(ret, "]", true);
    free(tiles);
    return ret;
}