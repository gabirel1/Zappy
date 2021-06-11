/*
** EPITECH PROJECT, 2021
** team2.c
** File description:
** team2.c
*/

#include "server/server.h"

team_t *get_team_by_name(char *name)
{
    for (team_t *tmp = *team_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->team_name, name) == 0)
            return tmp;
    }
    return NULL;
}