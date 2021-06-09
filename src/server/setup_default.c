/*
** EPITECH PROJECT, 2021
** setup_default.c
** File description:
** setup_default.c
*/

#include "server/server.h"

void setup_default(server_info_t *s_info, game_info_t *g_info)
{
    uuid_t tmp;

    s_info->port = 4242;
    s_info->max_client = 2;
    s_info->nb_teams = 2;
    g_info->height = 20;
    g_info->freq = 100;
    g_info->width = 20;
    g_info->team_names = malloc(sizeof(char *) * 3);
    g_info->team_names[0] = strdup("team1");
    g_info->team_names[1] = strdup("team2");
    g_info->team_names[2] = NULL;
    // g_info->team_uuids = malloc(sizeof(char *) * 3);
    // memset(g_info->team_uuids[0], 0, 37);
    // memset(g_info->team_uuids[1], 0, 37);
    // strcpy("team1", g_info->team_uuids[0]);
    // strcpy("team1", g_info->team_uuids[0]);
    // g_info->team_uuids[2] = NULL;
}