/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** cmd
*/

#include "server/server.h"

static void make_link_client_to_new_player(client_t *client, \
char *team_uuid, game_board_t *game, server_t *server)
{
    player_t *new_player = NULL;

    new_player = get_free_egg_player(team_uuid);
    if (new_player != NULL) {
        for (client_t *tmp = *client_container(); tmp; tmp = tmp->next)
            (tmp->is_graphic == true) ? \
            ebo(tmp->fd, new_player->player_number, server) : 0;
    }
    if (new_player == NULL)
        new_player = get_free_player(team_uuid);
    if (new_player == NULL) {
        new_player = init_player(team_uuid, rand() % \
        game->width, rand() % game->height);
        if (add_player(new_player) == false) {
            printf("error while creating player\n");
            return;
        }
    }
    strcpy(client->uuid, new_player->uuid);
    client->is_ia = true;
}

int check_first_client_send(char *buff, game_board_t *game, \
client_t *client, server_t *server)
{
    team_t *team = get_team_by_name(buff);
    player_t *egg = NULL;

    if (strcmp(buff, "GRAPHIC") == 0) {
        client->is_graphic = true;
        return graphic_send_first_batch(game, client, server);
    }
    if (team != NULL) {
        egg = get_free_egg_player(team->team_uuid);
        if (team->client_max <= 0 && egg == NULL) {
            printf("team full\n");
            return TEAM_FULL;
        }
        (egg != NULL) ? team->client_max -= 1 : 0;
        make_link_client_to_new_player(client, team->team_uuid, game, server);
        return ia_send_first_batch(game, client, server);
    }
    return ERROR;
}

int interpret_cmd(char *buff, server_t *server, game_board_t *game, \
client_t *client)
{
    char **tab = str_to_word_array(buff, " \n");
    bool passed = false;
    int res = 0;

    for (int i = 0; func_tab[i].cmd; i += 1) {
        if (strcmp(func_tab[i].cmd, tab[0]) == 0) {
            passed = true;
            func_tab[i].fun(&tab[1], server, game, client);
        }
    }
    free_tab(tab);
    if (passed)
        return SUCCESS;
    res = check_first_client_send(buff, game, client, server);
    if (res == ERROR && client->is_ia == true)
        (FD_IS_SET) ? dprintf(client->fd, "ko\n") : 0;
    if (res == ERROR && client->is_graphic == true)
        suc(client->fd, server);
    if (res == TEAM_FULL)
        return TEAM_FULL;
    return ERROR;
}