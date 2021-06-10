/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** cmd
*/

#include "server/server.h"

static void make_link_client_to_new_player(client_t *client, char *team_uuid)
{
    player_t *new_player = init_player(team_uuid, 10, 10); // change value later
    if (add_player(new_player) == false) {
        printf("error while creating player\n");
        return;
    }
    strcpy(client->uuid, new_player->uuid);
    client->is_ia = true;
}

int check_first_client_send(char *buff, game_board_t *game, \
client_t *client)
{
    if (strcmp(buff, "GRAPHIC") == 0) {
        client->is_graphic = true;
        return SUCCESS;
    }
    for (int index = 0; game->team_names[index]; index++) {
        if (strcmp(buff, game->team_names[index]) == 0) {
            make_link_client_to_new_player(client, game->team_uuids[index]);
            return SUCCESS;
        }
    }
    return ERROR;
}

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
    if (!passed) {
        if (check_first_client_send(buff, game, client) == ERROR)
            dprintf(client->fd, "ko\n");
    }
    return SUCCESS;
}