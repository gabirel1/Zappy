/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** player
*/

#include "server/server.h"

player_t **player_container(void)
{
    static player_t *head = NULL;

    return &head;
}

player_t *init_player(char *team_uuid, int posx, int posy)
{
    player_t *player = my_malloc(sizeof(player_t));
    uuid_t new_uuid;
    static int nb = 1;

    uuid_generate(new_uuid);
    memset(player, 0, sizeof(player_t));
    player->posx = posx;
    player->posy = posy;
    player->player_number = nb++;
    player->level = 1;
    player->is_egg = false;
    player->is_egg_used = false;
    strcpy(player->team_uuid, team_uuid);
    player->orientation = (rand() % 4) + 1;
    player->hp = 10;
    player->inventory[FOOD] = 10;
    gettimeofday(&(player->life_clock), NULL);
    gettimeofday(&(player->clock), NULL);
    uuid_unparse_lower(new_uuid, player->uuid);
    return player;
}

bool add_player(player_t *next)
{
    player_t **front_ptr = player_container();
    player_t *tmp = *front_ptr;

    if (!next)
        return (false);
    next->next = NULL;
    if (front_ptr == NULL || *front_ptr == NULL) {
        *front_ptr = next;
        return (true);
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = next;
    return (true);
}

bool delete_player(player_t *player)
{
    player_t **front_ptr = player_container();
    player_t *tmp = *front_ptr;
    player_t *second_tmp = *front_ptr;

    if (!*front_ptr)
        return (false);
    if (player == tmp) {
        *front_ptr = tmp->next;
        return (true);
    }
    while (player != tmp->next)
        tmp = tmp->next;
    second_tmp = tmp->next->next;
    tmp->next = second_tmp;
    return (true);
}

player_t *get_player_by_uuid(char *uuid)
{
    for (player_t *tmp = *player_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
    }
    return NULL;
}