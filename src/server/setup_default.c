/*
** EPITECH PROJECT, 2021
** setup_default.c
** File description:
** setup_default.c
*/

#include "server/server.h"

void setup_default_next_next(game_info_t *g_info, server_info_t *s_info, \
char *uuids[37])
{
    team_t *first_team = init_team(uuids[0], "Team1", s_info->max_client);
    team_t *second_team = init_team(uuids[1], "Team2", s_info->max_client);
    team_t *third_team = init_team(uuids[2], "Team3", s_info->max_client);
    team_t *fourth_team = init_team(uuids[3], "Team4", s_info->max_client);

    if (add_team(first_team) == false || add_team(second_team) == false || \
    add_team(third_team) == false || add_team(fourth_team) == false) {
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
    char third_uuid[37] = {0};
    char fourth_uuid[37] = {0};

    uuid_generate(tmp);
    uuid_unparse_lower(tmp, first_uuid);
    uuid_generate(tmp);
    uuid_unparse_lower(tmp, second_uuid);
    uuid_generate(tmp);
    uuid_unparse_lower(tmp, third_uuid);
    uuid_generate(tmp);
    uuid_unparse_lower(tmp, fourth_uuid);
    setup_default_next_next(g_info, s_info, (char *[37]){first_uuid, \
    second_uuid, third_uuid, fourth_uuid, NULL});
}

void setup_default(server_info_t *s_info, game_info_t *g_info)
{
    s_info->port = 4242;
    s_info->max_client = 3;
    s_info->nb_teams = 4;
    g_info->freq = 100;
    g_info->height = 10;
    g_info->width = 10;
    setup_default_next(g_info, s_info);
}