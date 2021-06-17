/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** loop
*/

#include "server/server.h"

int server_loop(server_t *server, int res, server_info_t *server_in, \
game_board_t *game)
{
    server->read_fd_set = server->active_fd_set;
    server->write_fd_set = server->active_fd_set;
    if (select(FD_SETSIZE, &server->read_fd_set, &server->write_fd_set, \
    NULL, &server->timeout) == -1) {
        fprintf(stderr, "Error while waiting for client\n");
        return ERROR;
    }
    if (my_handler(12, false) != 0)
        return ERROR;
    for (int i = 0; i < FD_SETSIZE; i += 1) {
        if (FD_ISSET(i, &server->read_fd_set))
            res = handle_connection(server, server_in, game, i);
        if (res == ERROR)
            stop_client(i, server, &res);
    }
    update_cooldown(game);
    return SUCCESS;
}