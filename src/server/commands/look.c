/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** look
*/

#include "server/server.h"

tile_t *look_north(game_board_t *game, player_t *player)
{
    tile_t *ret = my_malloc(sizeof(tile_t) * ((player->level + 1) ^ 2));
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

tile_t *look_south(game_board_t *game, player_t *player)
{
    tile_t *ret = my_malloc(sizeof(tile_t) * ((player->level + 1) ^ 2));
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
    tile_t *ret = my_malloc(sizeof(tile_t) * ((player->level + 1) ^ 2));
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
    tile_t *ret = my_malloc(sizeof(tile_t) * ((player->level + 1) ^ 2));
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
    int length = (player->level + 1) ^ 2;
    char *ret = my_strdup("[");
    char **ressources = ressources_container();

    if (player->orientation == NORTH)
        tiles = look_north(game, player);
    if (player->orientation == SOUTH)
        tiles = look_south(game, player);
    if (player->orientation == EAST)
        tiles = look_east(game, player);
    if (player->orientation == WEST)
        tiles = look_west(game, player);
    for (int i = 0; i < length; i += 1) {
        for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
            if (tmp->posx == tiles[i].posx && tmp->posy == tiles[i].posy) {
                my_strcat(ret, "player ");
            }
        }
        for (int j = 0; j <= THYSTAME; j += 1) {
            if (tiles[i].resources[j] > 0) {
                my_strcat(ret, ressources[j]);
                my_strcat(ret, " ");
            }
        }
        my_strcat(ret, ",");
    }
    my_strcat(ret, "]");
    player->cooldown = 7;
    return ret;
}