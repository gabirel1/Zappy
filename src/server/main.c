/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** main.c
*/

#include "server/server.h"

int main(int ac, char *av[])
{
    server_info_t server_info;
    game_info_t game_info;
    int res = 0;

    setup_default(&server_info, &game_info);
    if ((res = setup_infos(ac, av, &server_info, &game_info)) == ERROR) {
        if (game_info.team_names != NULL)
            free(game_info.team_names);
    }
    if (res == 21) {
        free_tab(game_info.team_names);
        return help_func(FAILURE);
    }
    if (res == 42)
        free_tab(game_info.team_names);
    else if (game_info.team_names != NULL)
        free(game_info.team_names);
    return SUCCESS;
}