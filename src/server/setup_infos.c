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
    if (is_full_digits(optarg) == false || atoi(optarg) <= 0) {
        printf("-p option only accepts valid ports\n");
        return ERROR;
    }
    server_info->port = atoi(optarg);
    return SUCCESS;
}

int n_case_next(server_info_t *s_info, char *name)
{
    uuid_t tmp;
    char buffer[37] = {0};
    team_t *new_team = NULL;

    printf("opt n nb ==  '%s'\n", name);
    uuid_generate(tmp);
    uuid_unparse_lower(tmp, buffer);

    if (get_team_by_name(name) != NULL || strcmp(name, "") == 0) {
        printf("-n option only accepts teams with different numbers\n");
        return ERROR;
    }
    new_team = init_team(buffer, name, s_info->max_client);
    if (add_team(new_team) == false) {
        printf("error while adding a team\n");
        return ERROR;
    }
    return SUCCESS;
}

int n_case(game_info_t *g_info, server_info_t *s_info, int ac, char *av[])
{
    int index = optind - 1;
    int count = 0;

    for (team_t *tmp = *team_container(); tmp; tmp = tmp->next) {
        if (delete_team(tmp) == false) {
            printf("error while deleting team\n");
            return ERROR;
        }
    }
    for (; index < ac; index++) {
        if (av[index][0] == '-') {
            optind = index - 1;
            break;
        }
        if (n_case_next(s_info, av[index]) == ERROR)
            return ERROR;
        count++;
    }
    g_info->teams = *team_container();
    s_info->nb_teams = count;
    return SUCCESS;
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
    int res = 0;

    while ((opt = getopt(ac, av, "p:x:y:n:c:f:")) != EOF) {
        res = switch_opt(server_info, game_info, (int [2]){opt, ac}, av);
        if (res == ERROR)
            return ERROR;
    }
    return SUCCESS;
}