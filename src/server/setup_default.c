/*
** EPITECH PROJECT, 2021
** setup_default.c
** File description:
** setup_default.c
*/

#include "server/server.h"

void setup_default_next_next(game_info_t *g_info, server_info_t *s_info, \
char first[37], char second[37])
{
    team_t *first_team = init_team(first, "team1", s_info->max_client);
    team_t *second_team = init_team(second, "team2", s_info->max_client);

    if (add_team(first_team) == false || add_team(second_team) == false) {
        printf("error while adding a team\n");
        return;
    }
    g_info->teams = *team_container();
}

void setup_default_next(game_info_t *g_info, server_info_t *s_info)
{
    uuid_t tmp;
    char first_uuid[37] = {0};
    char second_uuid[37] = {0};

    uuid_generate(tmp);
    uuid_unparse_lower(tmp, first_uuid);
    uuid_generate(tmp);
    uuid_unparse_lower(tmp, second_uuid);
    setup_default_next_next(g_info, s_info, first_uuid, second_uuid);
}

void setup_default(server_info_t *s_info, game_info_t *g_info)
{
    s_info->port = 4242;
    s_info->max_client = 2;
    s_info->nb_teams = 2;
    g_info->height = 20;
    g_info->freq = 100;
    g_info->width = 20;
    setup_default_next(g_info, s_info);
}