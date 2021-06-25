/*
** EPITECH PROJECT, 2021
** team.c
** File description:
** team.c
*/

#include "server/server.h"

team_t **team_container(void)
{
    static team_t *head = NULL;

    return &head;
}

team_t *init_team(char team_uuid[37], char *team_name, int max_client)
{
    team_t *new_team = my_malloc(sizeof(team_t));

    if (!new_team)
        return NULL;
    memset(new_team, 0, sizeof(team_t));
    strcpy(new_team->team_uuid, team_uuid);
    new_team->team_name = my_strdup(team_name);
    if (!new_team->team_name)
        return NULL;
    new_team->client_max = max_client;

    return new_team;
}

bool add_team(team_t *next)
{
    team_t **front_ptr = team_container();
    team_t *tmp = *front_ptr;

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

bool delete_team(team_t *team)
{
    team_t **front_ptr = team_container();
    team_t *tmp = *front_ptr;
    team_t *second_tmp = *front_ptr;

    if (!*front_ptr)
        return (false);
    if (team == tmp) {
        *front_ptr = tmp->next;
        return (true);
    }
    while (team != tmp->next)
        tmp = tmp->next;
    second_tmp = tmp->next->next;
    tmp->next = second_tmp;
    return (true);
}

team_t *get_team_by_uuid(char *uuid)
{
    for (team_t *tmp = *team_container(); tmp; tmp = tmp->next) {
        if (strcmp(tmp->team_uuid, uuid) == 0)
            return tmp;
    }
    return NULL;
}