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

    srand(time(NULL));
    signal(SIGINT, my_sighandler);
    signal(SIGPIPE, SIG_IGN);
    setup_default(&server_info, &game_info);
    if ((res = setup_infos(ac, av, &server_info, &game_info)) == ERROR) {
        return help_func(FAILURE);
    }
    if (create_server(&server_info, &game_info) == ERROR)
        return help_func(FAILURE);
    return SUCCESS;
}