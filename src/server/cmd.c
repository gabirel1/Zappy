/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** cmd
*/

#include "server/server.h"

int interpret_cmd(char *buff, server_t *server, game_board_t *game, \
client_t *client)
{
    char **tab = str_to_word_array(my_strdup(buff), " \n");
    bool passed = false;

    for (int i = 0; func_tab[i].cmd; i += 1) {
        if (strcmp(func_tab[i].cmd, tab[0]) == 0) {
            passed = true;
            func_tab[i].fun(tab, server, game, client);
        }
    }
    if (!passed)
        dprintf(client->fd, "ko\n");
    return SUCCESS;
}