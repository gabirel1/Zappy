/*
** EPITECH PROJECT, 2021
** setup_infos.c
** File description:
** setup_infos.c
*/

#include "server/server.h"

int p_case(server_info_t *server_info)
{
    printf("opt p == %s\n", optarg);
    if (is_full_digits(optarg) == false) {
        printf("-p option only accepts valid ports\n");
        return ERROR;
    }
    server_info->port = atoi(optarg);
    return SUCCESS;
}

int n_case(game_info_t *g_info, server_info_t *s_info, int ac, char *av[])
{
    int index = 0;
    int len = 0;

    index = optind - 1;
    free_tab(g_info->team_names);
    g_info->team_names = NULL;
    g_info->team_names = malloc(sizeof(char *));
    g_info->team_names[0] = NULL;
    for (; index < ac; index++) {
        if (av[index][0] == '-') {
            optind = index - 1;
            break;
        }
        printf("opt n nb ==  %s\n", av[index]);
        len = get_tab_len(g_info->team_names);
        g_info->team_names = realloc(g_info->team_names, (S_CHAR * (len + 2)));
        g_info->team_names[len + 1] = NULL;
        g_info->team_names[len] = my_strdup(av[index]);
    }
    s_info->nb_teams = get_tab_len(g_info->team_names);
    return 42;
}

int switch_opt(server_info_t *s_info, game_info_t *g_info, \
int opt_ac[2], char *av[])
{
    switch (opt_ac[0]) {
        case 'p':
            return p_case(s_info);
        case 'x':
            return x_case(g_info);
        case 'y':
            return y_case(g_info);
        case 'n':
            return n_case(g_info, s_info, opt_ac[1], av);
        case 'c':
            return c_case(s_info);
        case 'f':
            return f_case(g_info);
        default :
            return ERROR;
    }
}

int setup_infos(int ac, char *av[], server_info_t *server_info, \
game_info_t *game_info)
{
    int opt = 0;
    bool done = false;
    int res = 0;
    bool n_done = false;

    while ((opt = getopt(ac, av, "p:x:y:n:c:f:")) != EOF) {
        if (done == false) {
            done = true;
        }
        res = switch_opt(server_info, game_info, (int [2]){opt, ac}, av);
        if (res == ERROR && n_done == true)
            return ERROR;
        else if (res == ERROR && n_done == false)
            return 21;
        if (res == 42)
            n_done = true;
    }
    if (done == false || n_done == false)
        return 42;
    return SUCCESS;
}